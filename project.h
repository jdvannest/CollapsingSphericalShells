#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cmath>
#include <vector>
#include <sstream>
#include <string>

void count_shells(int* num_shells);
void initialize_arrays(std::string* names, double* mass, double* r, double* v);
void evolve(double time, double dt, double* mass, double* r, double* v, double* a, const int num_shells);