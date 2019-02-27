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
		// fazer cenas
	} else if(primitive == "sphere"){
		// fazer cenas
	} else if(primitive == "cone"){
		// fazer cenas
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
