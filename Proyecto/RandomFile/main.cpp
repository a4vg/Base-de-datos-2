#include <iostream>
#include <thread>
#include "RandomFile.h"

using namespace std;


int main(int argc, char const *argv[])
{    
    RandomFile myfile("modelos.dat");

    thread threads[5];
    for (int i=0; i<5; ++i){
        threads[i] = thread(RandomFile::insertRecord, myfile, "colchon inflable, drimer, 2 plazas");
    }

    for (int i=0; i<5; ++i) threads[i].join();
}

