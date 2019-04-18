#ifndef GEOMETRY_H
#define GEOMETRY_H
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <string>

using namespace std;

#define POINT_COUNT 8

namespace geometry{

    /**
    * @brief classe que define intancias de Ponto
    */
    class Point{
        public:
            float x,y,z;
    };

    /**
    * @brief classe que define intancias de Translações
    */
    class Translation{
        public:
            Translation() :empty(true) {}
            bool empty;
            float time;
            vector<Point> points;

            float p[POINT_COUNT][3];

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

            void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos) {

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
            }

            void getGlobalCatmullRomPoint(float gt, float *pos) {

            	float t = gt * POINT_COUNT; // this is the real global t
            	int index = floor(t);  // which segment
            	t = t - index; // where within  the segment

            	int indices[4];
            	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
            	indices[1] = (indices[0]+1)%POINT_COUNT;
            	indices[2] = (indices[1]+1)%POINT_COUNT;
            	indices[3] = (indices[2]+1)%POINT_COUNT;

            	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos);
            }

            void renderCatmullRomCurve() {

            // desenhar a curva usando segmentos de reta - GL_LINE_LOOP

            	float pos[3];
            	float tam = 1000; // nº de divisoes que vou querer fazer
            	float deltaT = 1.0/tam; // vai ajudar a estabelecer a "divisao em que estou"
            	glColor3f(0.86f, 0.86f, 0.86f); // grey
            	glBegin(GL_LINE_LOOP);

            		// percorro todas as divisoes, e o globalt multiplico pela divisao que estabeleci, desde 0 até 1
            		for(int i=0; i<tam; i++){
            			getGlobalCatmullRomPoint(deltaT*i,pos);
            			glVertex3f(pos[0],pos[1],pos[2]);
            		}

            	glEnd();
            }

            void apply_translation(){

            vector_to_matrix(points);
        		renderCatmullRomCurve();

        		float pos[3], deriv[3];
        		float time_p = glutGet(GLUT_ELAPSED_TIME)/(time*1000);

        		getGlobalCatmullRomPoint(time_p,pos);
        		glTranslatef(pos[0],pos[1],pos[2]);
            }
    };

    /**
    * @brief classe que define intancias de Rotaçoes
    */
    class Rotation{
        public:
            Rotation() :empty(true), angle(-1), time(-1) {}
            bool empty;
            float angle,x,y,z,time;

            void apply_rotation(){

        		if(time != -1) angle = glutGet(GLUT_ELAPSED_TIME)*360/(time*1000);

        		glRotatef(angle, x, y, z);
            }
    };

    /**
    * @brief classe que define intancias de Escalas
    */
    class Scale{
        public:
            Scale() :empty(true) {}
            bool empty;
            float x,y,z;
    };

    /**
    * @brief classe que define intancias de Cor
    */
    class Color{
        public:
            float r,g,b;
    };

    /**
    * @brief classe que define intancias de Figura
    */
    class Figure{
        public:
            string name;
            int num_triangles;
            vector<Point> points;
            Translation translation;
            Rotation rotation;
            Scale scale;
            Color color;
    };

    /**
    * @brief classe que define intancias de Arvores
    */
    class Tree{
        public:
            Figure head_figure;
            vector<Tree> children;
    };

}
