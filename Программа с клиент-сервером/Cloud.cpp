//211-Pushkareva-Anna-2021
#include "Cloud.h"

Cloud::Cloud()
{
    R = D = NP = 0;
}
Cloud::Cloud(const Cloud& C)
{
    int i, n;
    n = C.GetSize();
    for (i = 0; i < n; i++)
    {
        P[i] = C.P[i];
    }
}
Point& Cloud::GetPoint(int index)
{
    Point& S = P[index];
    return S;
}
void Cloud::SetPoint(Point& p)
{
    //printf("void Cloud::SetPoint( Point &p) \n");
      //printf("p.ID=%d\n",p.GetID());
    P.push_back(p);
    //printf("P.[P.size()-1].GetID()=%d P.[P.size()-1].GetX()=%d \n",P[P.size()-1].GetID(),P[P.size()-1].GetX());

  //printf("P.size()=%d\n",P.size());
  //printf("\n");

   // printf("x=%lf y=%lf index=%d\n",P[index].GetX(),P[index].GetY(),index);
}
const Cloud& Cloud::operator=(const Cloud& b)
{
    int i, n;
    vector<Point>::iterator it;
    it = P.begin();
    n = b.GetSize();
    //printf("n=%d",n);
 // printf("C size=%d b.C size=%d\n",P.size(),b.GetSize());
    if (P.size() != b.GetSize())
    {
        for (i = 0; i < n; i++)
        {  //printf("P[i]=b.P[i];\n");
            it = P.begin() + i;
            P.insert(it, b.P[i]);
            // printf("x=%lf y=%lf\n", P[i].GetX(), P[i].GetY());
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {  //printf("P[i]=b.P[i];\n");
           //it=P.begin()+i;
            P[i] = b.P[i];
            // printf("x=%lf y=%lf\n", P[i].GetX(), P[i].GetY());
        }
    }

    //printf("C size=%d b.C size=%d\n",P.size(),b.GetSize());
    return *this;
}
int Cloud::NamPointX(double a, double b)
{
    int i, j, n;
    n = 0;
    for (i = 0; i < P.size(); i++)
    {
        if (P[i].GetX() < b && P[i].GetX() > a) n++;
    }
    return n;

}
int Cloud::GetSize()
{
    return P.size();
}
int Cloud::GetSize() const
{
    return P.size();
}
void Cloud::Rotation(double centr_x, double centr_y, double a)
{
    //printf("void Cloud::Rotation(double centr_x, double centr_y, double a)\n");
    int i;
    //printf("P.size()=%d\n",P.size());
    for (i = 0; i < P.size(); i++)
    {
        double x, y;
        x = cos(a) * (P[i].GetX() - centr_x) - sin(a) * (P[i].GetY() - centr_y) + centr_x;
        y = sin(a) * (P[i].GetX() - centr_x) + cos(a) * (P[i].GetY() - centr_y) + centr_y;
        Point p(x, y);
        P[i] = p;
    }
    //("P.size()=%d\n",P.size());

}
void Cloud::Compr(double centr_x, double centr_y, double a)
{
    // printf("void Cloud::Compr(double centr_x, double centr_y, double a)\n");
    int i;
    //printf("P.size()=%d\n",P.size());
    for (i = 0; i < P.size(); i++)
    {
        double x, y;
        x = P[i].GetX() + ((P[i].GetX() - centr_x) / (sqrt((P[i].GetX() - centr_x) * (P[i].GetX() - centr_x) + (P[i].GetY() - centr_y) * (P[i].GetY() - centr_y)))) * a;
        y = P[i].GetY() + ((P[i].GetY() - centr_y) / sqrt((P[i].GetX() - centr_x) * (P[i].GetX() - centr_x) + (P[i].GetY() - centr_y) * (P[i].GetY() - centr_y))) * a;
        Point p(x, y);
        P[i] = p;
    }

}
void Cloud::Move(double centr_x, double centr_y)
{
    int i;
    //  printf("%d\n",P.size());
    for (i = 0; i < P.size(); i++)
    {
        double x, y;
        x = P[i].GetX() + centr_x;
        y = P[i].GetY() + centr_y;
        Point p(x, y);
        // printf("cx=%d cy=%d\n",centr_x,centr_y);
        // printf("x=%d y=%d\n",x,y);
        P[i] = p;
    }

}
double Cloud::Get_Point_X(int n)
{
    return P[n].GetX();
}
double Cloud::Get_Point_Y(int n)
{
    return P[n].GetY();
}
int Cloud::Get_Point_ID(int n)
{
    return P[n].GetID();
}
double Cloud::MAX_X()
{
    int i;
    double Max = P[0].GetX();
    for (i = 0; i < P.size(); i++)
    {
        if (Max < P[i].GetX()) Max = P[i].GetX();
    }
    return Max;
}
double Cloud::MAX_Y()
{
    int i;
    double Max = P[0].GetY();
    for (i = 0; i < P.size(); i++)
    {
        if (Max < P[i].GetY()) Max = P[i].GetY();
    }
    return Max;
}
double Cloud::MIN_Y()
{
    int i;
    double Min = P[0].GetY();
    for (i = 0; i < P.size(); i++)
    {
        if (Min > P[i].GetY()) Min = P[i].GetY();
    }
    return Min;
}
double Cloud::MIN_X()
{
    //cout <<"double Cloud::MIN_X()"<<endl;
    int i;
    // cout<<"P[0]="<<endl;
     //cout <<"Min=P[0].GetX()"<<P[0].GetX()<<endl;
    double Min = P[0].GetX();
    for (i = 0; i < P.size(); i++)
    {
        if (Min > P[i].GetX()) Min = P[i].GetX();
    }
    return Min;
}
void Cloud::Print_Cloud(string& file_name)
{
    int j;
    ofstream f;
    ofstream com;

    f.open(file_name.c_str());
    if (!f.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        for (j = 0; j < P.size(); j++)
        {
            f << P[j].GetX() << " " << P[j].GetY() << endl;

        }
    }
    f.close();

    com.open("Command_GP.txt");
    if (!com.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        com << "set xrange[-50:50] " << endl;
        com << "set yrange[-50:50] " << endl;
        com << " plot 'Point.txt' " << "u 1:2 w p, " << endl;
    }
    com.close();

}
double Cloud::Get_R()
{
    return R;
}
double Cloud::Get_D()
{
    return D;
}
void Cloud::Set_R(double n)
{
    R = n;
}
void Cloud::Set_D(double n)
{
    D = n;
}
