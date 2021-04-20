#include "project.h"

using namespace std;

int main()
{
    //Determine number of shells from params.txt
    int num_shells=0;
    count_shells(&num_shells);
    cout<<"Simulating "<<num_shells<<" spherical shells."<<endl;
    //Initialize data arrays with length=number of shells
    string names[num_shells];
    double mass[num_shells],r[num_shells],v[num_shells],a[num_shells];
    //Fill the data arrays with initial values from params.txt
    initialize_arrays(names,mass,r,v);
    // Convert to kg,m,s from Msol,AU,yr
    for(int i=0;i<num_shells;i++){
        mass[i] = Msol_to_kg(mass[i]);
        r[i] = AU_to_m(r[i]);}

    //Determine time paramaters for integration
    double total_time,output_time,dt;
    time_params(&total_time,&dt,&output_time);
    cout<<"Integrating for "<<total_time<<" years with a dt of "<<dt<<" years."<<endl;
    cout<<"Outputing data every "<<output_time<<" years."<<endl;
    //Convert from yr to s
    total_time = yr_to_s(total_time);
    dt = yr_to_s(dt);
    output_time = yr_to_s(output_time);

    //find initial accelerations from initial radii
    initial_acc(mass,r,a,num_shells);
    
    //Open output data file and fill with initial conditions
    ofstream myfile;
    myfile.open("output.txt");
    myfile<<"#Name"<<'\t'<<"Mass"<<'\t'<<"R"<<'\t'<<"v"<<'\t'<<"a"<<'\t'<<"t"<<endl;
    for(int i=0;i<num_shells;i++){
        myfile<<names[i]<<'\t'<<kg_to_Msol(mass[i])<<'\t'<<m_to_AU(r[i])<<'\t'<<v[i]<<'\t'<<a[i]<<'\t'<<0<<endl;}

    //Perform integrations and output data after "output_time" has passed
    for(int t=0;t<total_time;t+=output_time){
        evolve(output_time,dt,mass,r,v,a,num_shells);

        //Update output file current integration data
        for(int i=0;i<num_shells;i++){
            myfile<<names[i]<<'\t'<<kg_to_Msol(mass[i])<<'\t'<<m_to_AU(r[i])<<'\t'<<v[i]<<'\t'<<a[i]<<'\t'<<s_to_yr(t)<<endl;}
        }   

    //Close the output file and successfully exit the code
    myfile.close();
    cout<<"Done: Output written to output.txt"<<endl;
    exit(0);
}