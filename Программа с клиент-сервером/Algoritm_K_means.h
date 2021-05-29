//211-Pushkareva-Anna-2021
#pragma once
#include "Point.h"
#include "Find_Claster.h"
#include <string>
class Algoritm_K_means
{
public:
    Find_Claster Start(int k, vector <Point>& All_Point);
    double d(Point& A, Point& B);
};
