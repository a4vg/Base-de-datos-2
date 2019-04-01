#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Alumno{
    public:
        string nombre;
        string apellidos;
        string carrera;
        int ciclo;
        float mensualidad;

        Alumno(string n, string ap, string car, float m):
        nombre(n), apellidos(ap), carrera(car), mensualidad(m){}; 
        void print(){
            cout << setw(10) << nombre
             << setw(20) << apellidos
             << setw(20) << carrera
             << setw(10) << mensualidad << endl;
        }
};

#endif
