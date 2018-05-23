#include "videoMash.hpp"
#include <cmath>
#include <ifstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>

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
		struct out;
		//convert
		out.x = int((latLong[i].lon + 180)*(mapWidth/360));
		float latRad = latLong[i].lat*PI/180;
		float temp = log(tan((PI/4)+(latRad/2)));
		out.y = int((mapHeight/2)-(mapWidth*temp/(2*PI)));
		//add processed coords to planes vector
		planes.push_back(out);
	}
}

void getCoords(vector<geoCoord> &latLong) {
	ifstream in;
	int space;
	in.open("out.txt");
	string plane;

	while (in >> plane) {
		geoCoord cord;
		//delimit string by " "
		space = plane.find(" ");
		//convert strings to floats	
		cord.lat = atof(plane.substr(0, space));
		cord.lat = atof(plane.substr(space + 1));
		latLong.push_back(cord);
	}
	
	in.close();
}