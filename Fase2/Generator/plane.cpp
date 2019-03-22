#include <iostream>
#include <fstream>
#include <vector>
#include "figures.h"

using namespace figures;

int figures::generatePlane(float side, std::string file_name){
	std::vector<Point> points;

	float parcial_side = side/2;

	// primeiro triangulo
	points.push_back(Point(parcial_side, 0.0, -parcial_side));
	points.push_back(Point(-parcial_side, 0.0, -parcial_side));
	points.push_back(Point(-parcial_side, 0.0, parcial_side));

	// segundo triangulo
	points.push_back(Point(parcial_side, 0.0, -parcial_side));
	points.push_back(Point(-parcial_side, 0.0, parcial_side));
	points.push_back(Point(parcial_side, 0.0, parcial_side));

	int res = write_in_file(points, file_name);
	return res;
}
