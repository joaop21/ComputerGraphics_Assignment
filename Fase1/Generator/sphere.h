#ifndef SPHERE_H
#define SPHERE_H
#endif

#define _USE_MATH_DEFINES
#include <math.h>

/**
*  @brief Função que gera o pontos para a realização dos devidos triângulos, e
* conseguentemente gravação em ficheiro.
*
*  @param r - parâmetro que é o raio da esfera
*  @param slices - parâmetro que é o numero de fatias da esfera
*  @param stacks - parâmetro que é o número de partições de cada slice
*  @param file_name - parâmetro que é o nome do ficheiro onde se devem gravar os
* pontos e triangulos gerados.
*
*  Para que o algoritmo ficasse mais percetível e mais curto usamos abreviações
* nas variáveis, tal correspondência é feita de seguida:
*   - r : radius
*   - sls : SliceStep
*   - sts : StackStep
*   - rs : raio da stack atual
*   - rsn : raio da stack seguinte
*
*  @returns Integer que dita se a geração foi um sucesso ou não
*/

int generateSphere(float r, int slices, int stacks, string file_name){
	std::vector<Point> points;

	float sls = 2*M_PI / slices; // algulo entre cada slice (sliceStep)
	float sts = M_PI / stacks;	 // algulo entre cada stack (stackStep)

	for(int i = 0 ; i < stacks ; i++ ){
		float beta = i*sts;  // angulo que a stack atual faz com o eixo do Y
		float next_beta = (i+1)*sts; // angulo que a stack a seguir faz com o eixo do Y
		float rs = r*sin(beta); // raio stack (atual)
		float rsn = r*sin(next_beta); // raio da stack seguinte
		for(int j = 0 ; j < slices ; j++){
			float alfa = j*sls; // angulo que a slice atual faz com o eixo do X
			float next_alfa = (j+1)*sls; // angulo que a slice seguinte faz com o eixo do X
			points.push_back(Point(rs*cos(alfa), r*cos(beta), rs*sin(alfa)));
			points.push_back(Point(rsn*cos(next_alfa), r*cos(next_beta), rsn*sin(next_alfa)));
			points.push_back(Point(rsn*cos(alfa), r*cos(next_beta), rsn*sin(alfa)));

			points.push_back(Point(rs*cos(next_alfa), r*cos(beta), rs*sin(next_alfa)));
			points.push_back(Point(rsn*cos(next_alfa), r*cos(next_beta), rsn*sin(next_alfa)));
			points.push_back(Point(rs*cos(alfa), r*cos(beta), rs*sin(alfa)));
		}
	}

	int res = write_in_file(points, file_name);
	return res;
}
