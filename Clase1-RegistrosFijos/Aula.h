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
    string line;
    fstream data(filename, ios::in | ios::out);
    if (!data.is_open()) throw runtime_error("Can't open file");

    getline(data, line, '\n');
    data.seekg (0, ios::end); // get to the end of the file

    int line_length = line.length();
    int file_length = data.tellg(); 
    int total_lines = file_length / (line_length);

    cout << "line_length: " << line_length <<endl
         << "total_lines: " << total_lines <<endl
         << "file_length: " << file_length << endl;


    if (a>total_lines) return false; // register #a doesn't exist

    // get last line
    data.seekg(file_length-(line_length));
    if (a!=total_lines) getline(data, line, '\n'); 
    else line="";

    // delete register #a and move last register (replace)
    cout << "Last line: " << line <<endl;
    int beg_line_a = (line_length+1)*(a-1); // (line_length+1) : count the '\n' at the end of each line
                                   // (a-1): go to the beginning of line #a    

    cout << "Pick line #a from " << beg_line_a << " to " << beg_line_a+line_length <<endl;   
    data.seekg((line_length+1)*(a-1));

    // data.replace((line_length+1)*(a-1), line_length, "line");
    data.close();

    return true;

};





#endif
