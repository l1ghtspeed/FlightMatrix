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
	//pseduocode for conversion found at: https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection, by Michel Feldheim
	for (int i = 0; i < latLong.size(); i++) {
		matCoord out;
		//convert
		out.x = int((latLong[i].lon + 180.0f)*((float)mapWidth/360));
		float latRad = latLong[i].lat*3.14/180;
		float temp = log(tan((3.14/4)+(latRad/2)));
		out.y = int((mapHeight/2)-(mapWidth*temp/(2*3.14)));
		out.y = abs(out.y);
		//add processed coords to planes vector
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
