#include "figures.h"
#include <vector>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace figures;
using namespace std;

int figures::write_in_file(std::vector<Point> points, std::string file_name){
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

int figures::write_in_file(std::vector<Point> points, std::vector<Point> normals, std::vector<TexturePoint> textures, std::string file_name){
	// necessário operações sobre ficheiros
	ofstream file ("../Generated_Models/" + file_name);
  	if (file.is_open()){

		// no inicio escrevem-se o numero de triangulos existente no ficheiro
		int num_points = points.size();
	    file << to_string(num_points / 3) + "\n";

		// escrita dos pontos no ficheiro
		for(int i = 0 ; i < num_points ; i++){
			Point vertex = points[i];
			Point vertex_normal = normals[i];
			TexturePoint vertex_texture = textures[i];

			file << to_string(vertex.getX()) + " " +
					to_string(vertex.getY()) + " " +
					to_string(vertex.getZ()) + "\n";

			file << to_string(vertex_normal.getX()) + " " +
					to_string(vertex_normal.getY()) + " " +
					to_string(vertex_normal.getZ()) + "\n";

			file << to_string(vertex_texture.getX()) + " " +
					to_string(vertex_texture.getY()) + "\n";
		}
	    file.close();
		return 1;
    } else return 0;
}
