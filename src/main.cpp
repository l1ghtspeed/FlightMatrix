#include "latLongConv.hpp"
#include "led-matrix.h"
#include <stdio.h>
#include <signal.h>
#include <vector>
#include <time.h>
#include "graphics.h"
#include <cassert>
#include <unistd.h>

using namespace std;
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

	rgb_matrix::Font font;

	const char *bdf_font_file = "../fonts/4x6.bdf";
	font.LoadFont(bdf_font_file);
	rgb_matrix::Color bg_color(0, 0, 255);
	rgb_matrix::Color color(255, 255, 255);

	char x_orig = 1;
	char y_orig = 26;
	char letter_spacing = 0;

	char x = x_orig;
	char y = y_orig;

	char time_arr[5];
	
	time_t t = time(NULL);
	struct tm tme = *localtime(&t);

	time_arr[0] = (char) ((tme.tm_hour-4 < 0)?24-(tme.tm_hour-4):tme.tm_hour-4)/10 + 48;
	time_arr[1] = (char) ((tme.tm_hour-4 < 0)?24-(tme.tm_hour-4):tme.tm_hour-4)%10 + 48;
	time_arr[2] = ':';
	time_arr[3] = (char) tme.tm_min/10 + 48;
	time_arr[4] = (char) tme.tm_min%10 + 48;
	//time_arr[5] = '/0';

	// The outline font, we need to write with a negative (-2) text-spacing,
	// as we want to have the same letter pitch as the regular text that
	// we then write on top.
	// rgb_matrix::DrawText(canvas, *outline_font,
	// 					x - 1, y + font.baseline(),
	// 					outline_color, &bg_color, line, letter_spacing - 2);

	// The regular text. Unless we already have filled the background with
	// the outline font, we also fill the background here.
	rgb_matrix::DrawText(canvas, font, x, y + font.baseline(),color, &bg_color ,time_arr,-1);

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
	mat.x = 8;mat.y = 13;airports.push_back(mat);
	mat.x = 14;mat.y = 11;airports.push_back(mat);
	mat.x = 15;mat.y = 13;airports.push_back(mat);
	mat.x = 18;mat.y = 11;airports.push_back(mat);
<<<<<<< HEAD
	mat.x = 58;mat.y = 13;airports.push_back(mat);
	mat.x = 12;mat.y = 13;airports.push_back(mat);
	mat.x = 34;mat.y = 9;airports.push_back(mat);
	mat.x = 16;mat.y = 13;airports.push_back(mat);
	mat.x = 35;mat.y = 9;airports.push_back(mat);
	mat.x = 54;mat.y = 15;airports.push_back(mat);
=======
	mat.x = 32;mat.y = 12;airports.push_back(mat);
	mat.x = 33;mat.y = 15;airports.push_back(mat);
	mat.x = 35;mat.y = 16;airports.push_back(mat);
	mat.x = 16;mat.y = 13;airports.push_back(mat);
	mat.x = 35;mat.y = 9;airports.push_back(mat);
	mat.x = 52;mat.y = 15;airports.push_back(mat);
	mat.x = 50;mat.y = 18;airports.push_back(mat);
	mat.x = 56;mat.y = 14;airports.push_back(mat);
	mat.x = 37;mat.y = 14;airports.push_back(mat);
	mat.x = 42;mat.y = 12;airports.push_back(mat);
	mat.x = 56;mat.y = 21;airports.push_back(mat);
	mat.x = 47;mat.y = 14;airports.push_back(mat);
>>>>>>> b20f0cdc961859e04771a81eaea06b1b70c9035a
}

int main(int argc, char *argv[]) {
	RGBMatrix::Options defaults;
	vector<matCoord> airports, planes;
	addAirports(airports);
	defaults.hardware_mapping = "adafruit-hat";
	defaults.rows = 32;
	defaults.cols = 64;
	defaults.brightness = 25;
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

	while(!interrupt_received){
		drawMap(canvas);
		drawTime(canvas);
		drawAirports(canvas,airports);
		getPlaneCoord(planes);
		drawPlanes(canvas, planes);
		usleep(10000000);
	}
	
	//clear and delete the canvas if interrupt is sent
	canvas -> Clear();
	delete canvas;

	return 0;
};

