#include <iostream>
#include <cmath>
#include "latLongConv.hpp"

using namespace std;

matCoord test(struct geoCoord geo);

int main(int argc, char *argv[])
{
	geoCoord geo;
	while (cin >> geo.lat)
	{
		cin >> geo.lon;
		matCoord mat = test(geo);
		cout << mat.x << " " << mat.y << endl;
	}

	return 0;
}

matCoord test(struct geoCoord geo)
{
	float mapWidth = 64, mapHeight = 32;
	
	matCoord mat;
	mat.x = (geo.lon + 180) * (mapWidth / 360);
	mat.y = (mapHeight / 2) - (mapWidth * (log(tan((M_PI / 4) + ((geo.lat * M_PI / 180) / 2)))) / (2 * M_PI));
	
	return mat;
}
