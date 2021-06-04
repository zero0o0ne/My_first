
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Find_Claster.h"
#include "Binary_Matrix.h"
#include "Point.h"
class Algoritm_DBSCAN
{
public:
    Find_Claster Start(int k, int n, vector <Binary_Matrix>& B, vector <Point>& All_Point);
    int Graf_Volna_Chain_DB(int N, int u, int t, vector<Point>& Claster, vector <Binary_Matrix>& B, vector <Point>& All_Point, Find_Claster& Q, vector <double>& A, vector <double>& Tip);
};
