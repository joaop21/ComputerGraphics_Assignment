#ifndef CONE_H
#define CONE_H
#endif

#define _USE_MATH_DEFINES
#include <math.h>

int generateCone(float bottom_radius, float height, int slices, int stacks, string file_name){

	std::vector<Point> points;

	// base
	float alfa = 2*M_PI/slices;
	for(int i = 0; i < slices; i++){
		points.push_back(Point(0.0, 0.0, 0.0));
		points.push_back(Point(bottom_radius*cos(alfa*(i)), 0.0, bottom_radius*sin(alfa*(i))));
		points.push_back(Point(bottom_radius*cos(alfa*(i+1)), 0.0, bottom_radius*sin(alfa*(i+1))));
	}

	// cone (dúvidas na regra da mão direita)
	float beta = 2*M_PI/stacks;
	for(int j = 0; j < stacks; j++){
		points.push_back(Point(bottom_radius*cos(beta*(j)), 0.0, bottom_radius*sin(beta*(j))));
		points.push_back(Point(0.0, height, 0.0));
		points.push_back(Point(bottom_radius*cos(beta*(j+1)), 0.0, bottom_radius*sin(beta*(j+1))));
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
