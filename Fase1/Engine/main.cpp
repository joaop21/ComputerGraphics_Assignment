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
		Figure current_fig = figures[0];
		vector<Point> current_points = current_fig.points;

		glBegin(GL_TRIANGLES);
		int color;
		glColor3f(0, 0, 0.2);

		for(int j = 0, color = 0 ; j < current_points.size() ; j++,color++){

			if (color % 3 == 0) {
				glColor3f(0, 0, 0.4);
				if (color%6 == 0) glColor3f(0, 0, 0.2);
			}

			Point current_point = current_points[j];
			glVertex3f(current_point.x, current_point.y, current_point.z);
		}
		glEnd();
	}
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
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	load_generated_files();
	load_figures();

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	// fazer cenas
}


void processSpecialKeys(int key_code, int xx, int yy) {
	// fazer cenas
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Engine");

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
