#include "videoMash.hpp"
#include <cmath>

matCoord covertCoord(geoCoord latLong) {
	//latitude, longitude
	matCoord out;
	int mapWidth = 64;
	int mapHeight = 32;
	int latRad = matCoord.x*PI/180;
	out.x = int((geoCoord.lat + 180)*(mapWidth/360));
	float temp = log(tan((PI/4)+(latRad/2)));
	out.y = int((mapHeight/2)-(mapWidth*temp/(2*PI)));
	return out;
}