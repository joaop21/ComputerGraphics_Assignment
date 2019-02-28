#include <string>
#include <vector>
#include "point.h"
#include "plane.h"
#include "box.h"
#include "sphere.h"
#include "cone.h"

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
		// fazer cenas
	} else if(primitive == "cone"){
		float bottom_radius = atof(argv[2]);
		float height = atof(argv[3]);
		int slices = atoi(argv[4]);
		int stacks = atoi(argv[5]);
		string file_name = argv[6];
		res = generateCone(bottom_radius, height, slices, stacks, file_name);
	} else{
		printf("Parâmetros inválidos!!!\n");
		return 0;
	}

	if(res == 1){
		printf("Tudo gerado corretamente.\n" );
		return 1;
	}else{
		printf("Algo correu mal.\n" );
		return 0;
	}

}
