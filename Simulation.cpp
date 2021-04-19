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
    initialize_arrays(names,mass,r,v,a);
    for(int i=0;i<num_shells;i++){
        cout<<names[i]<<'\t'<<mass[i]<<'\t'<<r[i]<<'\t'<<v[i]<<'\t'<<a[i]<<'\t'<<endl;}




}