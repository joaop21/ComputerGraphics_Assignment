#ifndef SPHERE_H
#define SPHERE_H
#endif

#define _USE_MATH_DEFINES
#include <math.h>

/**
r - radius
sls - SliceStep
sts - StackStep
rs - raio da stack atual
rsn - raio da stack seguinte
*/

int generateSphere(float r, int slices, int stacks, string file_name){
	std::vector<Point> points;

	float sls = 2*M_PI / slices;
	float sts = M_PI / stacks;

	for(int i = 0 ; i < stacks ; i++ ){
		float beta = i*sts;
		float next_beta = (i+1)*sts;
		float rs = r*sin(beta); // radius stack (atual)
		float rsn = r*sin(next_beta); // radius stack next
		for(int j = 0 ; j < slices ; j++){
				float alfa = j*sls; // alfa anda no plano XZ
				float next_alfa = (j+1)*sls;
			points.push_back(Point(rs*cos(alfa), r*cos(beta), rs*sin(alfa)));
			points.push_back(Point(rsn*cos(next_alfa), r*cos(next_beta), rsn*sin(next_alfa)));
			points.push_back(Point(rsn*cos(alfa), r*cos(next_beta), rsn*sin(alfa)));

			points.push_back(Point(rs*cos(next_alfa), r*cos(beta), rs*sin(next_alfa)));
			points.push_back(Point(rsn*cos(next_alfa), r*cos(next_beta), rsn*sin(next_alfa)));
			points.push_back(Point(rs*cos(alfa), r*cos(beta), rs*sin(alfa)));
		}
	}

	// necessário operações sobre ficheiros
	ofstream file ("../Generated_Models/" + file_name);
  	if (file.is_open()){

		// no inicio escrevem-se o numero de triangulos existente no ficheiro
		int num_points = points.size();
	    file << to_string(num_points / 3) + "\n";

		// escrita dos pontos no ficheiro
		for(int i = 0 ; i < num_points ; i++){
			Point temp = points[i];
			file << to_string(temp.getX()) + " " +
					to_string(temp.getY()) + " " +
					to_string(temp.getZ()) + "\n";
		}
	    file.close();
		return 1;
    } else return 0;
}
