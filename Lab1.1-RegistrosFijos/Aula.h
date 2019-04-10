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
    int cic;
    float mens;
    
    vector<Alumno> alumnos;
    ifstream data;
    data.open(filename);

    if (!data.is_open()) throw runtime_error("Can't open file");

    while (data  >> nom >> appat >> apmat >> carr >> cic >> mens){
        Alumno a(nom, appat, apmat, carr, cic, mens);
    
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
         << left << setw(sizeof(a.carrera)) << a.carrera
         << a.ciclo << " " << a.mensualidad;
    
    cout << "[Added]  ";
    a.print();

    data.close();
    
    return true;
}

bool Aula::erase(int a){
    ifstream data(filename, ios::in);
    ofstream temp("temp.txt", ios::out);
    string line;

    if (!data.is_open()) throw runtime_error("Can't open file");

    getline(data, line, '\n');
    data.seekg (0, ios::end); // get to the end of the file

    int line_length = line.length();
    int file_length = data.tellg(); 
    int total_lines = file_length / (line_length);

    if (a>total_lines) return false; // register #a doesn't exist
    data.seekg(0);

    for (int i=1; i<a; ++i){
        getline(data, line, '\n');
        if (i!=1) temp << '\n'; // avoid writing '\n' in first line
        temp << line;
    }
    getline(data, line, '\n'); // skip line to be erased
    while(getline(data, line, '\n')){
        if (temp.tellp()) temp << '\n';
        temp << line;
    }

    temp.close();
    data.close();

    remove(filename);
    rename("temp.txt",filename);

    return true;

};





#endif
