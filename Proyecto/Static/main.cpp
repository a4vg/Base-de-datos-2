#include <iostream>
#include <vector>

#include "hash.h"

using namespace std;
//prueba.csv
//Archivos/modelos.csv
int main(){
  Hash myhash(6,10, "Archivos/modelos.csv");
  myhash.read();
  //myhash.insert(1119, "Hola");
  //myhash.insert(12);
  //myhash.print();
  myhash.search(119);

}
