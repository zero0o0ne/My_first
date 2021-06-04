
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"
class Cluster
{
private:
    vector <Point>  C;
    vector <double> Ind;
    double R;
    double D;
    Point centr;
    Point Min;
    Point Max;
    vector <Point> Pereferiya;
public:
    Cluster(const Cluster& p) = default;
    Cluster() = default;
    ~Cluster() = default;

    void SetR(const double& RR) { R = RR; }
    void SetD(const double& DD) { D = DD; }
    void SetCentr(const Point& cc) { centr = cc; }
    void SetC(vector <Point>& CC) { C = CC; }
    void SetMin(Point& PP) { Min = PP; }
    void SetMax(Point& PP) { Max = PP; }
    void Set_Pereferiya(Point& PP) { Pereferiya.push_back(PP); }

    vector <Point>  GetC() { return C; }
    double GetR() { return R; }
    double GetD() { return D; }
    Point GetCentr() { return centr; }
    double GetX(int i) { return C[i].GetX(); }
    double GetY(int i) { return C[i].GetY(); }
    Point GetMin() { return Min; }
    Point GetMax() { return Max; }
    Point GetPereferiya(int n) { return Pereferiya[n]; }
    int GetPerereferiyaSize() { return Pereferiya.size(); }

    int Size() { return C.size(); }

};

