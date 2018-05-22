#ifndef LAT_LONG_CONV_H
#define LAT_LONG_CONV_H

//coordinate structure for (lat, long)
struct geoCoord {
	float x;
	float y;
}

struct matCoord {
	int x;
	int y;
}
//Convert latitude and longitude to x,y coordinates (an R^2 -> R^2 mapping) for a 32 x 64 led matrix (Mercator projection)

matCoord covertCoord(geoCoord latLong);

#endif
