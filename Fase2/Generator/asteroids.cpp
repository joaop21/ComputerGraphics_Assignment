#include "figures.h"
#include <vector>
#include <string>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace figures;
using namespace std;

int figures::generateAsteroids(int num_asteroids, int min_radius, int max_radius, std::string file_name){

    ofstream file ("../Generated_Models/" + file_name);
  	if (file.is_open()){
        srand(1);

        for(int i = 0 ; i < num_asteroids ; i++){
            file << "<group>\n";
            while(true){
    			int x = rand()%(2*max_radius)-max_radius;
    			int z = rand()%(2*max_radius)-max_radius;
    			float hipotenusa = sqrt(pow(abs(x),2) + pow(abs(z),2));
    			if((hipotenusa >= min_radius) && (hipotenusa <= max_radius)){
    				file << "    <translate X=\"" + to_string(x) + "\" Z=\"" + to_string(z) + "\" />\n";
                    file << "    <models>\n        <model file=\"asteroid.3d\" R=\"0.412\" G=\"0.388\" B=\"0.376\" />\n    </models>";
                    file << "\n</group>\n";
    				break;
    			}
    		}
        }

        return 1;
    } else return 0;
}
