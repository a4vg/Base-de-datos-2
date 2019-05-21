#include <iostream>
#include <vector>

#include "hash.h"

using namespace std;

int main(){
  Hash myhash(4, 2);
  myhash.read();
  myhash.insert(24);
  //myhash.insert(12);
  //myhash.print();

}
