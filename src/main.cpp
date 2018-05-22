#include "latlongConv.hpp"
#include "led-matrix.h"
#include <stdio.h>
#include <signal.h>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//interrupt and interrupt handling setup
volatile bool interrupt_received = flase;
static void InterruptHandler(int signo) {
	interrupt_received = true;
}

static void drawMap(Canvas *canvas) {
	
}

int main(int argc, char *argv[]) {
	RGBMatrix::Options defaults;
	defaults.harware_mapping = "adafruit-hat";
	defaults.rows = 32;
	defaults.columns = 64;
	defaults.chain_length = 1;
	defaults.parallel = 1;
	defaults.show_refresh_rate_rate = true;
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

