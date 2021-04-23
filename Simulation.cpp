#include "project.h"

using namespace std;

int main()
{
    time_t start,end;
    time(&start);
    //Determine name out output file from params.txt
    string fname;
    file_name(&fname);
    cout<<"Performing Run: "<<fname<<endl;

    //Determine number of shells from params.txt
    int num_shells=0;
    count_shells(&num_shells);
    cout<<"Simulating "<<num_shells<<" spherical shells."<<endl;
    //Initialize data arrays with length=number of shells + 1
    num_shells+=1;
    string names[num_shells];
    double mass[num_shells],r[num_shells],v[num_shells],a[num_shells];
    double energy;
    //Fill the data arrays with initial values from params.txt
    //Shell 0 is the central point mass of 10Msol
    names[0] = "Central Mass";
    mass[0] = 10;
    r[0] = m_to_AU(1);
    v[0] = 0;
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

    //find initial accelerations/energy from initial radii and velocities
    initial_acc(mass,r,a,num_shells);
    initial_energy(mass,r,v,&energy,num_shells);
    
    //Open output data file and fill with initial conditions
    ofstream myfile;
    myfile.open("outputs/"+fname+".txt");
    myfile<<"#Name"<<'\t'<<"Mass"<<'\t'<<"R"<<'\t'<<"v"<<'\t'<<"a"<<'\t'<<"Energy"<<'\t'<<"t"<<endl;
    for(int i=1;i<num_shells;i++){
        myfile<<names[i]<<'\t'<<kg_to_Msol(mass[i])<<'\t'<<m_to_AU(r[i])<<'\t'<<v[i]<<'\t'<<a[i]<<'\t'<<energy<<'\t'<<0<<endl;}

    //Perform integrations and output data after "output_time" has passed
    double t_elapsed=0;
    float prog=0;
    cout<<"0.00%";
    while(t_elapsed<total_time){
        evolve(output_time,dt,mass,r,v,a,&energy,num_shells);
        t_elapsed+=output_time;
        //Update output file current integration data
        for(int i=1;i<num_shells;i++){
            myfile<<names[i]<<'\t'<<kg_to_Msol(mass[i])<<'\t'<<m_to_AU(r[i])<<'\t'<<v[i]<<'\t'<<a[i]<<'\t'<<energy<<'\t'<<s_to_yr(t_elapsed)<<endl;}
        prog = round_up(t_elapsed/total_time*100);
        cout<<'\r'<<prog<<"%"<<flush;
        }
    //Close the output file and successfully exit the code
    myfile.close();
    time(&end);
    float runtime=difftime(end,start);
    string t_unit;
    if(runtime>3600){
        runtime = round_up(runtime/3600);
        t_unit = "hours";
    }else if(runtime>60){
        runtime = round_up(runtime/60);
        t_unit = "minuts";
    }else{
        runtime = round_up(runtime);
        t_unit="seconds";
    }
    cout<<'\r'<<"Simulation completed in "<<runtime<<" "<<t_unit<<endl;
    cout<<"Output written to outputs/"<<fname<<".txt"<<endl;
    exit(0);
}