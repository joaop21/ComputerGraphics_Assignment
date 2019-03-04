#ifndef CONE_H
#define CONE_H
#endif

#define _USE_MATH_DEFINES
#include <math.h>

int generateCone(float bottom_radius, float height, int slices, int stacks, string file_name){

	std::vector<Point> points;

	for(int i = 0; i < slices; i++){
		float alfa = (i)*2*M_PI/slices;
		float next_alfa = (i+1)*2*M_PI/slices;

		// base
		points.push_back(Point(0.0, 0.0, 0.0));
		points.push_back(Point(bottom_radius*cos(alfa), 0.0, bottom_radius*sin(alfa)));
		points.push_back(Point(bottom_radius*cos(next_alfa), 0.0, bottom_radius*sin(next_alfa)));

		// lado (exceto o topo)
		// nr = new radius (stack)
		// pr = previous radius (stack)
		// nh = new height (stack)
		// ph = previous height (stack)
		float ph = 0, pr = bottom_radius;
		for (int j = 0; j < stacks-1; j++) {
			float nh = height / stacks * j;
			float nr = (height - nh) * bottom_radius / height;

			points.push_back(Point(nr * cos(alfa), nh, nr * sin(alfa)));
			points.push_back(Point(pr * cos(next_alfa), ph, pr * sin(next_alfa)));
			points.push_back(Point(pr * cos(alfa), ph, pr * sin(alfa)));

			points.push_back(Point(nr * cos(alfa), nh, nr * sin(alfa)));
			points.push_back(Point(nr * cos(next_alfa), nh, nr * sin(next_alfa)));
			points.push_back(Point(pr * cos(next_alfa), ph, pr * sin(next_alfa)));

			ph = nh;
			pr = nr;
		}

		// topo
		points.push_back(Point(0.0, height, 0.0));
		points.push_back(Point(pr * cos(next_alfa), ph, pr * sin(next_alfa)));
		points.push_back(Point(pr * cos(alfa), ph, pr * sin(alfa)));
	}


	int res = write_in_file(points, file_name);
	return res;
}
