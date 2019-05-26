#include <fstream>
#include <string>
using namespace std;

class Type{
    static const vector<pair<string,double>> type_data;
    pair<int, int> type; // id, size

    public:
        static int getIdOf(string type_string){
            int c=0;
            for (auto type_pair: type_data){
                if (type_pair.first==type_string) return c;
                ++c;
            }
            throw("[Type::getIdOf] Invalid type or type not supported");
        };

        Type(int type_id){
            if (type_id>type_data.size() && type_id<0) throw("[Type::Type] Invalid type id");
            type = make_pair(type_id, type_data[type_id].second);
        };
        Type(string type_string){
            int id = getIdOf(type_string);
            type = make_pair(id, type_data[id].second);
        };
        int getId() { return type.first; };
        int getSize() { return type.second; };
        string getName() { return type_data[type.first].first; }
};

const vector<pair<string,double>> Type::type_data = {
    {"int", sizeof(int)},
    {"float", sizeof(float)},
    {"char", sizeof(char)},
    {"string", -1}, // String doesn't have a fixed size
    {"bool", sizeof(bool)}
};

void writeStringTo(ofstream &file, string str) {
    if (!file.is_open()) throw("Can't write to unopened file");

    /* string-length string */
    int len = str.size();
    file.write((char *) &len, sizeof(len));
    file.write(&str[0], len);
};

string readStringFrom(ifstream &file) {
    if (!file.is_open()) throw("Can't read from unopened file");

    int len=0;
    file.read((char *)&len, sizeof(len));
    string str;
    str.resize(len);
    file.read(&str[0], len); // Read string

    return str;
};

void writeDataTo(string string_data, int type_id, ofstream &outfile) {
    switch(type_id){ // id
        case 0:{ // int;
            int auxi = stoi(string_data);
            // cout << "Writing " << auxi;
            outfile.write((char*)(&auxi), sizeof(int)); 
            break;
        }
        case 1:{ // float
            float auxf = stof(string_data);
            outfile.write((char*)(&auxf), sizeof(float));
            break;
        }
        case 2:{ // char
            outfile.write((char*)(&string_data[0]), sizeof(char));
            break;
        }
        case 3:{ // string
            writeStringTo(outfile, string_data);
            break;
        }
        case 4:{ // bool
            bool auxb = stoi(string_data);
            outfile.write((char*)(&auxb), sizeof(bool));
        }
    }
};

bool eatDataFrom(int type_id, ifstream &infile, bool jump) {
    switch(type_id){ // id
        case 0:{ // int;
            if (!jump){
                int auxi;
                infile.read((char*)(&auxi), sizeof(int));
                if (!infile.eof()) cout << auxi << "," ;
            }
            else infile.ignore(sizeof(int));
            break;
        }
        case 1:{ // float
            if (!jump){
                float auxf;
                infile.read((char*)(&auxf), sizeof(float));
                if (!infile.eof()) cout << auxf << ", ";
            }
            else infile.ignore(sizeof(float));
            break;
        }
        case 2:{ // char
            if (!jump){
                char auxc;
                infile.read((char*)(&auxc), sizeof(char));
                if (!infile.eof()) cout << auxc << ", ";
            }
            else infile.ignore(sizeof(char));
            break;
        }
        case 3:{ // string
            if (!jump){
                string auxs = readStringFrom(infile);
                if (!infile.eof()) cout << auxs << ", ";
                break;
            }
            int len;
            infile.read((char *)&len, sizeof(len));
            infile.ignore(len);
            break;
        }
        case 4:{ // bool
            if (!jump){
                bool auxb;
                infile.read((char*)(&auxb), sizeof(bool));
                if (!infile.eof()) cout << auxb << ", ";
            }
            else infile.ignore(sizeof(bool));
        }
    }
    return !infile.eof();
};