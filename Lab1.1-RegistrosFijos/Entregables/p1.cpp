#ifndef P1_CPP
#define P1_CPP

#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

struct Alumno{
    // fill with whitespace
    char nombre[12] = {};
    char apPaterno[12] = {};
    char apMaterno[12] = {};
    char carrera[15] = {};

    Alumno(string nom, string appat, string apmat, string carr) {
        // copy string to char array
        copy(nom.begin(), nom.end(), nombre);
        copy(appat.begin(), appat.end(), apPaterno);
        copy(apmat.begin(), apmat.end(), apMaterno);
        copy(carr.begin(), carr.end(), carrera);
        
    }

    void print(){
        cout << left << setw(sizeof(nombre)) << nombre << "|"
             << left << setw(sizeof(apPaterno)) << apPaterno << "|"
             << left << setw(sizeof(apMaterno)) << apMaterno << "|"
             << left << setw(sizeof(carrera)) << carrera << endl;
    }
};

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



int main(){
    Aula aulita((char*) "./datos.txt");

    for (Alumno& a: aulita.load()){
        a.print();
    };

    Alumno nuevoa("Andrea", "Velasquez", "Gushiken", "Computacion");
    aulita.add(nuevoa);
    
    return EXIT_SUCCESS;
}



#endif