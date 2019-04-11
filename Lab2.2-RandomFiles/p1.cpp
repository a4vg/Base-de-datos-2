#ifndef P1_CPP
#define P1_CPP

#include <iostream>
#include <iomanip>

#include "RandomFile.h"

using namespace std;

int main(){
    srand(time(0));

    RandomFile r("datos.txt");
    r.testIndex();

    
    return EXIT_SUCCESS;
}

#endif
