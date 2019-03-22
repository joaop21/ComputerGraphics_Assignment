#include "figures.h"
#include <vector>

using namespace figures;

int figures::generateBox(float xdim, float ydim, float zdim, int div, std::string file_name){
	std::vector<Point> points;

	float tam_x = xdim / div;
	float tam_y = ydim / div;
	float tam_z = zdim / div;

	float z = zdim/2;
	// faces paralelas a XY
	for(int i = 0; i < div ; i++){
		float x = -(xdim/2);
		for(int j = 0 ; j < div ; j++){
			points.push_back(Point((x+tam_x),(i+1)*tam_y,z));
			points.push_back(Point(x,i*tam_y,z));
			points.push_back(Point((x+tam_x),i*tam_y,z));

			points.push_back(Point(x,(i+1)*tam_y,z));
			points.push_back(Point(x,i*tam_y,z));
			points.push_back(Point((x+tam_x),(i+1)*tam_y,z));

			points.push_back(Point((x+tam_x),(i+1)*tam_y,-z));
			points.push_back(Point((x+tam_x),i*tam_y,-z));
			points.push_back(Point(x,i*tam_y,-z));

			points.push_back(Point(x,(i+1)*tam_y,-z));
			points.push_back(Point((x+tam_x),(i+1)*tam_y,-z));
			points.push_back(Point(x,i*tam_y,-z));
			x+=tam_x;
		}
	}

	float x = xdim/2;
	// faces paralelas a ZY
	for(int i = 0; i < div ; i++){
		float z = zdim/2;
		for(int j = 0 ; j < div ; j++){
			points.push_back(Point(x,(i+1)*tam_y,(z-tam_z)));
			points.push_back(Point(x,i*tam_y,z));
			points.push_back(Point(x,i*tam_y,(z-tam_z)));

			points.push_back(Point(x,(i+1)*tam_y,z));
			points.push_back(Point(x,i*tam_y,z));
			points.push_back(Point(x,(i+1)*tam_y,(z-tam_z)));

			points.push_back(Point(-x,(i+1)*tam_y,(z-tam_z)));
			points.push_back(Point(-x,i*tam_y,(z-tam_z)));
			points.push_back(Point(-x,i*tam_y,z));

			points.push_back(Point(-x,(i+1)*tam_y,z));
			points.push_back(Point(-x,(i+1)*tam_y,(z-tam_z)));
			points.push_back(Point(-x,i*tam_y,z));
			z-=tam_z;
		}
	}

	z = zdim/2;
	// faces paralelas a ZX
	for(int i = 0; i < div ; i++){
		x = -(xdim/2);
		float y = ydim;
		for(int j = 0 ; j < div ; j++){
			points.push_back(Point((x+tam_x),y,(z-tam_z)));
			points.push_back(Point(x,y,z));
			points.push_back(Point((x+tam_x),y,z));

			points.push_back(Point(x,y,(z-tam_z)));
			points.push_back(Point(x,y,z));
			points.push_back(Point((x+tam_x),y,(z-tam_z)));

			points.push_back(Point((x+tam_x),0,(z-tam_z)));
			points.push_back(Point((x+tam_x),0,z));
			points.push_back(Point(x,0,z));

			points.push_back(Point(x,0,(z-tam_z)));
			points.push_back(Point((x+tam_x),0,(z-tam_z)));
			points.push_back(Point(x,0,z));
			x+=tam_x;
		}
		z-=tam_z;
	}

	int res = write_in_file(points, file_name);
	return res;
}
