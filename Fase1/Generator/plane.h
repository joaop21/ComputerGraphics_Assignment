#ifndef PLANE_H
#define PLANE_H
#endif

#include <iostream>
#include <fstream>

/**
*  @brief Função que gera o pontos para a realização dos devidos triângulos, e
* conseguentemente gravação em ficheiro.
*
*  @param side - parâmetro que é o tamanho do lado do plano.
*  @param file_name - parâmetro que é o nome do ficheiro onde se devem gravar os
* pontos e triangulos gerados.
*
*/
int generatePlane(float side, string file_name){
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

	// necessário operações sobre ficheiros
	ofstream file ("../Genarated_Models/" + file_name);
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
