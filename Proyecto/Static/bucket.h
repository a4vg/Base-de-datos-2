#include <iostream>
#include <vector>

using namespace std;

class Bucket{
public:
  int id;
  string name;
  int count=0;
  vector<int> overflow;

  Bucket(){
  }
};
