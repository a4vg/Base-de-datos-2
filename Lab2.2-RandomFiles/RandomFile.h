#ifndef RANDOMFILE_H
#define RANDOMFILE_H

#include <iostream>
#include <utility> // make_pair()
#include <cstdlib> // srand()
#include <ctime> // time()
#include <fstream>
#include <string>
#include <vector>
#include <map>


#include "Record.h"

using namespace std;

struct RandomIndex{
    map<int, Record*> dictionary;
    void readIndex(){
        ifstream indexfile("index.dat");
        if (!indexfile.good()) return; // if file doesn't exist
        cout << "\nInexistent index file";
        // TODO
    };
    void saveIndex(){
        ofstream outputbin("index.dat");
    }; // TODO
    void addIndexEntry(int key, Record* address){
        dictionary.insert(make_pair(key, address));
    };
    Record get(int key){
        return *dictionary[key];
    };
    void print(){
        for (auto& entrypair: dictionary){
            cout << "[" << entrypair.first << "]"; // id
            entrypair.second->print();
        }
    };
};


class RandomFile{
    string filename;
    string indexname;
    RandomIndex index;

    vector<Record> records;
    static int totalregisters;

    public:
        RandomFile(string fn) : filename(fn){
            string nom, appat, apmat, carr;
            int cic;
            float mens;
            
            ifstream data(filename);

            if (!data.is_open()) throw runtime_error("Can't open file");

            while (data  >> nom >> appat >> apmat >> carr >> cic >> mens){
                addRecord(nom, appat, apmat, carr, cic, mens);
            }
            
            data.close();
            // index.readIndex();
        };

        void addRecord(string nom, string appat, string apmat, string carr, int cic, float mens){
            Record* rp = new Record(totalregisters, nom, appat, apmat, carr, cic, mens);
            records.push_back(*rp);
            index.addIndexEntry(totalregisters, rp);

            ++totalregisters;
        }
        
        bool search(int id){
            if (totalregisters<=id or 0>id) return false;
            index.get(id).print();
            return true;
        }

        void testIndex(){
            cout << "\nTesting index...\n";
            // Print
            index.print();
            cout << "Last id should be: " << totalregisters-1 << "\n";
            //Search
            int randomregister = rand()%(totalregisters-1);
            cout << "\nGetting register #" << randomregister << endl;
            search(randomregister);
        }


        ~RandomFile(){
            index.saveIndex();
        }

};

int RandomFile::totalregisters = 0;
#endif

// Alumno(string nom, string appat, string apmat, string carr, int cic, float mens)
//           : ciclo(cic), mensualidad(mens){
