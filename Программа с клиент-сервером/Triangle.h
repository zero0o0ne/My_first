//Semenov Nikita 211
#pragma once
#include "Point.h"
#include "Segment.h"
class Triangle
{
private:
    vector <Point> P;
    int I;
public:
    Triangle(const Triangle& p) = default;
    Triangle() = default;
    ~Triangle() = default;
    void Set_P(const Point& PP)
    {
        P.push_back(PP);
    }
    Point Get_P(int n) { return P[n]; }
    int Get_N() { return P.size(); }
    int Belongs(Point& PP);
    void Set_I(int i)
    {
        I = i;
    }
    int Get_I() { return I; }
    Point IntersectL(double A, double B, double C, double A1, double B1, double C1);
    double d(Point& A, Point& B);
    int Belongs_S(Segment& PP);
    int Belongs_P(Point& A);
};

