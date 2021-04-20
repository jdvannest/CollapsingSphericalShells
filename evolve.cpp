#include "project.h"

using namespace std;

void initial_acc(const double* mass, const double* r, double* a, const int num_shells)
{
    double G = 6.67430e-11 ; //(m^3 kg^-1 s^-2)
    for(int i=0;i<num_shells;i+=1){
        a[i] = (-G*mass[i])/(2*M_PI*pow(r[i],2));
        for(int j=0;j<num_shells;j+=1){
            if(i!=j & r[j]<r[i]){
                a[i]+=(-G*mass[j])/(pow(r[i],2));
            }
        }
    }
}

void evolve(double time, double dt, const double* mass, double* r, double* v, double* a, const int num_shells)
{
    double G = 6.67430e-11 ; //(m^3 kg^-1 s^-2)
    float t=0,int_a;
    while(t<time){
        for(int i=0;i<num_shells;i+=1){
            r[i] = r[i]+v[i]*dt+0.5*a[i]*pow(dt,2);
            int_a = (-G*mass[i])/(2*M_PI*pow(r[i],2));
            for(int j=0;j<num_shells;j+=1){
                if(i!=j & r[j]<r[i]){
                int_a += (-G*mass[j])/(pow(r[i],2));}
            }
            v[i] = v[i]+0.5*(a[i]+int_a)*dt;
            a[i] = int_a;
            if(r[i]<1e-5){
                r[i]=0;
                v[i]=0;
                a[i]=0;
            }
        }
        t+=dt;
    }
}