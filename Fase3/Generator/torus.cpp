#include "figures.h"
#include <vector>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace figures;
using namespace std;

int figures::generateTorus(float innerRadius, float outerRadius, int nsides, int nrings, string file_name) {
    int nPoints = 0;
    float deltaPhi, deltaTheta;
    float phi, theta, nextPhi, nextTheta;
    float cosPhi, cosTheta, sinPhi, sinTheta;
    float cosNextPhi, cosNextTheta, sinNextPhi, sinNextTheta;

    vector<Point> points;

    deltaPhi = 2.0f * M_PI / nrings;
    deltaTheta = 2.0f * M_PI / nsides;

    for (int i = 0; i < nrings; i++) {
        phi = i * deltaPhi;
        nextPhi = (i + 1) * deltaPhi;
        cosPhi = cos(phi);
        sinPhi = sin(phi);
        cosNextPhi = cos(nextPhi);
        sinNextPhi = sin(nextPhi);

        for (int j = 0; j < nsides; j++, nPoints += 6) {
            float dXZ, nextDXZ;

            theta = j * deltaTheta;
            nextTheta = (j + 1) * deltaTheta;
            cosTheta = cos(theta);
            sinTheta = sin(theta);
            cosNextTheta = cos(nextTheta);
            sinNextTheta = sin(nextTheta);
            dXZ = outerRadius + innerRadius * cosTheta;
            nextDXZ = outerRadius + innerRadius * cosNextTheta;

			points.push_back(Point(nextDXZ * cosPhi, innerRadius * sinNextTheta, nextDXZ * sinPhi));
            points.push_back(Point(dXZ * cosNextPhi, innerRadius * sinTheta, dXZ * sinNextPhi));
            points.push_back(Point(dXZ * cosPhi, innerRadius * sinTheta, dXZ * sinPhi));

            points.push_back(Point(nextDXZ * cosNextPhi, innerRadius * sinNextTheta, nextDXZ * sinNextPhi));
			points.push_back(Point(dXZ * cosNextPhi, innerRadius * sinTheta, dXZ * sinNextPhi));
			points.push_back(Point(nextDXZ * cosPhi, innerRadius * sinNextTheta, nextDXZ * sinPhi));
        }
    }

    int res = write_in_file(points, file_name);
    return res;
}
