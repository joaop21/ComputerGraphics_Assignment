#include "figures.h"
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace figures;

int figures::generateSphere(float r, int slices, int stacks, std::string file_name){
	std::vector<Point> points;

	float sls = 2*M_PI / slices; // algulo entre cada slice (sliceStep)
	float sts = M_PI / stacks;	 // algulo entre cada stack (stackStep)

	for(int i = 0 ; i < stacks ; i++ ){
		float beta = i*sts;  // angulo que a stack atual faz com o eixo do Y
		float next_beta = (i+1)*sts; // angulo que a stack a seguir faz com o eixo do Y
		float rs = r*sin(beta); // raio stack (atual)
		float rsn = r*sin(next_beta); // raio da stack seguinte
		for(int j = 0 ; j < slices ; j++){
			float alfa = j*sls; // angulo que a slice atual faz com o eixo do X
			float next_alfa = (j+1)*sls; // angulo que a slice seguinte faz com o eixo do X
			points.push_back(Point(rs*cos(alfa), r*cos(beta), rs*sin(alfa)));
			points.push_back(Point(rsn*cos(next_alfa), r*cos(next_beta), rsn*sin(next_alfa)));
			points.push_back(Point(rsn*cos(alfa), r*cos(next_beta), rsn*sin(alfa)));

			points.push_back(Point(rs*cos(next_alfa), r*cos(beta), rs*sin(next_alfa)));
			points.push_back(Point(rsn*cos(next_alfa), r*cos(next_beta), rsn*sin(next_alfa)));
			points.push_back(Point(rs*cos(alfa), r*cos(beta), rs*sin(alfa)));
		}
	}

	int res = write_in_file(points, file_name);
	return res;
}
