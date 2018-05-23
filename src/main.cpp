#include "latLongConv.hpp"
#include "led-matrix.h"
#include <stdio.h>
#include <signal.h>
#include <vector>
#include <unistd.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//interrupt and interrupt handling setup
volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
	interrupt_received = true;
}

static void drawMap(Canvas *canvas) {
	const short blue[3] = {0,0,255};
	const short green[3] = {0,255,0};

	for(int i = 0; i < 32; i++){
		for(int j = 0; j < 64; j++){
			if(initMap[i][j] == 1){
				canvas->SetPixel(j,i,green[0],green[1],green[2]);
			}else{
				canvas->SetPixel(j,i,blue[0],blue[1],blue[2]);
			}
			
		}
	}
}

static void drawPlanes(Canvas *canvas,std::vector<matCoord> &planes){
	short numPlanes = planes.size();
	for(int i = 0; i < numPlanes; i++){
		canvas->SetPixel(planes.at(i).x,planes.at(i).y,255,0,0);
	}
}

int main(int argc, char *argv[]) {
	RGBMatrix::Options defaults;
	defaults.hardware_mapping = "adafruit-hat";
	defaults.rows = 32;
	defaults.cols = 64;
	defaults.chain_length = 1;
	defaults.parallel = 1;
	defaults.brightness=50;
	Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
	if (canvas == NULL) {
		return 1;
	}
	
	//exit when CTRL-C
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);
	std::vector<matCoord> planes;
	while(!interrupt_received){
	drawMap(canvas);
	getPlaneCoord(planes);
	drawPlanes(canvas, planes);
	usleep(100000);
	}
	//clear and delete the canvas if interrupt is sent
	canvas -> Clear();
	delete canvas;

	return 0;
};

