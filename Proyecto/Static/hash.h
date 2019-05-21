#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "bucket.h"

using namespace std;

class Hash{
private:
  int d;
  vector <Bucket> table;
  bool full;
  int fd;
  int nextBuck=0;

public:
  Hash(int numBuckets, int fdbuck){
    d=numBuckets;
    fd=fdbuck;
    for (int i=0; i<d; i++){
      Bucket buck;
      buck.id = i;
      buck.name = to_string(i).append(".txt");
      //buck.overflow.push_back(i);
      table.push_back(buck);
      string svector="vector" + to_string(i).append(".txt");
      if (!is_file_exist(svector)){
        ofstream myfile;
        myfile.open(svector);
        myfile << i << endl;
        myfile.close();
      }
      nextBuck++;
    }
  }

  bool is_file_exist(string fileName){
    ifstream infile(fileName);
    return infile.good();
  }

  int doHash(int num){
    return num%d;
  }

  void read(){
    ifstream myfile;
    for (int i=0; i<d; i++){
      string svector="vector" + to_string(i).append(".txt");
      ifstream myfile;
      string line;
      myfile.open(svector);
      while (getline (myfile,line)){
        table[i].overflow.push_back(stoi(line));
        cout << "line: " << line << endl;
      }
      myfile.close();

    }
  }

  void insert(int num){
    int buckHash=doHash(num);
    string line;
    int buckNum=table[buckHash].overflow.back();
    string snBucket=to_string(buckNum).append(".txt");
    ifstream myfile;
    myfile.open(snBucket);
    while (getline (myfile,line)){
      table[buckNum].count+=1;
      cout << line;
    }
    myfile.close();
    if (table[buckNum].count<fd){
      ofstream myfile;
      myfile.open(snBucket, ios::app);
      myfile << num << endl;
      myfile.close();
    }
    else{
      cout <<"Overflow" << endl;
      nextBuck++;
      Bucket buck;
      buck.id = nextBuck;
      buck.name = to_string(nextBuck).append(".txt");
      buck.overflow.push_back(nextBuck);
      table.push_back(buck);
      table[buckHash].overflow.push_back(nextBuck);
      string svector="vector" + to_string(buckHash).append(".txt");
      ofstream myfilev;
      myfilev.open(svector, ios::app);
      myfilev << buck.id << endl;
      myfilev.close();
      ofstream myfile;
      myfile.open(buck.name, ios::app);
      myfile << num << endl;
      myfile.close();
    }
  }

  // bool search(int num){
  //
  // }

  // void print(){
  //   for (int i=0; i<table.size(); i++){
  //     vector<int> vtmp=table[i].vectorfd;
  //     cout  << table[i].id << "  ";
  //     for (int j=0; j<vtmp.size(); j++){
  //       cout << vtmp[j] << " ";
  //     }
  //     cout << endl;
  //   }
  // }

};
