#include <iostream>
#include <cmath>
#include "latLongConv.hpp"

int main(int argc, char *argv[])
{
	struct geoCoord geo = { .x = 50, .y = 120 }
	struct matCoord mat = test(geo);
	cout << mat.x << " " << mat.y << endl;

	return 0;
}

struct matCoord test(struct geoCoord geo)
{
	int mapWidth = 200, mapHeight = 100;
	struct matCoord mat = { .x = (longitude + 180) * (mapWidth / 360), .y = (mapHeight / 2) - (mapWidth * (log(tan((PI / 4) + (latRad / 2)))) / (2 * PI)) };
	
	return mat;
}
