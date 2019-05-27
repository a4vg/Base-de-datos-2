#include <iostream>
#include <thread>
#include <vector>

#include "hash.h"

using namespace std;
//prueba.csv
//Archivos/modelos.csv
int main(){
  Hash myhash(10,50, "Archivos/modelos.csv");
  myhash.read();
  thread threads[5];
    for (int i=0; i<5; ++i){
        threads[i] = thread(Hash::insert, myhash, 510);
    }

    for (int i=0; i<5; ++i) threads[i].join();
}
