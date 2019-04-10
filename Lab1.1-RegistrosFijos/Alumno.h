#ifndef ALUMNO_H
#define ALUMNO_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

struct Alumno{
    // fill with whitespace
    char nombre[12] = {};
    char apPaterno[12] = {};
    char apMaterno[12] = {};
    char carrera[15] = {};
    int ciclo;
    float mensualidad;

    Alumno(string nom, string appat, string apmat, string carr, int cic, float mens)
          :ciclo(cic), mensualidad(mens) {

        // Resize string to fixed length
        nom.resize(sizeof(nombre)-1);
        appat.resize(sizeof(apPaterno)-1);
        apmat.resize(sizeof(apMaterno)-1);
        carr.resize(sizeof(carrera)-1);

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
             << left << setw(sizeof(carrera)) << carrera << "|"
             << ciclo << "|"
             << mensualidad << endl;
    }
};

#endif

// Alumno(string nom, string appat, string apmat, string carr, int cic, float mens)
//           : ciclo(cic), mensualidad(mens){
