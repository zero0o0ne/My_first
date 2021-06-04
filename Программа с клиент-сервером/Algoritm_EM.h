
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"
#include "Find_Claster.h"
#include <string>
#define pi 3.1415926535
class Algoritm_EM
{
public:
    Find_Claster Start(int k, vector <Point>& All_Point);
    double d(Point& A, Point& B);

};
