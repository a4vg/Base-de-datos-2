#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Alumno{
    public:
        string filename;
        string nombre;
        string apellidos;
        string carrera;
        int ciclo;
        float mensualidad;

        Alumno(string file); // P1

};


Alumno::Alumno(string file) : filename(file){
    ifstream data;
    string mens;

    data.open(filename);

    if (!data.is_open()) throw runtime_error("Can't open file");

    data.ignore(256, '\n'); //ignore first line

    cout << "Datos\n----------------------\n";
    while (getline(data, this->nombre, '|') &&
           getline(data, this->apellidos, '|') &&
           getline(data, this->carrera, '|') &&
           getline(data, mens, '\n')
          ){

        this->mensualidad = stof(mens);

        cout << setw(10) << this->nombre;
        cout << setw(20) << this->apellidos;
        cout << setw(20) << this->carrera;
        cout << setw(10) << this->mensualidad <<endl;
    }

    data.close();

};





#endif
