#include <string>
#include "point.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Parâmetros inválidos!!!\n");
		return 0;
	}

	string primitive = argv[1];

	if(primitive == "plane"){
		// fazer cenas
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
