#include "figures.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace figures;

int MAX_PATCH_INDEXES = 16;
int number_patches = 0;
unsigned int *patches;
float *control_points;

void parsePatchFile(std::string patch_file){

    std::ifstream file;
    file.open("../Generated_Models/" + patch_file);

	std::string firstLine, line;
	getline(file, firstLine); // get the first line

	number_patches = atoi(firstLine.c_str());
	patches = (unsigned int*) malloc(sizeof(unsigned int) * number_patches * MAX_PATCH_INDEXES);

	/* Save Patches */
	for (int patch_number = 0; patch_number < number_patches; patch_number++) {
		getline(file, line);
		std::istringstream indexes(line);
		std::string indexCP;

		for (int pos = 0; pos < MAX_PATCH_INDEXES && getline(indexes, indexCP, ','); pos++)
			patches[patch_number * MAX_PATCH_INDEXES + pos] = atoi(indexCP.c_str());
	}

	/* Save Control Points */
	getline(file, firstLine);
	int number_control_points = atoi(firstLine.c_str());
	control_points = (float *) malloc(sizeof(float) * 3 * number_control_points);

	for (int control_point = 0; control_point < number_control_points; control_point++) {
		getline(file, line);
		std::istringstream indexes(line);
		std::string indexCP;
		for (int position = 0; position < 3 && getline(indexes, indexCP, ','); position++)
			control_points[control_point * 3 + position] = (float)atof(indexCP.c_str());
    }
}


Point bezierPoint(int patch_number, float u, float v) {
	Point p(0, 0, 0);

	// Bernstein Polynomial
	float bpu[4] = { powf(1 - u, 3), 3 * u * powf(1 - u, 2), 3 * powf(u, 2) * (1 - u), powf(u, 3) };
	float bpv[4] = { powf(1 - v, 3), 3 * v * powf(1 - v, 2), 3 * powf(v, 2) * (1 - v), powf(v, 3) };

	// Bezier Patch sum
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			int indexInsidePatch = j * 4 + i;
			int indexCP = patches[patch_number * MAX_PATCH_INDEXES + indexInsidePatch];
			p.setX(p.getX() + control_points[indexCP * 3 + 0] * bpu[j] * bpv[i]);
			p.setY(p.getY() + control_points[indexCP * 3 + 1] * bpu[j] * bpv[i]);
			p.setZ(p.getZ() + control_points[indexCP * 3 + 2] * bpu[j] * bpv[i]);
		}

	return p;
}


int figures::generateBezierSurface(std::string patch_file, int tessellation, std::string file_name){

    parsePatchFile(patch_file);
	std::vector<Point> points;

	for (int patch_number = 0; patch_number < number_patches; patch_number++) {

		for (int tessellation_v = 0; tessellation_v < tessellation; tessellation_v++) {

			float v = (float) tessellation_v / tessellation;

			for (int tessellation_u = 0; tessellation_u < tessellation; tessellation_u++) {

				float u = (float) tessellation_u / tessellation;
				/* first triangle */
				points.push_back(bezierPoint(patch_number, u, v));
				points.push_back(bezierPoint(patch_number, (u + (1.0f / tessellation)), v));
				points.push_back(bezierPoint(patch_number, (u + (1.0f / tessellation)), (v + (1.0f / tessellation))));

				/* second triangle */
				points.push_back(bezierPoint(patch_number, (u + (1.0f / tessellation)), (v + (1.0f / tessellation))));
				points.push_back(bezierPoint(patch_number, u, (v + (1.0f / tessellation))));
				points.push_back(bezierPoint(patch_number, u, v));
			}
		}
    }

    int res = write_in_file(points, file_name);

    // free memory allocated in readPatch
	free(patches);
    free(control_points);

    return res;
}
