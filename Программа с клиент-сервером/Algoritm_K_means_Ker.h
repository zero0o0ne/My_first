
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"
#include "Find_Claster.h"
class Algoritm_K_means_Ker
{
public:
    Find_Claster Start(int k, int u, vector <Point>& All_Point);
    double d(Point& A, Point& B);
};


