#ifndef AULA_H
#define AULA_H

// in Alumno.h
// #include <iostream>
// #include <string>

#include <vector>
#include <fstream>
#include <cmath>
#include "Alumno.h"

using namespace std;

struct Aula{ 
    char filename[100];

    vector<Alumno> load();
    bool add(Alumno a);
    bool erase(int a);
    
    Aula(){}; 
    Aula(char f[]){ strncpy(filename, f, sizeof(filename)); };
    ~Aula(){}
};

vector<Alumno> Aula::load(){
    string nom, appat, apmat, carr;
    
    vector<Alumno> alumnos;
    ifstream data;
    data.open(filename);

    if (!data.is_open()) throw runtime_error("Can't open file");

    while (data  >> nom >> appat >> apmat >> carr){
        Alumno a(nom, appat, apmat, carr);
    
        alumnos.push_back(a);
    }
    
    data.close();
    return alumnos;
}

bool Aula::add(Alumno a){
    ofstream data(filename, ios::app);
   
    if (!data.is_open()) throw runtime_error("Can't open file");

    data << "\n"
         << left << setw(sizeof(a.nombre)) << a.nombre
         << left << setw(sizeof(a.apPaterno)) << a.apPaterno
         << left << setw(sizeof(a.apMaterno)) << a.apMaterno
         << left << setw(sizeof(a.carrera)) << a.carrera;
    
    cout << "[Added]  ";
    a.print();

    data.close();
    
    return true;
}


#endif
