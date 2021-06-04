//Semenov Nikita 211
#include "Triangle.h"


int Triangle::Belongs(Point& PP)
{
   
    int k; 
    Point a = P[0];
    Point b = P[1];
    Point c = P[2];
    double ax = a.GetX();
    double ay = a.GetY();
    double bx = b.GetX();
    double by = b.GetY();
    double cx = c.GetX();
    double cy = c.GetY();
    if (!((ax == bx && ay == by) || (ax == cx && ay == cy) || (bx == cx && by == cy) || (ax == bx && bx == cx) || (ay == by && by == cy)))
    {
        //cout<<"2) if(!((ax"<<ax<<"==bx"<<bx<<" &&ay"<<ay<<"==by"<<by<<")||..."<<endl;
        Point S = IntersectL(ax - cx, ay - cy, (ax * ax - cx * cx + ay * ay - cy * cy) / 2, ax - bx, ay - by, (ax * ax - bx * bx + ay * ay - by * by) / 2);
        k = 0;
        if (d(S, PP) <= d(S, a)) k = 1;


        return k;
    }
    k = -1;
    return -1;
}
int Triangle::Belongs_S(Segment& PP)
{
    int k = 0;

    for (int i = 0; i < 3; i++)
    {
        if ((P[i].GetX() == PP.Get_A().GetX()) && (P[i].GetY() == PP.Get_A().GetY()))
        {
            k++;
        }
        if ((P[i].GetX() == PP.Get_B().GetX()) && (P[i].GetY() == PP.Get_B().GetY()))
        {
            k++;
        }
    }
    if (k == 2) return 1;
    else return 0;

}
int Triangle::Belongs_P(Point& A)
{
    int k = 1;
    P.push_back(P[0]);
    P.push_back(P[1]);
    for (int i = 0; i < 3; i++)
    {
        double a = ((P[i + 1].GetY() - P[i].GetY())*(A.GetX() - P[i].GetX()) - (P[i + 1].GetX() - P[i].GetX())*(A.GetY() - P[i].GetY()));
        double b = ((P[i + 1].GetY() - P[i].GetY())*(P[i+2].GetX() - P[i].GetX()) - (P[i + 1].GetX() - P[i].GetX())*(P[i+2].GetY() - P[i].GetY()));
        if (a * b <= 0) k = -1;
    }
    return k;
}
Point Triangle::IntersectL(double A, double B, double C, double A1, double B1, double C1)
{
    if (A != 0)
    {
        double g = ((A * C1) - (A1 * C)) / (A * B1 - A1 * B);

        Point P(C / A - ((B)*g / A), g);
        return P;
    }
    if (A == 0)
    {
        Point P(C1 / A1 - (B1 / A1) * (C * A1 - A * C1) / (B * A1 - A * B1), (C * A1 - A * C1) / (B * A1 - A * B1));
        return P;
    }
}
double Triangle::d(Point& A, Point& B)
{
    double xx, yy;
    double x_1 = A.GetX();
    double x_2 = B.GetX();
    xx = (x_1 - x_2) * (x_1 - x_2);

    double y_1 = A.GetY();
    double y_2 = B.GetY();
    yy = (y_1 - y_2) * (y_1 - y_2);
    return sqrt(xx + yy);
}
