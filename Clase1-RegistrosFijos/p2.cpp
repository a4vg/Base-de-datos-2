#ifndef P1_CPP
#define P1_CPP

#include <iostream>
#include <iomanip>

#include "Aula.h"
#include "Alumno.h"

using namespace std;

int main(){
    Aula aulita((char*) "./datos.txt");

    for (Alumno& a: aulita.load()){
        a.print();
    };

    Alumno nuevoa("Andrea", "Velasquez", "Gushiken", "Computacion", 5, 2000);
    aulita.add(nuevoa);
    
    aulita.erase(2);
    
    return EXIT_SUCCESS;
}

#endif
