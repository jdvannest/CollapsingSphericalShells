#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

void count_shells(int* num_shells);
void initialize_arrays(std::string* names, double* mass, double* r, double* v);
void evolve(double time, double dt,const double* mass, double* r, double* v, double* a, const int num_shells);
void time_params(double* time, double* dt, double* output_time);
void initial_acc(const double* mass, const double* r, double* a, const int num_shells);
double yr_to_s(double years);
double s_to_yr(double seconds);
double AU_to_m(double AU);
double m_to_AU(double meters);
double Msol_to_kg(double Msol);
double kg_to_Msol(double kg);