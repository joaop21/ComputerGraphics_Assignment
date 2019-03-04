#ifndef SPHERE_H
#define SPHERE_H
#endif

#define _USE_MATH_DEFINES
#include <math.h>

int generateSphere(float radius, int slices, int stacks, string file_name){
	std::vector<Point> points;

	float sliceStep = 2*M_PI / slices;
	float stackStep = M_PI / stacks;

	for(int i = 0 ; i < stacks ; i++ ){
		float rstack = radius*sin(i*stackStep); // raio da stack atual
		float rstack_next = radius*sin((i+1)*stackStep); // raio da stack seguinte
		for(int j = 0 ; j < slices ; j++){
			points.push_back(Point(rstack*cos(j*sliceStep), radius*cos(i*stackStep), rstack*sin(j*sliceStep)));
			points.push_back(Point(rstack_next*cos((j+1)*sliceStep), radius*cos((i+1)*stackStep), rstack_next*sin((j+1)*sliceStep)));
			points.push_back(Point(rstack_next*cos(j*sliceStep), radius*cos((i+1)*stackStep), rstack_next*sin(j*sliceStep)));

			points.push_back(Point(rstack*cos((j+1)*sliceStep), radius*cos(i*stackStep), rstack*sin((j+1)*sliceStep)));
			points.push_back(Point(rstack_next*cos((j+1)*sliceStep), radius*cos((i+1)*stackStep), rstack_next*sin((j+1)*sliceStep)));
			points.push_back(Point(rstack*cos(j*sliceStep), radius*cos(i*stackStep), rstack*sin(j*sliceStep)));
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
