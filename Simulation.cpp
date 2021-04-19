#include "project.h"

using namespace std;

int main()
{
    //Determine number of shells from params.txt
    fstream params1;
    int num_shells=0;
    count_shells(&num_shells);
    cout<<"Simulating "<<num_shells<<" spherical shells..."<<endl;
    //Initialize data arrays with length=number of shells
    string names[num_shells];
    double mass[num_shells],r[num_shells],v[num_shells],a[num_shells];
    //Fill the data arrays with initial values from params.txt
    initialize_arrays(names,mass,r,v);
    double dt=.1,time=1,G = 4.30091e-3; //pc (km/s)^2 Msol^-1
    //find initial accelerations from initial radii
    for(int i=0;i<num_shells;i++){
        a[i] = (-G*.5*mass[i])/(pow(2*r[i],2));}
    ofstream myfile;
    myfile.open("output.txt");
    myfile<<"#Name"<<'\t'<<"Mass"<<'\t'<<"R"<<'\t'<<"v"<<'\t'<<"a"<<endl;
    myfile<<names[0]<<'\t'<<mass[0]<<'\t'<<r[0]<<'\t'<<v[0]<<'\t'<<a[0]<<endl;
    for(int t=0;t<450;t+=time){
        evolve(time,dt,mass,r,v,a,num_shells);
        myfile<<names[0]<<'\t'<<mass[0]<<'\t'<<r[0]<<'\t'<<v[0]<<'\t'<<a[0]<<endl;}
    myfile.close();




}