#ifndef WRITEFILE_H
#define WRITEFILE_H
#endif

#define _USE_MATH_DEFINES
#include <math.h>

int write_in_file(vector<Point> points, string file_name){
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
