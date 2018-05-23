#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "latLongConv.hpp"

using namespace std;

void getPlaneCoord(vector<matCoord> &planes) {
	//latitude, longitude
	int mapWidth = 64;
	int mapHeight = 32;
	vector<geoCoord> latLong;
	//get coordinates
	getCoords(latLong);
	//process and convert
	for (int i = 0; i < latLong.size(); i++) {
		matCoord out;
		out.x = int((float)(latLong[i].lat + 180.0f) * ((float)mapWidth/360.0f));
		out.y = int(((float)(latLong[i].lon * -1) + 90.0f) * ((float)mapHeight/180.0f));
		out.y += 4;
		planes.push_back(out);
	}
}

void getCoords(vector<geoCoord> &latLong) {
	ifstream in;
	int space;
	in.open("out.txt");
	string plane;

	while (getline(in, plane)) {
		geoCoord cord;
		//delimit string by " "
		space = plane.find(" ");
		//convert strings to floats	
		cord.lat = atof(plane.substr(0, space).c_str());
		cord.lon = atof(plane.substr(space + 1).c_str());
		latLong.push_back(cord);
	}
	
	in.close();
}
