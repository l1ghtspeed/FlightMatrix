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

string decToBin(int digit){
	if(digit == 0)return "00000";
	string binary = "";

	while(digit > 0){
	    binary += to_string((digit%2));
		digit /= 2;
	}

	reverse(binary.begin(),binary.end());
	binary = "0000" + binary;
	binary = binary.substr(binary.length()-5);

	return binary;
}


void drawIP(string ipAddress){
	short purple[3] = {128,0,128};
	short yellow[3] = {255,255,0};
	short blue[3] = {0,0,255};

	if(ipAddress.substr(0,8) != "192.168."){
		for(int i = 0; i<64; i++){
			//canvas->SetPixel(i,0,purple[0],purple[1],purple[2]);
			cout << "rip" << endl;
		}
	}else{
		ipAddress = ipAddress.substr(8);
		short start = ipAddress.find(".");
		short ind = 0;
		int seperation[7] = {5,4,4,8,4,4,5};
		string bin = "";

		string num = "00" + ipAddress.substr(0,start);
		string num2 = "00" + ipAddress.substr(start+1);
		num = num.substr(num.length()-3) + num2.substr(num2.length()-3);

		start = 0;
		
		for (int i = 0; i<13; i++){
			if(i%2 == 0){ //draw spacers
				for(int j = start; j < start + seperation[(int)(i/2)]; j++){
					//canvas->SetPixel(j,0,blue[0],blue[1],blue[2]);
					cout << "-";
				}
				start += seperation[i];
			}else{ //draw ip digits
				bin = decToBin((int)num.at(ind)-48);
				ind++;
				
				for(int j = start; j < start + 5; j++){
					if(bin.at(j-start) == '0'){
						cout << "0";
					}else{
						cout << "1";
					}	
				}
				start += 5;
			}
		}
	}

}
int main(int argc, char* argv[]){
	drawIP("192.168.141.101");
	//cout << decToBin(0) << endl;
	return 0;
}