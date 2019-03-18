#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "tinyxml2.h"
#include "point.h"
#include "figure.h"

using namespace tinyxml2;
using namespace std;

vector<Figure> figures; // estrutura que armazen todas as figuras carregadas de ficheiros


/**
* @brief Função que lê o ficheiro XML que contêm os modelos a carregar,
*     posteriormente lê os modelos e armazena os pontos e as figuras necessárias
*     para mais à frente poderem ser desenhadas.
*/
void load_generated_files(){
	XMLDocument doc;
	doc.LoadFile("../Scenes/scene.xml");

	// testa se ficheiro XML abriu sem erros
	if(doc.ErrorID() != 0) {
		cout << "Erro ao abrir o ficheiro xml.\n";
		return;
	}

	XMLElement *pRoot = doc.FirstChildElement("scene");
	if (pRoot == nullptr) return; // testa se obteve a raiz da arvore xml


	vector<string> files; // nomes de ficheiros que contêm as figuras

	// filtra os nomes dos ficheiros
	XMLElement *file_names = pRoot->FirstChildElement("model");
	while(file_names) {
		string new_file = file_names->Attribute("file"); // retira o nome do ficheiro
		files.push_back(new_file); // coloca o nome no vetor
		file_names = file_names->NextSiblingElement("model"); // passa para o proximo filho
	}

	// filtra os pontos e figuras
	for(int i = 0 ; i < files.size() ; i++){
		string current_file = files[i];
		ifstream file;
		file.open("../Generated_Models/" + current_file);

		Figure fig;
		file >> fig.num_triangles;
		while (!file.eof()) {
			Point new_point;
			file >> new_point.x >> new_point.y >> new_point.z;
			fig.points.push_back(new_point);
		}
		figures.push_back(fig);
	}

}


/**
* @brief Função que vai à variável global figures buscar as Figuras anteriormente
*    carregadas de ficheiros e as desenha.
*/
void load_figures(){
	for(int i = 0 ; i < figures.size() ; i++){
		Figure current_fig = figures[i];
		vector<Point> current_points = current_fig.points;

		glBegin(GL_TRIANGLES);
		int color;
		glColor3f(0.2, 0.2, 0.2);

		for(int j = 0, color = 0 ; j < current_points.size() ; j++,color++){

			if (color % 3 == 0) {
				glColor3f(0.4, 0.4, 0.4);
				if (color%6 == 0) glColor3f(0.2, 0.2, 0.2);
			}

			Point current_point = current_points[j];
			glVertex3f(current_point.x, current_point.y, current_point.z);
		}
		glEnd();
	}
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

	load_figures();

	draw_axis();

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
	glutInitWindowSize(800,800);
	glutCreateWindow("Engine");

// file load
	load_generated_files();

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
