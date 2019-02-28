#ifndef BOX_H
#define BOX_H
#endif

#include <iostream>
#include <fstream>

/**
*  @brief Função que gera o pontos para a realização dos devidos triângulos, e
* conseguentemente gravação em ficheiro.
*
*  @param xdim - parâmetro que é o tamanho da dimensão X.
*	 @param ydim - parâmetro que é o tamanho da dimensão Y.
*  @param zdim - parâmetro que é o tamanho da dimensão Z.
*  @param div - parâmetro que é o números de divisões na box.
*  @param file_name - parâmetro que é o nome do ficheiro onde se devem gravar os
* pontos e triangulos gerados.
*
*/
int generateBox(float xdim, float ydim, float zdim, int div, string file_name){
	std::vector<Point> points;

	// primeiro triangulo base (não se pode ver)
	points.push_back(Point(-xdim, 0.0, zdim));
	points.push_back(Point(-xdim, 0.0, -zdim));
	points.push_back(Point(xdim, 0.0, -zdim));

	// segundo triangulo base (não se pode ver)
	points.push_back(Point(xdim, 0.0, -zdim));
	points.push_back(Point(xdim, 0.0, zdim));
	points.push_back(Point(-xdim, 0.0, zdim));

	// primeiro triangulo topo
	points.push_back(Point(xdim, ydim, -zdim));
	points.push_back(Point(-xdim, ydim, -zdim));
	points.push_back(Point(-xdim, ydim, zdim));

	// segundo triangulo topo
	points.push_back(Point(xdim, ydim, -zdim));
	points.push_back(Point(-xdim, ydim, zdim));
	points.push_back(Point(xdim, ydim, zdim));


	// primeiro triangulo eixo OZ
	points.push_back(Point(xdim, 0.0, zdim));
	points.push_back(Point(xdim, ydim, zdim));
	points.push_back(Point(-xdim, 0.0, zdim));

	// segundo triangulo eixo OZ
	points.push_back(Point(xdim, ydim, zdim));
	points.push_back(Point(-xdim, ydim, zdim));
	points.push_back(Point(-xdim, 0.0, zdim));

	// primeiro triangulo eixo OZ negativo (não se pode ver)
	points.push_back(Point(-xdim, ydim, -zdim));
	points.push_back(Point(xdim, ydim, -zdim));
	points.push_back(Point(xdim, 0.0, -zdim));

	// segundo triangulo eixo OZ negativo (não se pode ver)
	points.push_back(Point(xdim, 0.0, -zdim));
	points.push_back(Point(-xdim, 0.0, -zdim));
	points.push_back(Point(-xdim, ydim, -zdim));


	// primeiro triangulo eixo OX
	points.push_back(Point(xdim, 0.0, -zdim));
	points.push_back(Point(xdim, ydim, -zdim));
	points.push_back(Point(xdim, ydim, zdim));

	// segundo triangulo eixo OX
	points.push_back(Point(xdim, 0.0, -zdim));
	points.push_back(Point(xdim, ydim, zdim));
	points.push_back(Point(xdim, 0.0, zdim));

	// primeiro triangulo eixo OX negativo (não se pode ver)
	points.push_back(Point(-xdim, ydim, zdim));
	points.push_back(Point(-xdim, ydim, -zdim));
	points.push_back(Point(-xdim, 0.0, -zdim));

	// segundo triangulo eixo OX negativo (não se pode ver)
	points.push_back(Point(-xdim, ydim, zdim));
	points.push_back(Point(-xdim, 0.0, -zdim));
	points.push_back(Point(-xdim, 0.0, zdim));


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
