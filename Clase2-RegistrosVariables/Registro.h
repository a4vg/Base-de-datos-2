#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Alumno.h"

using namespace std;

class Registro{
    string filename;
    public:
        Registro(string file) : filename(file){};

        vector<Alumno> get_alumnos(); // P1
        void write_tobin(); // P2
        vector<Alumno> read_frombin(string bfile); // P2
};


vector<Alumno> Registro::get_alumnos(){
    ifstream data;
    vector<Alumno> alumnos;

    string nombre, apellidos, carrera;
    string s_mensualidad;

    data.open(filename);

    if (!data.is_open()) throw runtime_error("Can't open file");
    data.ignore(256, '\n'); //ignore first line

    while (getline(data, nombre, '|') &&
           getline(data, apellidos, '|') &&
           getline(data, carrera, '|') &&
           getline(data, s_mensualidad, '\n')
          ){
        Alumno a(nombre, apellidos, carrera, stof(s_mensualidad));
        alumnos.push_back(a);
    }

    data.close();

    return alumnos;
};


void Registro::write_tobin(){
    ifstream data(filename);
    ofstream bfile("datos.dat", ios::out | ios::binary);

    if (!data.is_open()) throw runtime_error("Can't open file");
    data.ignore(256, '\n'); //ignore first line
    /*
    string nombre ="Andrea", apellidos="Velasquez Gushiken", carrera="Computacion";
    int ciclo=5;
    float mensualidad=3212.65;
    Alumno a(nombre, apellidos, carrera, mensualidad);
    */

    string nombre, apellidos, carrera, s_mensualidad;

    while (getline(data, nombre, '|') &&
           getline(data, apellidos, '|') &&
           getline(data, carrera, '|') &&
           getline(data, s_mensualidad, '\n')
          ){
        Alumno a(nombre, apellidos, carrera, stof(s_mensualidad));
        bfile.write((const char*) &a, sizeof(a));
    }

    data.close();
    bfile.close();
};


#endif
