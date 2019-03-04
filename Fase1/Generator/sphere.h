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

	float sls = 2*M_PI / slices; // sliceStep
	float sts = M_PI / stacks; //

	for(int i = 0 ; i < stacks ; i++ ){
		float rs = r*sin(i*sts); // raio da stack atual
		float rsn = r*sin((i+1)*sts); // raio da stack seguinte
		for(int j = 0 ; j < slices ; j++){
			points.push_back(Point(rs*cos(j*sls), r*cos(i*sts), rs*sin(j*sls)));
			points.push_back(Point(rsn*cos((j+1)*sls), r*cos((i+1)*sts), rsn*sin((j+1)*sls)));
			points.push_back(Point(rsn*cos(j*sls), r*cos((i+1)*sts), rsn*sin(j*sls)));

			points.push_back(Point(rs*cos((j+1)*sls), r*cos(i*sts), rs*sin((j+1)*sls)));
			points.push_back(Point(rsn*cos((j+1)*sls), r*cos((i+1)*sts), rsn*sin((j+1)*sls)));
			points.push_back(Point(rs*cos(j*sls), r*cos(i*sts), rs*sin(j*sls)));
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
