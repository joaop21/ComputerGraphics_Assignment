#include <string>
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

	if(primitive == "plane"){
		int side = atoi(argv[2]);
		string file_name = argv[3];
		int res = generatePlane(side,file_name);
		// testar o res
		return 0;
	} else if(primitive == "box"){
		// fazer cenas
	} else if(primitive == "sphere"){
		// fazer cenas
	} else if(primitive == "cone"){
		// fazer cenas
	} else{
		printf("Parâmetros inválidos!!!\n");
		return 0;
	}

}
