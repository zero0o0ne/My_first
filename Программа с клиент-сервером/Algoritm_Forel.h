//211-Pushkareva-Anna-2021
#pragma once
#include "Point.h"
#include "Find_Claster.h"
class Algoritm_Forel
{
public:
    vector <Find_Claster> Start(double R, int n, vector <Point>& All_Point);
    double d(Point& A, Point& B);
};
