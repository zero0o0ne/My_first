
//Programma Semenova Nikity iz 211 gruppy
#include "H_Point.h"

H_Point::H_Point()
{
    tree = x = y = ID = a = b = 0;
    //tip = 0;
    ves = 1;
}
void H_Point::SetID(int n)
{
    //cout<<"void Point::SetID (int n)"<<endl;
    //cout<<"n="<<n<<endl;
    ID = n;
    //cout<<"ID="<<ID<<endl;
}
//void Point::SetTip(int n)
//{
//    tip=n;
//}
H_Point::H_Point(double xx, double yy)
{
    x = xx; y = yy;
}
void H_Point::SetA(int n)
{
    a = n;
}
int H_Point::GetA()
{
    return a;
}

H_Point::H_Point(const H_Point& p)
{
    x = p.x; y = p.y; ID = p.ID; //tip=p.tip;
    a = p.a; tree = p.tree; ves = p.ves;
}
double H_Point::GetX()
{
    //cout <<"double Point::GetX()"<<endl;
    //cout <<"x="<<x<<endl;
    return x;
}
int H_Point::GetID()
{
    int n = ID;
    // cout <<n<< endl;
    return n;
}
double H_Point::GetY()
{
    return y;
}
const H_Point& H_Point::operator=(const H_Point& b)
{
    x = b.x;  y = b.y; ID = b.ID; a = b.a;  //tip=b.tip;
    tree = b.tree;
    return *this;
}
void H_Point::Print(FILE* f, int n)
{
    int k;
    k = 15 * n;

    printf("%15lf  %15lf  \n", x, y);
    fprintf(f, "%15lf  %15lf \n", x, y);
}
