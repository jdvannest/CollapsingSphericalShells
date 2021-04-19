#include "project.h"

using namespace std;

void count_shells(int* num_shells)
{
    //Determine number of shells from params.txt
    fstream params;
    string line;
    params.open("params.txt",ios::in);
    while(getline(params,line)){
        if(line[0]!='#'){
            *num_shells+=1;
        }
    }
    params.close();
}

void initialize_arrays(std::string* names, double* mass, double* r, double* v)
{
    //Fill the data arrays with initial values from params.txt
    int index=0,c_index_in=0,c_index_out=0;
    fstream params;
    params.open("params.txt",ios::in);
    string line;
    while(getline(params,line)){
        if(line[0]!='#'){
            c_index_out=0;
            c_index_in=c_index_out;
            while(line[c_index_out]!=','){c_index_out+=1;}
            names[index] = line.substr(0,c_index_out);
            c_index_out+=1;
            c_index_in=c_index_out;
            while(line[c_index_out]!=','){c_index_out+=1;}
            mass[index] = stod(line.substr(c_index_in,c_index_out));
            c_index_out+=1;
            c_index_in=c_index_out;
            while(line[c_index_out]!=','){c_index_out+=1;}
            r[index] = stod(line.substr(c_index_in,c_index_out));
            c_index_out+=1;
            c_index_in=c_index_out;
            v[index] = stod(line.substr(c_index_in));
            //move to next shell entry
            index+=1;
        }
    }
    params.close();
}