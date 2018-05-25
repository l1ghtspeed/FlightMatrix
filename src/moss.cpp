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
        if((char) msg.at(read) != 46){
            ipAddress += msg.at(read);
        }
        read++;
    }

    return ipAddress;
}

int main(int argc, char* argv[]){
    string x = getIP("ip.txt");
    cout << x << endl;
    return 0;
}
