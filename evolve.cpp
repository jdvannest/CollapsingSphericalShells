#include "project.h"

using namespace std;

void initial_acc(const double* mass, const double* r, double* a, const int num_shells)
{
    double G = 6.67430e-11 ; //(m^3 kg^-1 s^-2)
    for(int i=0;i<num_shells;i+=1){
        a[i] = (-G*mass[i])/(2*pow(r[i],2));
        for(int j=0;j<num_shells;j+=1){
            if(i!=j & r[j]<r[i]){
                a[i]+=(-G*mass[j])/(pow(r[i],2));
            }
        }
    }
}

void initial_energy(const double* mass, const double* r, const double* v, double* energy, const int num_shells)
{
    double G = 6.67430e-11 ; //(m^3 kg^-1 s^-2)
    *energy=0;
    for(int i=0;i<num_shells;i+=1){
        *energy += (-G*pow(mass[i],2))/(2*r[i]);
        *energy += .5*mass[i]*pow(v[i],2);
    }
}

void evolve(double time, double dt, const double* mass, double* r, double* v, double* a, double* energy, const int num_shells)
{
    double G = 6.67430e-11 ; //(m^3 kg^-1 s^-2)
    float t=0,a_next;
    while(t<time){
        for(int i=0;i<num_shells;i+=1){
            r[i] = r[i]+v[i]*dt+0.5*a[i]*pow(dt,2);
            if(r[i]<1e-5){
                r[i]=0;
                v[i]=0;
                a[i]=0;
            }
        }
        for(int i=0;i<num_shells;i+=1){
            if(r[i]>0){
                a_next = (-G*mass[i])/(2*pow(r[i],2));
                for(int j=0;j<num_shells;j+=1){
                    if(i!=j & r[j]<r[i]){
                    a_next += (-G*mass[j])/(pow(r[i],2));}
                }
                v[i] = v[i]+0.5*(a[i]+a_next)*dt;
                a[i] = a_next;
            }
        }
        *energy=0;
        bool bad = false;
        for(int i=0;i<num_shells;i+=1){
            *energy += (-G*pow(mass[i],2))/(2*r[i]);
            *energy += .5*mass[i]*pow(v[i],2);
            if(r[i]==0){bad=true;}
        }
        if(bad){*energy=0;}
        t+=dt;
    }
}