#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream paramfile;
    paramfile.open("params.txt");
    paramfile<<"#Name of run. For example, entering"<<endl;
    paramfile<<"#run123"<<endl;
    paramfile<<"#would output the data into the file outputs/run123.txt"<<endl;
    paramfile<<endl;
    paramfile<<"output"<<endl;
    paramfile<<endl;
    paramfile<<"------Do Not Remove This Line------"<<endl;
    paramfile<<endl;
    paramfile<<"#Total Integration Time (yr), dt (yr), Output time (yr)"<<endl;
    paramfile<<"#*Recommended dt ~1e-5 or less*"<<endl;
    paramfile<<endl;
    paramfile<<"2,1e-5,.001"<<endl;
    paramfile<<endl;
    paramfile<<"------Do Not Remove This Line------"<<endl;
    paramfile<<endl;
    paramfile<<"#Shell Name,Mass (Msol),Initial Radius (AU),Initial Velocity (km/s)"<<endl;
    paramfile<<endl;
    paramfile<<"alpha,1,10,0"<<endl;
    paramfile.close();
    cout<<"Generated file 'params.txt'"<<endl;
    exit(0);
}