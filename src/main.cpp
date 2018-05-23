#include "latLongConv.hpp"
#include "led-matrix.h"
#include <stdio.h>
#include <signal.h>
#include <vector>
#include <time.h>

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

static void drawPlanes(Canvas *canvas,std::vector<matCoord> planes){
	short numPlanes = planes.size();
	for(int i = 0; i < numPlanes; i++){
		canvas->SetPixel(planes.at(i).x,planes.at(i).y,255,0,0);
	}
}

static void drawTime(Canvas* canvas){

	RGBMatrix::Options matrix_options;
	rgb_matrix::RuntimeOptions runtime_opt;

	const char *bdf_font_file = "../fonts/8x13.bdf";
	font.LoadFont(bdf_font_file);

	Color color(255, 255, 0);

	char x_orig = 0;
	char y_orig = 0;
	char letter_spacing = 0;

	rgb_matrix::Font font;

	const char x = x_orig;
	char y = y_orig;

	char[6] time_arr;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	time_arr[0] = (char) tm.tm_hour/10;
	time_arr[1] = (char) tm.tm_hour%10;
	time_arr[2] = ':';
	time_arr[3] = (char) tm.tm_min/10;
	time_arr[4] = (char) tm.tm_min%10;
	time_arr[5] = '/0';

	// The outline font, we need to write with a negative (-2) text-spacing,
	// as we want to have the same letter pitch as the regular text that
	// we then write on top.
	// rgb_matrix::DrawText(canvas, *outline_font,
	// 					x - 1, y + font.baseline(),
	// 					outline_color, &bg_color, line, letter_spacing - 2);

	// The regular text. Unless we already have filled the background with
	// the outline font, we also fill the background here.
	rgb_matrix::DrawText(canvas, font, x, y + font.baseline(),
						color, outline_font ? NULL : &bg_color, line,
						letter_spacing);
	y += font.height();

}

static void drawAirports(Canvas *canvas,vector<matCoord> &airports){
	short numAirports = airports.size();
	for(int i = 0; i < numAirports; i++){
		canvas->SetPixel(airports.at(i).x,airports.at(i).y,0,0,0);
	}
}

static void addAirports(vector<matCoord> &airports){
	matCoord mat;
	mat.x = 47;mat.y = 9;airports.push_back(mat);
	mat.x = 52;mat.y = 8;airports.push_back(mat);
	mat.x = 32;mat.y = 5;airports.push_back(mat);
	mat.x = 47;mat.y = 7;airports.push_back(mat);
	mat.x = 56;mat.y = 9;airports.push_back(mat);
	mat.x = 53;mat.y = 9;airports.push_back(mat);
	mat.x = 32;mat.y = 5;airports.push_back(mat);
	mat.x = 49;mat.y = 9;airports.push_back(mat);
	mat.x = 33;mat.y = 5;airports.push_back(mat);
	mat.x = 52;mat.y = 11;airports.push_back(mat);
}

int main(int argc, char *argv[]) {
	RGBMatrix::Options defaults;
	defaults.hardware_mapping = "adafruit-hat";
	defaults.rows = 32;
	defaults.cols = 64;
	defaults.brightness = 50;
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

	while(!interrupt_recieved){
		drawMap(canvas);
		drawAirports(canvas);
	}
	
	//clear and delete the canvas if interrupt is sent
	canvas -> Clear();
	delete canvas;

	return 0;
};

