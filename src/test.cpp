#include <iostream>
#include <cmath>
#include "latLongConv.hpp"

using namespace std;

matCoord test(struct geoCoord geo);

int main(int argc, char *argv[])
{
	geoCoord geo;
	geo.lat = 120;
	geo.lon = 50;
	matCoord mat = test(geo);
	cout << mat.x << " " << mat.y << endl;

	return 0;
}

matCoord test(struct geoCoord geo)
{
	int mapWidth = 200, mapHeight = 100;
	
	matCoord mat;
	mat.x = (geo.lon + 180) * (mapWidth / 360);
	mat.y = (mapHeight / 2) - (mapWidth * (log(tan((M_PI / 4) + ((geo.lat * M_PI / 180) / 2)))) / (2 * M_PI));
	
	return mat;
}
