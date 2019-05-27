#include <vector>
#include <map>
#include <sstream>
#include <thread>
#include <mutex>
#include "ImportantOperations.cpp"

typedef int keytype;

void split(string line, vector<string>& words, char delimiter){
    stringstream line_stream(line);
    string temp;

    while (getline(line_stream, temp, delimiter)) {
        if (temp[temp.size() - 1] == '\r') temp.erase(temp.size() - 1);
        words.push_back(temp);
    }
};

class RandomFile
{
    string bin_filename;
    vector<Type> columns_type;
    static int id_count;
    static mutex mlock;

    public:
        map<keytype, int> dictionary;

        int insertRecord(string data_string){
            ofstream outfile(bin_filename, ios::app | ios::binary);
            // outfile.seekp(outfile.eof());
            mlock.lock();
            writeRecord(to_string(id_count) + "," + data_string, outfile);
            id_count++;
            mlock.unlock();
            outfile.close();

            return id_count;
        }

        void showRecord(int id){
            if (id>id_count || id<0) throw("[RandomFile::showRecord] Invalid id");

            ifstream infile(bin_filename);
            infile.seekg(dictionary[id]);
            goThroughRecord(infile);

            infile.close();
        }

        bool goThroughRecord(ifstream &infile, bool jump=false){
            for (int c=0; c<columns_type.size(); ++c){
                if (!eatDataFrom(columns_type[c].getId(), infile, jump)) return false;
            }
            if (!jump) cout << endl;
            return true;
        }

        void uploadIndex(bool verbose=false){
            dictionary.clear(); // ONLY FOR DEBUGGING

            string index_filename = "index_" + bin_filename;
            ifstream infile(index_filename);

            int key, value;
            while (infile.read((char*)&key, sizeof(int))){
                infile.read((char*)&value, sizeof(int));
                dictionary[key] = value;
                if (verbose) cout << "Uploading " << key << " " << value <<endl;
            }
            id_count = key+1;
            
            infile.close();
        }

        void saveIndex(){
            string index_filename = "index_" + bin_filename;
            ofstream outfile(index_filename);

            for (auto const &el: dictionary){
                outfile.write((char*)(&el.first), sizeof(int));
                outfile.write((char*)(&el.second), sizeof(int));
                
                // cout << el.first << " (id)    " << el.second << " (pos)"  << endl;
            }

            outfile.close();
        }

        void printIndex(){
            for (auto const &el: dictionary){
                cout << el.first << " (id)    " << el.second << " (pos)"  << endl;
            }
        }

        void processIndex(){
            ifstream infile(bin_filename, ios::binary);
            readColumnTypes(infile, false); // just skip

            do{
                dictionary.insert(make_pair(++id_count, infile.tellg()));
            }while (goThroughRecord(infile, true));
            
            infile.close();
        }

        void readColumnTypes(ifstream &infile, bool set_columns_type){
            int n_columns;
            infile.read((char *)&n_columns, sizeof(int));
            for (int i=0; i<n_columns; ++i){
                int aux;
                if (set_columns_type) infile.read((char *)&aux, sizeof(int));
                else infile.ignore(sizeof(int));
                
                if (set_columns_type) columns_type.push_back(Type(aux));
            }
        }

        void exportBinary(){
            ifstream infile(bin_filename, ios::binary);
            if (!infile.is_open()) perror("error while opening file");

            readColumnTypes(infile, false);

            while (goThroughRecord(infile));

            infile.close();
        }

        void writeRecord(string data_string, ofstream &outfile){
            vector<string> words;
            split(data_string, words, ',');

            int c=0;
            for (int c=0; c<columns_type.size(); ++c){
                writeDataTo(words[c], columns_type[c].getId(), outfile);
            }
        }

        string generateBinary(string csv_file, vector<string> col_type, bool has_headers){
            string line;
            ifstream infile(csv_file, ios::in);
            if (!infile.is_open()) perror("error while opening file");

            string filename = csv_file.erase(csv_file.length()-4, csv_file.length()) + string(".dat"); // change ext from .csv to .bin
            ofstream outfile(filename, ios::binary);

            // Write column types
            int aux = col_type.size();
            outfile.write((char*)(&aux), sizeof(int)); // number of columns
            // cout << "Writing " << aux << endl;

            for (const auto &type_string: col_type) {
                Type type(type_string);
                aux = type.getId();
                outfile.write((char*)(&aux), sizeof(int)); // write id

                columns_type.push_back(type); // add to atribute columns_type
            }
            
            if (has_headers) getline(infile, line, '\n'); // skip if headers

            // Write data
            while (getline(infile, line, '\n')) writeRecord(line, outfile);


            infile.close();
            outfile.close();
            return filename;

        }

        RandomFile(string bin_file="", string csv_file="", vector<string> col_type=vector<string>(), bool has_headers=true){
            if ((csv_file.empty() && bin_file.empty()) || (!csv_file.empty() && col_type.empty()))
                throw("[RandomFile::RandomFile] Supply csv_file with column types or bin_file");
            
            if (!csv_file.empty()) { bin_filename = generateBinary(csv_file, col_type, has_headers); }
            else{
                bin_filename=bin_file;
                ifstream infile(bin_filename, ios::binary);
                readColumnTypes(infile, true); // set column_types
                infile.close();
                uploadIndex();
            }
        };
        ~RandomFile(){
            // save index and bin
        };
};
int RandomFile::id_count=0;
