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
  int fd;
  int count;

public:
  Hash(int numBuckets, int fdbuck){
    d=numBuckets;
    fd=fdbuck;
    string countertxt="counter.txt";
    if (!is_file_exist(countertxt)){
      ofstream myfile;
      myfile.open(countertxt);
      myfile << d-1 << endl;
      myfile.close();
    }
    string line;
    ifstream myfile;
    myfile.open(countertxt);
    getline(myfile, line);
    count=stoi(line);
    cout << count << endl;
    myfile.close();
    for (int i=0; i<d; i++){
      Bucket buck;
      buck.id = i;
      buck.name = "bucket/" + to_string(i).append(".txt");
      //buck.overflow.push_back(i);
      table.push_back(buck);
      string svector="bucket/overflow_info/vector" + to_string(i).append(".txt");
      if (!is_file_exist(svector)){
        ofstream myfile;
        myfile.open(svector);
        myfile << i << endl;
        myfile.close();
      }
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
      string svector="bucket/overflow_info/vector" + to_string(i).append(".txt");
      ifstream myfile;
      string line;
      myfile.open(svector);
      while (getline (myfile,line)){
        table[i].overflow.push_back(stoi(line));
      }
      myfile.close();

    }
  }

  void insert(int num){
    int buckHash=doHash(num);
    string line;
    int buckNum=table[buckHash].overflow.back();
    string snBucket="bucket/" + to_string(buckNum).append(".txt");
    ifstream myfile;
    myfile.open(snBucket);
    while (getline (myfile,line)){
      table[buckNum].count+=1;
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
      string countertxt="counter.txt";
      ofstream myfilec;
      myfilec.open(countertxt);
      count+=1;
      myfilec << count << endl;
      cout << count << endl;
      myfilec.close();
      Bucket buck;
      buck.id = count;
      buck.name = "bucket/" + to_string(count).append(".txt");
      buck.overflow.push_back(count);
      table.push_back(buck);
      table[buckHash].overflow.push_back(count);
      string svector="bucket/overflow_info/vector" + to_string(buckHash).append(".txt");
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

};
