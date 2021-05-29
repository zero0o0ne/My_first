//211-Pushkareva-Anna-2021
#pragma once
#include "Point.h";
#include "Triang_Delon.h"
#include "Algoritm_Triangulation.h" 
#include "stdio.h"
#include <cstdlib>
#include "cmath"
#include "Algoritm_Forel.h"
#include "Algoritm_K_means.h"
#include "Find_Claster.h"


class Regression
{
public:
	int Start (Point& P, vector <Point>& All_Point);
	double Evaluation (vector <Point>& All_Point);
	double d (Point& A, Point& B);

};

