//211-Pushkareva-Anna-2021
#include "Point.h"
Point::Point()
{
   F= x = y = ID = 0;
    //tip = 0;
    //ves=1;
}
void Point::SetID(int n)
{
    //cout<<"void Point::SetID (int n)"<<endl;
    //cout<<"n="<<n<<endl;
    ID = n;
    //cout<<"ID="<<ID<<endl;
}

Point::Point(double xx, double yy)
{
    x = xx; y = yy;
}


Point::Point(const Point& p)
{
    x = p.x; y = p.y; ID = p.ID; F = p.F; Sosedi = p.Sosedi;
}
double Point::GetX()
{
    //cout <<"double Point::GetX()"<<endl;
    //cout <<"x="<<x<<endl;
    return x;
}
int Point::GetID()
{
    int n = ID;
    // cout <<n<< endl;
    return n;
}
double Point::GetY()
{
    return y;
}
const Point& Point::operator=(const Point& b)
{
    x = b.x;  y = b.y; ID = b.ID; F = b.F; //a=b.a;  //tip=b.tip;
    //Sosedi = b.Sosedi;
    return *this;
}
void Point::Print(FILE* f, int n)
{
    int k;
    k = 15 * n;

    printf("%15lf  %15lf  \n", x, y);
    fprintf(f, "%15lf  %15lf \n", x, y);
}
