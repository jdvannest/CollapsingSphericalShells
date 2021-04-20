#include "project.h"

using namespace std;

void evolve(double time, double dt, double* mass, double* r, double* v, double* a, const int num_shells)
{
    double G = 4.30091e-3; //pc (km/s)^2 Msol^-1
    float t=0,int_a;
    while(t<time){
        for(int i=0;i<num_shells;i+=1){
            r[i] = r[i]+v[i]*dt+0.5*a[i]*pow(dt,2);
            int_a = (-G*.5*mass[i])/(pow(2*r[i],2));
            for(int j=0;j<num_shells;j+=1){
                if(i!=j & r[j]<r[i]){
                int_a += (-G*mass[j])/(pow(r[i],2));}
            }
            v[i] = v[i]+0.5*(a[i]+int_a);
            a[i] = int_a;
            if(r[i]<0){
                r[i]=0;
                v[i]=0;
                a[i]=0;
            }
        }
        t+=dt;
    }
}