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

Tree tree_struct;

void draw_figure(vector<Point> points) {

	glBegin(GL_TRIANGLES);
	int color;
	glColor3f(0.2, 0.2, 0.2);

	for(int j = 0, color = 0 ; j < points.size() ; j++,color++){
		if (color % 3 == 0) {
			glColor3f(0.4, 0.4, 0.4);
			if (color%6 == 0) glColor3f(0.2, 0.2, 0.2);
		}

		Point current_point = points[j];
		glVertex3f(current_point.x, current_point.y, current_point.z);
	}
	glEnd();
}

void draw_tree(Tree t) {

	glPushMatrix();

	if (!t.head_figure.translation.empty)
		glTranslatef(t.head_figure.translation.x, t.head_figure.translation.y, t.head_figure.translation.z);
	if (!t.head_figure.rotation.empty)
		glRotatef(t.head_figure.rotation.angle, t.head_figure.rotation.x, t.head_figure.rotation.y, t.head_figure.rotation.z);
	if (!t.head_figure.scale.empty)
		glScalef(t.head_figure.scale.x, t.head_figure.scale.y, t.head_figure.scale.z);

	draw_figure(t.head_figure.points);

	vector<Tree>::iterator it;

	for (it = t.children.begin(); it != t.children.end(); it++)
		draw_tree(*it);

	glPopMatrix();
}

void draw_axis(){

	glColor3f(0.0f, 1.0f, 0.0f); // green
	glBegin(GL_LINE_STRIP); // yy axis
	glVertex3f(0.0f, 20.0f, 0.0f);
	glVertex3f(0.0f, -20.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f); //blue
	glBegin(GL_LINE_STRIP); // zz axis
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f); // red
	glBegin(GL_LINE_STRIP); // xx axis
	glVertex3f(20.0f, 0.0f, 0.0f);
	glVertex3f(-20.0f, 0.0f, 0.0f);
	glEnd();
}

// camera angles
float alfa = M_PI/4;
float beta = M_PI/4;

// radius
float camera_radius = 10.0;
float camera_radius_line;

// camera posicion
float px;
float py;
float pz;

// look at point
float dx = 0.0;
float dy = 0.0;
float dz = 0.0;

void desenha_coordenadas_camara(float radiusn, float alfan, float betan, float dxn, float dyn, float dzn){
	alfa = alfan;
	beta = betan;

	camera_radius = radiusn;
	camera_radius_line = camera_radius * cos(beta);

	px = camera_radius_line * cos(alfa);
	py = camera_radius * sin(beta);
	pz = camera_radius_line * sin(alfa);

	dx = dxn;
	dy = dyn;
	dz = dzn;

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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	desenha_coordenadas_camara(camera_radius,alfa,beta,dx,dy,dz);
	glLoadIdentity();
	gluLookAt(px,py,pz,
		      dx,dy,dz,
			  0.0f,1.0f,0.0f);

	draw_axis();

	draw_tree(tree_struct);

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	switch (c)
	{
	case 'd':
		dx -= 0.1;
		break;
	case 'a':
		dx += 0.1;
		break;
	case 'w':
		dy -= 0.1;
		break;
	case 's':
		dy += 0.1;
		break;
	case 'q':
		dz -= 0.1;
		break;
	case 'e':
		dz += 0.1;
		break;
	case '+':
		camera_radius -= 0.1;
		break;
	case '-':
		camera_radius += 0.1;
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
	glutPostRedisplay();
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1000,800);
	glutCreateWindow("Engine");

// struct load
	tree_struct = parser_XML();

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
