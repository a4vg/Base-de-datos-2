#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <thread>
#include <ctime>
#include <ratio>
#include <chrono>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <time.h>

#include "bucket.h"

using namespace std;

class Hash{
private:
  int d;//cantidad de  buckets
  vector <Bucket> table;
  int fb;//limite de datos en un bucket
  int count;
  static mutex mlock;

public:
  Hash(int numBuckets, int fdbuck, string archivo){//constructor
    d=numBuckets;
    fb=fdbuck;
    string countertxt="counter.txt";
    string line;
    ifstream myfile;
    myfile.open(countertxt);
    myfile >> count;//saber cual era el count anterior
    myfile.close();
    string hash="hash.txt";//donde se gurada el hash
    int vd;
    int vfd;
    if (is_file_exist(hash)){
      ifstream myfile;
      myfile.open(hash);
      myfile >> vd >> vfd;
      if (vd!=d || vfd!=fb){//si se cambia el numero de buckets o de limite
        cout << "borra todos los txt" << endl;
        system("rm bucket/*.txt");//system ingresa el comando en terminal (macos y linux)
        system("rm bucket/overflow_info/*.txt");
        system("rm hash.txt");
        system("rm counter.txt");
        myfile.close();
        ofstream hmyfile;
        hmyfile.open(hash);//ingresar el nuevo numero de buckets y limite
        hmyfile <<  d << " " << fb << endl;
        hmyfile.close();
      }
    }
    else{
      ofstream hmyfile;
      hmyfile.open(hash);//ingresar el numero de buckets y limite
      hmyfile <<  d << " " << fb << endl;
      hmyfile.close();
    }

    for (int i=0; i<d; i++){//crear los buck iniciales con el d
      Bucket buck;
      buck.id = i;
      buck.name = "bucket/" + to_string(i).append(".txt");
      buck.overflow.push_back(i);//lista para saber cuales son los buckets de overflow
      table.push_back(buck);
      string svector="bucket/overflow_info/vector" + to_string(i).append(".txt");
      if (!is_file_exist(svector)){//crearle un overflow a cada buck inicial
        ofstream myfile;
        myfile.open(svector);
        myfile << i << endl;
        myfile.close();
      }
    }
    if (!is_file_exist(countertxt)){//counter para saber cual es el sig buck
      ofstream myfile;
      myfile.open(countertxt);
      myfile << d-1 << endl;//-1 porque empieza en 0
      count=d-1;
      myfile.close();
      string hline;
      ifstream hmyfile;
      string idf;
      hmyfile.open(archivo);
      getline(hmyfile, hline);
      while(getline(hmyfile, hline)){
        stringstream tmp;
        replace(hline.begin(), hline.end(), ',', ' ');
        if (hline[hline.size() - 1] == '\r') hline.erase(hline.size() - 1);//elimina \r
        tmp << hline;
        tmp >> idf;
        int largo=idf.length()+1;//+1 por el espacio en blanco
        int id=stoi(idf);
        hline.erase (hline.begin(), hline.begin()+largo);//eliminar los numero para tener solo la data
        insert(id, hline);
      }
      hmyfile.close();
    }

  }

  bool is_file_exist(string fileName){//saber si existe elarchivo
    ifstream infile(fileName);
    return infile.good();
  }

  int doHash(int num){
    return num%d;
  }

  void read(){//leer lo que habia en mem secundaria para hacer cosas
    ifstream myfile;
    for (int i=0; i<d; i++){
      string svector="bucket/overflow_info/vector" + to_string(i).append(".txt");
      ifstream myfile;
      string line;
      myfile.open(svector);
      while (getline (myfile,line)){
        table[i].overflow.push_back(stoi(line));//agregarlo al vector de overflow
      }
      myfile.close();
    }
  }
  double prom=0;
  double cantfilas=0;
  void insert(int num, string datos){
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int buckHash=doHash(num);
    string line;
    string hash="hash.txt";
    int buckNum=table[buckHash].overflow.back();//coger el ultimo bucket del overflow
    string snBucket="bucket/" + to_string(buckNum).append(".txt");
    ifstream myfile;
    myfile.open(snBucket);
    while (getline (myfile,line)){//saber cuantos datos tiene el bucket
      table[buckNum].count+=1;
    }
    myfile.close();
    if (table[buckNum].count<fb){//si hay espacio
      ofstream myfile;
      myfile.open(snBucket, ios::app);
      myfile << num << " " << datos << endl;//meterlo al buck
      cout << "Insertado" << endl;
      myfile.close();
      ofstream vmyfile;
      vmyfile.open(hash, ios::app);
      vmyfile << num << " " << buckNum << endl;//meterlo al hash
      vmyfile.close();
    }
    else{
      string countertxt="counter.txt";
      ofstream myfilec;
      myfilec.open(countertxt);
      count+=1;//siguiente bucket
      myfilec << count << endl;
      myfilec.close();
      Bucket buck;
      buck.id = count;//crear otro bucket
      buck.name = "bucket/" + to_string(count).append(".txt");
      table.push_back(buck);
      table[buckHash].overflow.push_back(count);
      string svector="bucket/overflow_info/vector" + to_string(buckHash).append(".txt");
      ofstream myfilev;
      myfilev.open(svector, ios::app);//agregarlo al overflow vector
      myfilev << buck.id << endl;
      myfilev.close();
      ofstream myfile;
      myfile.open(buck.name, ios::app);//agregarlo al nuevo bucket
      myfile << num << " " << datos << endl;
      cout << "Insertado overflow" << endl;
      myfile.close();
      ofstream vfmyfile;
      vfmyfile.open(hash, ios::app);//agregarlo al hash
      vfmyfile << num << " " << count << endl;
      vfmyfile.close();
    }
    table[buckNum].count=0;
    cantfilas++;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    prom+=time_span.count();
    cout << "Insertar duro " << prom/cantfilas << " segundos." << endl;
  }

  void search(int target){//retorna la linea
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    string hash="hash.txt";
    int id;
    int idb;
    int bucket;
    string line;
    string tmp;
    ifstream myfile;
    myfile.open(hash);
    getline(myfile, tmp);
    while (myfile >> id >> bucket){//encontrar el bucket donde esta target
      if (id==target) break;
    }
    myfile.close();
    string bucktxt="bucket/" + to_string(bucket).append(".txt");
    ifstream vmyfile;
    vmyfile.open(bucktxt);//abrir ese bucket
    while (getline(vmyfile, line)){
      stringstream tmp;
      if (line[line.size() - 1] == '\r') line.erase(line.size() - 1);//elimina \r
      tmp << line;
      tmp >> idb;
      if (idb==target){
        cout << "Busqueda: " << line << endl;
        break;
      }
    }
    vmyfile.close();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Buscar duro " << time_span.count() << " segundos." << endl;
  }
};
