#ifndef FIGURE_H
#define FIGURE_H
#endif

using namespace std;
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
