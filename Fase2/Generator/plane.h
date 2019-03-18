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
*  @returns Integer que dita se a geração foi um sucesso ou não
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

	int res = write_in_file(points, file_name);
	return res;
}
