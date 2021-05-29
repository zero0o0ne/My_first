//211-Pushkareva-Anna-2021
#pragma once
#include "Find_Claster.h"
#include "Binary_Matrix.h"
#include "Point.h"
class Algoritm_Wave
{
private:

public:
    Find_Claster Start(int N, vector <Binary_Matrix> B, vector <Point> All_Point);
    int Graf_Volna_Chain(int N, int u, int t, vector <Point>& Claster, vector <Binary_Matrix>& B, vector <Point>& All_Point, Find_Claster& Q, vector <int>& A);
};


