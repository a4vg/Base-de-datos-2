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
    // ifstream data(filename);
    fstream bfile("datos.dat", ios::out | ios::binary);
    ifstream data(filename);

    if (!data.is_open()) throw runtime_error("Can't open file");
    if (!bfile.is_open()) throw runtime_error("Can't open file");
    data.ignore(256, '\n'); //ignore first line

    string nombre, apellidos, carrera, s_mensualidad;

    while (getline(data, nombre, '|') &&
           getline(data, apellidos, '|') &&
           getline(data, carrera, '|') &&
           getline(data, s_mensualidad, '\n')
          ){


        float mensualidad = stof(s_mensualidad);
    
        Alumno a(nombre, apellidos, carrera, stof(s_mensualidad));

        cout << "Writing.. alumno:\n";

        a.print();
        // Nombre
        int strlength = nombre.length();
        bfile.write((char*) &strlength, sizeof(strlength));
        bfile.write((char*) nombre.c_str(), strlength);
        // Apellidos
        strlength = apellidos.length();
        bfile.write((char*) &strlength, sizeof(strlength));
        bfile.write((char*) apellidos.c_str(), strlength);
        // Carrera
        strlength = carrera.length();
        bfile.write((char*) &strlength, sizeof(strlength));
        bfile.write((char*) carrera.c_str(), strlength);
        // Mensualidad
        bfile.write((char*) &mensualidad, mensualidad);
    }

    data.close();
    bfile.close();

};

vector<Alumno> Registro::read_frombin(string bfilename){
    ifstream bfile("datos.dat", ios::in | ios::binary);

    if (!bfile.is_open()) throw runtime_error("Can't open file");
    bfile.ignore(256, '\n'); //ignore first line

    vector<Alumno> alumnos;

    int count=0;
    while (!bfile.eof()){

        cout << "Reading alumno...\n";
        int tam;
        string attr[3];

        // Nombre, apellidos, carrera
        for (int i=0; i<3; ++i){
            bfile.read((char *) &tam, sizeof(int));
            char* temp = new char[tam + 1];
            bfile.read(temp, tam);
            temp[tam] = '\0';
            attr[i] = string(temp);
            cout << setw(15) << temp << endl;
            // delete [] temp;
        }
        
        int mensualidad;
        bfile.read((char*) &mensualidad, mensualidad);
        cout << setw(15) << mensualidad << endl;

        Alumno a(attr[0], attr[1], attr[2], mensualidad);
        alumnos.push_back(a);
    }

        
        bfile.close();
        return alumnos;
};


#endif
