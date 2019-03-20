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

    class Translation{
        public:
            float x;
            float y;
            float z;
    };

    class Rotation{
        public:
            float angle;
            float x;
            float y;
            float z;
    };

    class Scale{
        public:
            float x;
            float y;
            float z;
    };

    /**
    * @brief classe que define intancias de Figura
    */
    class Figure{
        public:
            int num_triangles;
            vector<Point> points;
            vector<Translation> translations;
            vector<Rotation> rotations;
            vector<Scale> scales;
    };

}
