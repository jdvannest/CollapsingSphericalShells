#include "project.h"

using namespace std;

int main()
{
    //Determine number of shells from params.txt
    fstream params1;
    int num_shells=0;
    string line1;
    params1.open("params.txt",ios::in);
    while(getline(params1,line1)){
        if(line1[0]!='#'){
            num_shells+=1;
        }
    }
    params1.close();
    cout<<"Simulating "<<num_shells<<" spherical shells..."<<endl;
    //Initialize data arrays with length=number of shells
    string names[num_shells];
    double mass[num_shells],r[num_shells],v[num_shells],a[num_shells];
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
            while(line[c_index_out]!=','){c_index_out+=1;}
            v[index] = stod(line.substr(c_index_in,c_index_out));
            c_index_out+=1;
            c_index_in=c_index_out;
            a[index] = stod(line.substr(c_index_in));
            //move to next shell entry
            index+=1;
        }
    }
    




}