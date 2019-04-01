#ifndef P2_CPP
#define P2_CPP

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

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





int main(){
    Aula aulita((char*) "./datos.txt");

    for (Alumno& a: aulita.load()){
        a.print();
    };

    Alumno nuevoa("Andrea", "Velasquez", "Gushiken", "Computacion", 5, 2000);
    aulita.add(nuevoa);
    
    aulita.erase(2);
    
    return EXIT_SUCCESS;
}

#endif
