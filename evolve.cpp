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
        *energy += .5*mass[i]*pow(v[i],2);
        for(int j=0;j<num_shells;j+=1){
            if(j!=i & r[j]<r[i]){
                *energy += (-G*mass[j]*mass[i])/r[i];
            }
        }
    }
}

void evolve(double time, double dt, const double* mass, double* r, double* v, double* a, double* energy, const int num_shells)
{
    double G = 6.67430e-11 ; //(m^3 kg^-1 s^-2)
    float t=0,a_next;
    while(t<time){
        //Calculate new radii for all shells
        for(int i=0;i<num_shells;i+=1){
            r[i] = r[i]+v[i]*dt+0.5*a[i]*pow(dt,2);
            if(r[i]<1){
                r[i]=1;
                v[i]=0;
                a[i]=0;
            }
        }
        //Calculate new accelerations and velocities
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
        //Calculate new system energy
        *energy=0;
        for(int i=0;i<num_shells;i+=1){
            *energy += .5*mass[i]*pow(v[i],2);
            for(int j=0;j<num_shells;j+=1){
                if(j!=i & r[j]<r[i]){
                    *energy += (-G*mass[j]*mass[i])/r[i];
                }
            }
        }
        //Advance to next time step
        t+=dt;
    }
}