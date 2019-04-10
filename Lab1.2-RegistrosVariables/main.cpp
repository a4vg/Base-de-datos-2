#ifndef MAIN_CPP
#define MAIN_CPP

#include "Registro.h"


int main(){
    Registro reg("./datos.txt");

    cout << "Datos\n----------------------\n";
    for (auto& a : reg.get_alumnos()){
        a.print();
    };

    cout << "\n Writing to binary... \n";
    reg.write_tobin();

    cout << "\n Reading from binary... \n";
    reg.read_frombin("datos.dat");





    return 0;
}

#endif