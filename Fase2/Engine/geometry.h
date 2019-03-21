#ifndef GEOMETRY_H
#define GEOMETRY_H
#endif

#include <vector>

using namespace std;

namespace geometry{

    /**
    * @brief classe que define intancias de Ponto
    */
    class Point{
        public:
            float x,y,z;
    };

    /**
    * @brief classe que define intancias de Translações
    */
    class Translation{
        public:
            Translation() :empty(true) {}
            bool empty;
            float x,y,z;
    };

    /**
    * @brief classe que define intancias de Rotaçoes
    */
    class Rotation{
        public:
            Rotation() :empty(true) {}
            bool empty;
            float angle,x,y,z;
    };

    /**
    * @brief classe que define intancias de Escalas
    */
    class Scale{
        public:
            Scale() :empty(true) {}
            bool empty;
            float x,y,z;
    };

    /**
    * @brief classe que define intancias de Figura
    */
    class Figure{
        public:
            int num_triangles;
            vector<Point> points;
            Translation translation;
            Rotation rotation;
            Scale scale;
    };

    /**
    * @brief classe que define intancias de Arvores
    */
    class Tree{
        public:
            Figure head_figure;
            vector<Tree> children;
    };

}
