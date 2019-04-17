#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "tinyxml2.h"
#include "geometry.h"
#include "parser.h"

using namespace tinyxml2;
using namespace std;
using namespace geometry;

#define POINT_COUNT 8

Tree tree_struct;
float p[POINT_COUNT][3];
float time_p = 0;

void vector_to_matrix(vector<Point> points){
	vector<Point>::iterator it;
	int i = 0;
	for(it = points.begin() ; it != points.end() ; it++,i++){
		p[i][0] = it->x;
		p[i][1] = it->y;
		p[i][2] = it->z;
	}
}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};

	float ax[4], ay[4], az[4];
	float px[4], py[4], pz[4];
	px[0] = p0[0]; px[1] = p1[0]; px[2] = p2[0]; px[3] = p3[0];
	py[0] = p0[1]; py[1] = p1[1]; py[2] = p2[1]; py[3] = p3[1];
	pz[0] = p0[2]; pz[1] = p1[2]; pz[2] = p2[2]; pz[3] = p3[2];

	multMatrixVector(*m, px, ax);
	multMatrixVector(*m, py, ay);
	multMatrixVector(*m, pz, az);

	float tpos[4] = { t*t*t, t*t, t, 1};
	pos[0] = 0; pos[1] = 0; pos[2] = 0;
	for(int i=0; i<4; i++){
		pos[0] += tpos[i] * ax[i];
		pos[1] += tpos[i] * ay[i];
		pos[2] += tpos[i] * az[i];
	}

	float tderiv[4] = { 3*t*t, 2*t, 1, 0};
	deriv[0] = 0; deriv[1] = 0; deriv[2] = 0;
	for(int i=0; i<4; i++){
		deriv[0] += tderiv[i] * ax[i];
		deriv[1] += tderiv[i] * ay[i];
		deriv[2] += tderiv[i] * az[i];
	}
}

void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	int indices[4];
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT;
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void renderCatmullRomCurve() {

// desenhar a curva usando segmentos de reta - GL_LINE_LOOP

	float pos[3], deriv[3];
	float tam = 1000; // nº de divisoes que vou querer fazer
	float deltaT = 1.0/tam; // vai ajudar a estabelecer a "divisao em que estou"
	glBegin(GL_LINE_LOOP);

		// percorro todas as divisoes, e o globalt multiplico pela divisao que estabeleci, desde 0 até 1
		for(int i=0; i<tam; i++){
			getGlobalCatmullRomPoint(deltaT*i,pos,deriv);
			glVertex3f(pos[0],pos[1],pos[2]);
		}

	glEnd();
}


void draw_figure(Figure fig) {

	GLuint t;
	glGenBuffers(1, &t); // Generate Vertex Buffer Objects
	glBindBuffer(GL_ARRAY_BUFFER, t); // Bind a named buffer object

	float *v;
	v = (float *) malloc(sizeof(float) * fig.num_triangles * 3 * 3); // num_triangles x num_vertices x num_coordinates
	vector<Point>::iterator it;
	int i = 0;
	for(it = fig.points.begin() ; it != fig.points.end() ; it++){
		v[i++] = it->x;
		v[i++] = it->y;
		v[i++] = it->z;
	}

	Color color = fig.color;
	glColor3f(color.r, color.g, color.b);


	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * fig.num_triangles * 3 * 3, v, GL_STATIC_DRAW); // Fill buffer
					 // (GL_ARRAY_BUFFER, arraySize (in bytes), v, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0); // Define an array of vertex data
							// (GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
	glDrawArrays(GL_TRIANGLES, 0, fig.num_triangles * 3); // Render primitives from array data
					 // (GL_TRIANGLES, first, count);

	free(v);
}

void draw_tree(Tree t) {

	glPushMatrix();

	if (!t.head_figure.translation.empty){
		vector_to_matrix(t.head_figure.translation.points);
		renderCatmullRomCurve();

		float pos[3], deriv[3];

		// desenhar o objeto
		getGlobalCatmullRomPoint(time_p,pos,deriv); // com o t (global t) inicial vou buscar o catmull-rom point
		glTranslatef(pos[0],pos[1],pos[2]); // faço o translate para essa posicao
	}
	if (!t.head_figure.rotation.empty)
		glRotatef(t.head_figure.rotation.angle, t.head_figure.rotation.x, t.head_figure.rotation.y, t.head_figure.rotation.z);
	if (!t.head_figure.scale.empty)
		glScalef(t.head_figure.scale.x, t.head_figure.scale.y, t.head_figure.scale.z);


	draw_figure(t.head_figure);

	vector<Tree>::iterator it;

	for (it = t.children.begin(); it != t.children.end(); it++)
		draw_tree(*it);

	glPopMatrix();
}

void draw_axis(){

	glColor3f(0.0f, 1.0f, 0.0f); // green
	glBegin(GL_LINE_STRIP); // yy axis
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f); //blue
	glBegin(GL_LINE_STRIP); // zz axis
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f); // red
	glBegin(GL_LINE_STRIP); // xx axis
	glVertex3f(1000.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glEnd();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


float alfa = 0.5f, beta = 0.5f, radius = 500.0f;
float camx, camy, camz, dx = 0.0, dy = 0.0, dz = 0.0;

void spherical2Cartesian() {
	camx = radius * cos(beta) * sin(alfa);
	camy = radius * sin(beta);
	camz = radius * cos(beta) * cos(alfa);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camx+dx, camy+dy, camz+dz,
		      dx,dy,dz,
			  0.0f,1.0f,0.0f);

	draw_axis();

	draw_tree(tree_struct);

	// End of frame
	glutSwapBuffers();

	time_p += 0.001;
}

void processKeys(unsigned char c, int xx, int yy) {
	switch (c)
	{
	case 'd':
		dx -= 20;
		break;
	case 'a':
		dx += 20;
		break;
	case 'w':
		dy -= 20;
		break;
	case 's':
		dy += 20;
		break;
	case 'q':
		dz -= 20;
		break;
	case 'e':
		dz += 20;
		break;
	case '+':
		radius -= 20;
		break;
	case '-':
		radius += 20;
		break;
	case 'z':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'x':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 'c':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	spherical2Cartesian();
	glutPostRedisplay();
}


void processSpecialKeys(int key_code, int xx, int yy) {
	switch(key_code){
		case GLUT_KEY_UP:
			if(beta < (M_PI/2)-0.1)
				beta += 0.1;
			break;
		case GLUT_KEY_DOWN:
			if(beta > -(M_PI/2)+0.1)
				beta -= 0.1;
			break;
		case GLUT_KEY_LEFT:
			alfa += 0.1;
			break;
		case GLUT_KEY_RIGHT:
			alfa -= 0.1;
			break;
	}
	spherical2Cartesian();
	glutPostRedisplay();
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(2000,1000);
	glutCreateWindow("Engine");

// struct load
	tree_struct = parser_XML();

// Required callback registry
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	#ifndef __APPLE__
		glewInit();
	#endif

	spherical2Cartesian();

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
