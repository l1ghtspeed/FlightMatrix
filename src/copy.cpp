#include "latLongConv.hpp"
#include "led-matrix.h"
#include <stdio.h>
#include <signal.h>
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
	char color = 0;
	while(true){
		if(color == 0)
			color = 100;
		else
			color = 0;
		for(int x = 0; x < 64; x++){
			for(int y = 0; y < 32; y++){
				canvas->SetPixel(x, y, color, 0, 0);
				usleep(1*1000);
			}
		}
	}	
}

int main(int argc, char *argv[]) {
	RGBMatrix::Options defaults;
	defaults.hardware_mapping = "adafruit-hat";
	defaults.rows = 32;
	defaults.cols = 64;
	defaults.chain_length = 1;
	defaults.parallel = 1;
	Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
	if (canvas == NULL) {
		return 1;
	}
	
	//exit when CTRL-C
	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	drawMap(canvas);
	//clear and delete the canvas if interrupt is sent
	canvas -> Clear();
	delete canvas;

	return 0;
};

