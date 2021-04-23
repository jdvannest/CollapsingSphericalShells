#include "project.h"

using namespace std;

float round_up(float value)
{
    return(std::ceil(value * 100.0) / 100.0);
}

double yr_to_s(double years)
{
    return(years*31556952);
}

double s_to_yr(double seconds)
{
    return(seconds*3.17098e-8);
}

double AU_to_m(double AU)
{
    return(AU*149597870700);
}

double m_to_AU(double meters)
{
    return(meters*6.6845871222684e-12);
}

double Msol_to_kg(double Msol)
{
    return(Msol*1.98847e+30);
}

double kg_to_Msol(double kg)
{
    return(kg*5.0000000025e-31);
}