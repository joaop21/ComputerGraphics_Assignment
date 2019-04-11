#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "figures.h"

using namespace figures;
using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Parâmetros inválidos!!!\n");
		return 0;
	}

	string primitive = argv[1];
	int res = 0;
	if(primitive == "plane"){
		float side = atof(argv[2]);
		string file_name = argv[3];
		res = generatePlane(side,file_name);
	} else if(primitive == "box"){
		float xdim = atof(argv[2]);
		float ydim = atof(argv[3]);
		float zdim = atof(argv[4]);
		if(argc==6){
			int divisions = 1;
			string file_name = argv[5];
			res = generateBox(xdim,ydim,zdim,divisions,file_name);
		}
		else if(argc==7){
			int divisions = atoi(argv[5]);
			string file_name = argv[6];
			res = generateBox(xdim,ydim,zdim,divisions,file_name);
		}
	} else if(primitive == "sphere"){
		float radius = atof(argv[2]);
		int slices = atoi(argv[3]);
		int stacks = atoi(argv[4]);
		string file_name = argv[5];
		if(slices < 3)
			printf("O mínimo de slices possível é 3.\n");
		else if(stacks < 2)
			printf("O mínimo de stacks possível é 2.\n");
		else
			res = generateSphere(radius,slices,stacks,file_name);
	} else if(primitive == "cone"){
		float bottom_radius = atof(argv[2]);
		float height = atof(argv[3]);
		int slices = atoi(argv[4]);
		int stacks = atoi(argv[5]);
		string file_name = argv[6];
		res = generateCone(bottom_radius, height, slices, stacks, file_name);
	} else if(primitive == "asteroid_belt"){
		int num_asteroids = atoi(argv[2]);
		int min_radius = atoi(argv[3]);
		int max_radius = atoi(argv[4]);
		string file_name = argv[5];
		res = generateAsteroids(num_asteroids,min_radius,max_radius,file_name);
	} else if(primitive == "torus"){
		float innerRadius = atof(argv[2]);
		float outerRadius = atof(argv[3]);
		int nsides = atoi(argv[4]);
		int nrings = atoi(argv[5]);
		string file_name = argv[6];
		res = generateTorus(innerRadius,outerRadius,nsides,nrings,file_name);
	}else if(primitive == "bezier"){
		string patch_file = argv[2];
		int tessellation = atoi(argv[3]);
		string file_name = argv[4];
		res = generateBezierSurface(patch_file,tessellation,file_name);
	}else{
		printf("Parâmetros inválidos!!!\n");
		return 0;
	}

	// testa se correu tudo bem
	if(res == 1){
		printf("Tudo gerado corretamente.\n" );
		return 1;
	}else{
		printf("Algo correu mal.\n" );
		return 0;
	}

}
