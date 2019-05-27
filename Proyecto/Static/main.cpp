#include <iostream>
#include <vector>

#include "hash.h"

using namespace std;
//prueba.csv
//Archivos/modelos.csv
int main(){
  Hash myhash(10,50, "Archivos/modelos.csv");
  myhash.read();
  myhash.insert(510);
}
