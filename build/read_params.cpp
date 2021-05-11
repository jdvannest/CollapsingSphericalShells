#include "project.h"

using namespace std;

void file_name(std::string* fname)
{
    fstream params;
    string line;
    params.open("params.txt",ios::in);
    bool good=true;
    while(getline(params,line)){
        if(good){
            if(!line.empty()){
                if(line[0]!='#'){
                    *fname=line;
                    good=false;
                }
            }
        }
    }
}

void time_params(double* time, double* dt, double* output_time)
{
    int index=0,c_index_in=0,c_index_out=0;
    fstream params;
    string line;
    params.open("params.txt",ios::in);
    int n=0;
    while(getline(params,line)){
        if(!line.empty()){
            if(n==1){
                if(line[0]!='#'){
                    c_index_out=0;
                    c_index_in=c_index_out;
                    while(line[c_index_out]!=','){c_index_out+=1;}
                    *time = stod(line.substr(0,c_index_out));
                    c_index_out+=1;
                    c_index_in=c_index_out;
                    while(line[c_index_out]!=','){c_index_out+=1;}
                    *dt = stod(line.substr(c_index_in,c_index_out));
                    c_index_out+=1;
                    c_index_in=c_index_out;
                    *output_time = stod(line.substr(c_index_in));
                    n+=1;
                }
            }
            else if(line[0]=='-'){
                n+=1;
            }
        }
    }
    params.close();
}

void count_shells(int* num_shells)
{
    //Determine number of shells from params.txt
    fstream params;
    string line;
    int n=0;
    params.open("params.txt",ios::in);
    while(getline(params,line)){
        if(!line.empty()){
            if(n==2){
                if(line[0]!='#'){
                    *num_shells+=1;
                }
            }
            else if(line[0]=='-'){
                n+=1;
            }   
        }
    }
    params.close();
}

void initialize_arrays(std::string* names, double* mass, double* r, double* v)
{
    //Fill the data arrays with initial values from params.txt
    int index=1,c_index_in=0,c_index_out=0;
    fstream params;
    params.open("params.txt",ios::in);
    string line;
    int n=0;
    while(getline(params,line)){
        if(!line.empty()){
            if(n==2){
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
            else if(line[0]=='-'){
                n+=1;
            }
        }
    }
    params.close();
}