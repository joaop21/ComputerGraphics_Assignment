#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "IL/il.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "tinyxml2.h"
#include "geometry.h"
#include "parser.h"


using namespace tinyxml2;
using namespace std;
using namespace geometry;

Tree tree_struct;
float alfa = 0.5f, beta = 0.5f, radius = 500.0f;
float camx, camy, camz, dx = 0.0, dy = 0.0, dz = 0.0;
int timebase = 0, frame = 0;

void draw_figure(Figure fig) {

	GLuint buffers[2];
	glGenBuffers(2, buffers); // Generate Vertex Buffer Objects

	float *vertex;
	float *normal;
	vertex = (float *) malloc(sizeof(float) * fig.num_triangles * 3 * 3); // num_triangles x num_vertices x num_coordinates
	normal = (float *) malloc(sizeof(float) * fig.num_triangles * 3 * 3); // num_triangles x num_vertices x num_coordinates
	vector<Point>::iterator it;
	int i = 0;
	for(it = fig.points.begin() ; it != fig.points.end() ; it++){
		vertex[i++] = it->x;
		vertex[i++] = it->y;
		vertex[i++] = it->z;
	}

	i = 0;
	for(it = fig.normals.begin() ; it != fig.normals.end() ; it++){
		normal[i++] = it->x;
		normal[i++] = it->y;
		normal[i++] = it->z;
	}

	float color[4] = { fig.color.r, fig.color.g, fig.color.b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float) * fig.num_triangles * 3 * 3, vertex, GL_STATIC_DRAW);
	glVertexPointer(3,GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * fig.num_triangles * 3 * 3, normal,GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT,0,0);

	glDrawArrays(GL_TRIANGLES, 0, fig.num_triangles * 3 * 3);

	free(vertex);
	free(normal);
}

void draw_tree(Tree t) {

	glPushMatrix();

	if (!t.head_figure.translation.empty){
		t.head_figure.translation.apply_translation(t.head_figure.name);
	}
	if (!t.head_figure.rotation.empty){
		t.head_figure.rotation.apply_rotation();
	}
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

void spherical2Cartesian() {
	camx = radius * cos(beta) * sin(alfa);
	camy = radius * sin(beta);
	camz = radius * cos(beta) * cos(alfa);
}

void renderScene(void) {

	float fps;
	int time;
	char s[64];

	// clear buffers
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camx+dx, camy+dy, camz+dz,
		      dx,dy,dz,
			  0.0f,1.0f,0.0f);

	for(Light l : tree_struct.lights){
		l.apply();
	}

	draw_axis();

	draw_tree(tree_struct);

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
		timebase = time;
		frame = 0;
		sprintf(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	}

	// End of frame
	glutSwapBuffers();
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

void initGL() {

// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);


// init
	spherical2Cartesian();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	for(Light lig : tree_struct.lights){
		glEnable(lig.l);
	}
}



int loadTexture(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1,&texID);

	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;

}



int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1600,1000);
	glutCreateWindow("Solar System");

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
	#ifndef __APPLE__
		glewInit();
	#endif

	initGL();

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
