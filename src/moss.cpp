#include <stdio.h>
#include <iostream>
#include "stdlib.h"
#include <string>
#include <fstream>
#include <cassert>

using namespace std;
string getIP(string file_name){
    ifstream f;
    f.open(file_name);
    string msg;
    short read = 5;
    string ipAddress = "";

    getline(f,msg);
    assert(msg.length());
    
    while((char) msg.at(read) != 32){
        ipAddress += msg.at(read);
        read++;
    }

    return ipAddress;
}

string decToBin(char digit){
	string binary = "";
	while(!digit){
		binary += (char)digit%2;
		binary /= 2;
	}
	return binary;
}

void drawIP(Canvas * canvas, string ipAddress){
	short len = ipAddress.length();
	short start = 0;
	short ind = 9;
	string out = "";
	char digits[6];

    while(ipAddress.at(start) != 32){
        start++;
    }

    for(int i = 0; i<6; i++){
        if(i<(3-start)){
            digits[i] = 0;
        }else{

        }
    }

	short purple[3] = {128,0,128};
	short yellow[3] = {255,255,0};
	short blue[3] = {0,0,255};

	short seperation[7] = {5,4,4,8,4,4,5}

	if(ipAddress.substr(0,8) != "192.168."){
		for(int i = 0; i<64; i++){
			canvas->SetPixel(i,0,purple[0],purple[1],purple[2]);
		}
	}else{
		
		for (int i = 0; i<13; i++){
			if(!i%2){ 
				for(int j = start; j < (int)(seperation/2); j++){
					canvas->SetPixel(j,0,blue[0],blue[1],blue[2]);
				}
				start += seperation[i];
			}else{
				out = decToBin(ipAddress.at(ind));
				for(int j = start; j < start + 5; j++){
					canvas->SetPixel(j,0,blue[0],blue[1],blue[2]);
				}
				start += 5;
			}
		}
	}

}