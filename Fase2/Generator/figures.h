#ifndef FIGURES_H
#define FIGURES_H
#endif

#include <string>

namespace figures{
    /**
    * @brief classe que define intancias de Ponto
    */
    class Point{
        private:
            float x,y,z;
        public:
            Point(){
                x = 0;
                y = 0;
                z = 0;
            }
            Point(float xn, float yn, float zn){
                x = xn;
                y = yn;
                z = zn;
            }
            float getX(){return x;}
            float getY(){return y;}
            float getZ(){return z;}
    };

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
    int generatePlane(float side, std::string file_name);

    /**
    *  @brief Função que gera o pontos para a realização dos devidos triângulos, e
    * conseguentemente gravação em ficheiro.
    *
    *  @param xdim - parâmetro que é o tamanho da dimensão X.
    *  @param ydim - parâmetro que é o tamanho da dimensão Y.
    *  @param zdim - parâmetro que é o tamanho da dimensão Z.
    *  @param div - parâmetro que é o números de divisões na box.
    *  @param file_name - parâmetro que é o nome do ficheiro onde se devem gravar os
    * pontos e triangulos gerados.
    *
    *  @returns Integer que dita se a geração foi um sucesso ou não
    */
    int generateBox(float xdim, float ydim, float zdim, int div, std::string file_name);

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

    int generateSphere(float r, int slices, int stacks, std::string file_name);

    /**
    *  @brief Função que gera o pontos para a realização dos devidos triângulos, e
    * conseguentemente gravação em ficheiro.
    *
    *  @param bottom_radius - parâmetro que é o raio da base do cone.
    *  @param height - parâmetro que é o tamanho do cone.
    *  @param slices - parâmetro que é o número de fatias em que o cone se deve dividir.
    *  @param stacks - parâmetro que é o números de divisões de cada slice.
    *  @param file_name - parâmetro que é o nome do ficheiro onde se devem gravar os
    * pontos e triangulos gerados.
    *
    *  @returns Integer que dita se a geração foi um sucesso ou não
    */

    int generateCone(float bottom_radius, float height, int slices, int stacks, std::string file_name);

    int write_in_file(std::vector<Point> points, std::string file_name);

}
