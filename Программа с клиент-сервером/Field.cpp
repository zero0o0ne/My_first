//211-Pushkareva-Anna-2021
#include "Field.h"

double Field::MIN_X()
{
    int i;
    double Min = C[0].MIN_X();
    for (i = 0; i < NC; i++)
    {
        if (Min > C[0].MIN_X()) Min = C[0].MIN_X();
    }
    return Min;
}
double Field::MAX_X()
{
    int i;
    double Max = C[0].MAX_X();
    for (i = 0; i < NC; i++)
    {
        if (Max < C[i].MAX_X()) Max = C[i].MAX_X();
    }
    return Max;
}
double Field::MIN_Y()
{
    int i;
    double Min = C[0].MIN_Y();
    for (i = 0; i < NC; i++)
    {
        if (Min > C[i].MIN_Y()) Min = C[i].MIN_Y();
    }
    return Min;
}
double Field::MAX_Y()
{
    int i;
    double Max = C[0].MAX_Y();
    for (i = 0; i < NC; i++)
    {
        if (Max < C[i].MAX_Y()) Max = C[i].MAX_Y();
    }
    return Max;
}
void Field::Print_Cloud(string& file_name, int& n)
{
    C[n - 1].Print_Cloud(file_name);
}
Cloud& Field::GetCloud(int index)
{
    Cloud& f = C[index];
    return f;
}
void Field::SetCloud(Cloud& c)
{
    //cout <<"Sostoyanie"<<Sostoyanie<<endl;
    if (Sostoyanie == 1)
    {
        int i = 0;
        Point G;
        // printf("void Field::SetCloud(Cloud &c)\n");
       //printf("1c.GetSize() = %d\n",c.GetSize());
        for (i = 0; i < c.GetSize(); i++)
        {
            G = c.GetPoint(i);
            // printf("Namber_point=%d\n",Namber_point);
            G.SetID(Namber_point);
            // printf("Namber_point=%d\n",Namber_point);
            Namber_point++;
            // printf("x=%lf y=%lf ID=%d\n",G.GetX(),G.GetY(),G.GetID());
             //printf("3 %d\n",i);
            //printf("G.ID=%d\n",G.GetID());
            C[NC].SetPoint(G);
            //printf("C[NC].GetSize()-1=%d\n",C[NC].GetSize()-1);
            //printf("C[NC].ID=%d\n",C[NC].Get_Point_ID(C[NC].GetSize()-1));
            All_Point.push_back(G);

            //kghcvkh
 // printf("4 %d\n",i);

        }
        NC++;
        //cout <<"NC="<<NC<<endl;
    }
    if (Sostoyanie == 0)
    {
        cout << "Izmenenie polya v sostoyanii Analiza => oshibka " << endl;
        return;
    }

}
const Field& Field::operator=(const Field& b)
{
    //printf("const Field & Field::operator=(const Field &b)\n");



    int i;
    //printf("NC=%d\n",b.NC);
    for (i = 0; i < b.NC; i++)
    {
        //printf("7\n");
        C[i] = b.C[i];
        //printf("7\n");

    }
    //printf("b.NC=%d\n",b.NC);
    NC = b.NC;
    return *this;

}
Field::Field()
{
    NC = 0;
    NP = 0;
    Sostoyanie = 1;
}
int Field::Get_NP()
{
    int i;
    NP = 0;
    for (i = 0; i < NC; i++)
    {
        NP = NP + C[i].GetSize();
    }
    return NP;
}
int Field::GetSize()
{
    return NC;
}
void Field::Rotation(double centr_x, double centr_y, double a)
{
    // printf("void Field::Rotation(double centr_x, double centr_y, double a)");
    if (Sostoyanie == 0)
    {
        return;
    }
    int i;
    for (i = 0; i < NC; i++)
    {
        C[i].Rotation(centr_x, centr_y, a);
    }
}
void Field::Compr(double centr_x, double centr_y, double a)
{
    if (Sostoyanie == 0)
    {
        return;
    }
    int i;
    for (i = 0; i < NC; i++)
    {
        C[i].Compr(centr_x, centr_y, a);
    }
}
void Field::Move(double centr_x, double centr_y)
{
    if (Sostoyanie == 0)
    {
        return;
    }
    int i;
    //printf("void Field::Move(double centr_x, double centr_y)\n");
    //printf("NC=%d",NC);
    for (i = 0; i < NC; i++)
    {
        //printf("C[i].Move( centr_x, centr_y);");
        C[i].Move(centr_x, centr_y);
    }
}
void Field::Print_Field(string& file_name)
{
    int i, j, k;
    ofstream f;
    ofstream com;
    //cout <<"void Field::Print_Field(string & file_name)"<< endl;
    f.open(file_name.c_str());
    if (!f.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        //f.setprecision(6);
        //printf("i=%d/n",i);

        for (i = 0; i < NC; i++)
        {
            for (j = 0; j < C[i].GetSize(); j++)
            {
                // cout <<"C[i].Get_Point_ID(j)="<<C[i].Get_Point_ID(j)<< endl;
                f << C[i].Get_Point_X(j) << "\t" << C[i].Get_Point_Y(j) << "\t" << C[i].Get_Point_ID(j) << endl;

            }
            f << endl << endl;
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
        k = 0;
        com << "set xrange[-50:50] " << endl;
        com << "set yrange[-50:50] " << endl;
        com << " plot ";
        com << "'Point.txt' u 1:2 w p" << endl;
        for (i = 0; i < NC; i++)
        {

            //every ::"<< k<<"::" << C[i].GetSize()+k-1 << "w p" << ",";
            k = k + C[i].GetSize() - 1;
        }
        com << endl;
    }
    com.close();
}
void Field::Print_Claster(string& file_name, int n)
{
    //cout<<"\n"<<"void Field::Print_Claster(string & file_name, int n)"<<endl;
    double a = FC[n - 1].GetAlfa();
    FC[n - 1].Print(file_name);
}
int Field::GetSizeCloud(int n)
{
    int k;
    k = C[n].GetSize();
    //printf("k=C[n].GetSize()=%d\n",C[n].GetSize());
    return k;
}
int Field::NamPointX(double a, double b)
{
    //cout<<"int Field::NamPointX(double a,double b)"<< endl;
    int i, j, n;
    n = 0;
    for (i = 0; i < NC; i++)
    {
        // cout<<"NC="<<NC<<endl;
        n = n + C[i].NamPointX(a, b);
        //cout<<"n="<<n<<" i="<<i<<endl;
    }
    return n;

}



void Field::VectorX(int nx)
{

    double Min = MIN_X();
    //cout<<"Min="<< Min<< endl;
    double Max = MAX_X();
    double e;
    int i;
    e = (Max - Min) / nx;
    if (e < 0) e = e * (-1);
    // cout<<"e="<< e<< endl;
    for (i = 0; i < nx; i++)
    {
        XK.push_back(NamPointX(Min + e * i, Min + e * (i + 1)));
        // cout<<"XK["<<i<<"]="<<XK[i]<< endl;
    }

}
void Field::VectorX(int nx, int n)
{
    //  cout<<"Min="<< C[n].MIN_X()<< endl;
    double Min = C[n - 1].MIN_X();
    //cout<<"Min="<< Min<< endl;
    double Max = C[n - 1].MAX_X();
    double e;
    int i;
    e = (Max - Min) / nx;
    if (e < 0) e = e * (-1);
    //cout<<"e="<< e<< endl;
    for (i = 0; i < nx; i++)
    {
        XK.push_back(C[n - 1].NamPointX(Min + e * i, Min + e * (i + 1)));
        //cout<<"XK["<<i<<"]="<<XK[i]<< endl;
    }

}
int Field::NamPointY(double a, double b)
{
    // cout<<"int Field::NamPointY(double a,double b)"<< endl;
    int i, j, n;
    n = 0;
    for (i = 0; i < NC; i++)
    {

        n = n + C[i].NamPointY(a, b);
        //      cout<<"n="<<n<<" i="<<i<<endl;
    }
    return n;

}
void Field::VectorY(int ny, int n)
{

    double Min = C[n - 1].MIN_Y();
    //cout<<"Min="<< Min<< endl;
    double Max = C[n - 1].MAX_Y();
    double e;
    int i;
    e = (Max - Min) / ny;
    if (e < 0) { e = e * (-1); }
    // cout<<"e="<< e<< endl;
    for (i = 0; i < ny; i++)
    {
        YK.push_back(C[n - 1].NamPointY(Min + e * i, Min + e * (i + 1)));
        // cout<<"YK["<<i<<"]="<<YK[i]<< endl;
    }

}
int Cloud::NamPointY(double a, double b)
{
    int i, j, n;
    n = 0;
    for (i = 0; i < P.size(); i++)
    {
        if (P[i].GetY() < b && P[i].GetY() > a) n++;
    }
    return n;

}
void Field::VectorY(int ny)
{
    double Min = MIN_Y();
    //cout<<"Min="<< Min<< endl;
    double Max = MAX_Y();
    double e;
    int i;
    e = (Max - Min) / ny;
    if (e < 0) e = e * (-1);
    //cout<<"e="<< e<< endl;
    for (i = 0; i < ny; i++)
    {
        YK.push_back(NamPointY(Min + e * i, Min + e * (i + 1)));
        // cout<<"YK["<<i<<"]="<<YK[i]<< endl;
    }

}
void Field::Gistogram(string& file_name_x, string& file_name_y, double nx, double ny)
{
    //printf("void Field::Gistogram(string & file_name_x, string & file_name_y,double nx,double ny)\n");
    int i, j, k;
    ofstream f, g;
    ofstream com;
    VectorX(nx);
    VectorY(ny);
    f.open(file_name_x.c_str());
    g.open(file_name_y.c_str());
    if (!f.is_open() || (!g.is_open()))
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        for (i = 0; i < NC; i++)
        {
            for (j = 0; j < nx; j++)
            {
                f << XK[j] << endl;
            }
            for (j = 0; j < ny; j++)
            {
                g << YK[j] << endl;
            }
        }

    }
    f.close();
    g.close();

    com.open("Command_GP_Gist.txt");
    if (!com.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        k = 0;
        com << "set autoscale x" << endl;
        com << "set autoscale y " << endl;
        com << "set yrange[0:] " << endl;
        com << "set style data histogram" << endl;
        com << "set style fill solid " << endl;
        com << "set style fill solid " << endl;
        com << "set boxwidth 2" << endl;
        com << "plot 'Gist_x.txt', 'Gist_y.txt' " << endl;
        //printf("com <<plot 'Gist_x.txt', 'Gist_y.txt' << endl;\n");

    }
    com.close();
}
void Field::Gistogram(string& file_name_x, string& file_name_y, double nx, double ny, int n)
{
    //printf("void Field::Gistogram(string & file_name_x, string & file_name_y,double nx,double ny)\n");
    int j, k;
    ofstream f, g;
    ofstream com;
    //cout <<//"ny="<<ny<<" YK="<<YK.size()<<endl;
    //cout <<"n="<<n<<endl;
    VectorX(nx, n);
    VectorY(ny, n);
    //for(i=0;i<nx;i++) {cout<< XK[i]<< endl;}
   // printf("VectorY(ny)\n");
    f.open(file_name_x.c_str());
    g.open(file_name_y.c_str());
    if (!f.is_open() || (!g.is_open()))
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {

        for (j = 0; j < nx; j++)
        {
            f << XK[j] << endl;
        }
        for (j = 0; j < ny; j++)
        {
            g << YK[j] << endl;
        }

    }
    f.close();
    g.close();

    com.open("Command_GP_Gist.txt");
    if (!com.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        k = 0;
        com << "set autoscale x" << endl;
        com << "set autoscale y " << endl;
        com << "set yrange[0:] " << endl;
        com << "set style data histogram" << endl;
        com << "set style fill solid " << endl;
        com << "set style fill solid " << endl;
        com << "set boxwidth 10" << endl;
        com << "plot 'Gist_x.txt', 'Gist_y.txt' " << endl;
        // printf("com <<plot 'Gist_x.txt', 'Gist_y.txt' << endl;\n");

    }
    com.close();
    //printf("void Field::Gistogram(string & file_name_x, string & file_name_y,double nx,double ny)\n");

}
void Field::Calc_Dist_Matrix()
{
    Sostoyanie = 0;
    int n = Get_NP();
    int i, j;
    vector <double> r;
    double xx, yy;
    Point Cenr1[2], Peref[2];
    //cout<<"n=" << n <<endl;
    D.SetN(n);
    D.SetZ(1);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            double x_1 = All_Point[i].GetX();
            double x_2 = All_Point[j].GetX();
            xx = (x_1 - x_2) * (x_1 - x_2);

            double y_1 = All_Point[i].GetY();
            double y_2 = All_Point[j].GetY();
            yy = (y_1 - y_2) * (y_1 - y_2);
            D.Set(i, j, sqrt(xx + yy));
        }
    }

    /*
    int k,f;
     for(k=0;k<NC;k++)
     {
         vector<double> H;
         cout << "k="<<k<<endl;
         double min_1, min_2, max_1, max_2;
             //cout << "C[k].GetSize()="<<C[k].GetSize()<<endl;
             n=C[k].GetSize();

                 for(i=0;i<n;i++)
                 {
                     for(j=0;j<n;j++)
                     {
                       double x_1=C[k].Get_Point_X(i);
                       double x_2=C[k].Get_Point_Y(j);
                       xx=(x_1-x_2)*(x_1-x_2);

                       double y_1=C[k].Get_Point_X(i);
                       double y_2=C[k].Get_Point_Y(j);
                       yy=(y_1-y_2)*(y_1-y_2);
                       H.push_back(sqrt(xx+yy));
                     }
                 }
             //cout <<"H.size()="<<H.size()<<endl;
             for(i=0;i<n;i++)
             {
                for(j=0;j<n;j++)
                {
                   if(Max<H[i*n+j])
                   {
                       Max=H[i*n+j];
                       Centr[0]=All_Point[i];
                       Centr[1]=All_Point[j];
                   }
                }
                 r.push_back(Max);
             }
              //cout <<"r.size()="<<r.size()<<endl;
             C[k].Set_D(Max);
             Min=Max;

             for(i=0;i<n;i++)
             {
                if(Min>r[i]) Min=r[i];
             }
             C[k].Set_R(Min);

     }

     for(i=0;i<NC;i++)
     {
         printf("C[i].Get_D=%lf C[i].Get_R=%lf\n",C[i].Get_D(), C[i].Get_R());
     }*/




     /*for(i=0;i<n;i++)
     {
         for(j=0;j<n;j++)
         {
            printf("%15lf ",D.Get(i,j));
         }
         printf("\n");
     }*/

}
void Field::Binary(double R)
{
    //cout<<"void Field::Binary(double "<<R<<")"<<"\n";
    int i, j, n;
    Binary_Matrix U;
    n = Get_NP();
    U.SetN(n);
    U.SetR(R);

    if (D.GetZ() == 0) {
        cout << "Oshibka - Matrica D ne sozdana" << endl;
        return;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if ((D.Get(i, j) < R) && (D.Get(i, j) != 0)) { U.Set(i, j, 1); }

        }
    }
    B.push_back(U);
    /*for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
           cout << B[B.size()-1].Get(i,j)<<" ";
        }
        printf("\n");
    }*/
    //cout<< B.size()<<endl;
   //cout<< B.size()<<endl;

}

double Field::d(Point& A, Point& B)
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

void Field::Find_Factor()
{
    vector <Point> S_vector;
    vector <Point> Centr;
    for (int i = 0; i < Get_NC(); i++)
    {
        vector <double> Sigma;
        for (int g = 0; g < 4; g++)
        {
            Sigma.push_back(0);
        }

        for (int j = 0; j < C[i].GetSize(); j++)
        {
            Sigma[0] += C[i].Get_Point_X(j) * C[i].Get_Point_X(j);
            Sigma[1] += C[i].Get_Point_X(j) * C[i].Get_Point_Y(j);
            Sigma[2] += C[i].Get_Point_X(j) * C[i].Get_Point_Y(j);
            Sigma[3] += C[i].Get_Point_Y(j) * C[i].Get_Point_Y(j);
        }

        cout << Sigma[0] << " " << Sigma[1] << endl;
        cout << Sigma[2] << " " << Sigma[3] << endl << endl;
        double x_1, x_2;
        double centr_x, centr_y;
        centr_x = centr_y = 0;
        x_1 = (0.5 * ((Sigma[0] + Sigma[3]) + sqrt((Sigma[0] + Sigma[3]) * (Sigma[0] + Sigma[3]) - 4 * (Sigma[0] * Sigma[3] - Sigma[1] * Sigma[2]))));
        x_2 = (0.5 * ((Sigma[0] + Sigma[3]) - sqrt((Sigma[0] + Sigma[3]) * (Sigma[0] + Sigma[3]) - 4 * (Sigma[0] * Sigma[3] - Sigma[1] * Sigma[2]))));
        for (int j = 0; j < C[i].GetSize(); j++)
        {
            centr_x += C[i].Get_Point_X(j) / C[i].GetSize();
            centr_y += C[i].Get_Point_Y(j) / C[i].GetSize();
            //cout<<centr_x<<" "<<centr_y<<endl;
        }
        Point f(centr_x, centr_y);
        Centr.push_back(f);
        double fi = sqrt((-Sigma[1]) * (-Sigma[1]) + (-Sigma[2]) * (-Sigma[2]));
        Point p((x_1 / C[i].GetSize()) * (-Sigma[1]) / fi, (x_1 / C[i].GetSize()) * (Sigma[0] - x_1) / fi);
        S_vector.push_back(p);
        double si = sqrt((Sigma[3] - x_2) * (Sigma[3] - x_2) + (-Sigma[2]) * (-Sigma[2]));
        Point S((x_2 / C[i].GetSize()) * ((Sigma[3] - x_2)) / si, (x_2 / C[i].GetSize()) * (-Sigma[2] / si));
        S_vector.push_back(S);
        cout << "C[" << i << "]=" << C[i].GetSize() << endl;
        cout << x_1 << " " << x_2 << endl;
        cout << -Sigma[1] / C[i].GetSize() << " " << (Sigma[0] - x_1) / C[i].GetSize() << endl << endl;
    }

    string h = "Point.txt";
    Print_Field(h);
    ofstream com;
    string d = "Command_GP_";
    string file_name = "Find_Factor.plt";
    d = d + file_name.c_str();
    com.open(d);
    com << "set xrange[-20:20] " << endl;
    com << "set yrange[-10:10] " << endl;
    com << "plot 'Point.txt' u 1:2 w p,";
    com << " 'Find_Factor.txt' u 1:2 w linespoints," << endl;
    com.close();
    ofstream out;
    string de = "Find_Factor.txt";
    out.open(de);
    for (int h = 0; h < Get_NC(); h++)
    {
        out << Centr[h].GetX() << " " << Centr[h].GetY() << endl;
        out << Centr[h].GetX() + S_vector[2 * h].GetX() << " " << Centr[h].GetY() + S_vector[2 * h].GetY() << endl;
        out << Centr[h].GetX() << " " << Centr[h].GetY() << endl;
        out << Centr[h].GetX() + S_vector[2 * h + 1].GetX() << " " << Centr[h].GetY() + S_vector[2 * h + 1].GetY() << endl << endl << endl;
    }
    out.close();
}
int Field::Triangulation()
{
    //cout<<"int Field::Triangulation()"<<endl;
    double MIN_X, MAX_X, MIN_Y, MAX_Y;
    vector <Triangle> TR;
    vector <Triangle> TR20;
    MIN_X = All_Point[0].GetX();
    MAX_X = All_Point[0].GetX();
    MIN_Y = All_Point[0].GetX();
    MAX_Y = All_Point[0].GetX();
    for (int i = 0; i < All_Point.size(); i++)
    {
        if (MIN_X > All_Point[i].GetX()) MIN_X = All_Point[i].GetX();
        if (MAX_X < All_Point[i].GetX()) MAX_X = All_Point[i].GetX();
        if (MIN_Y > All_Point[i].GetY()) MIN_Y = All_Point[i].GetY();
        if (MAX_Y < All_Point[i].GetY()) MAX_Y = All_Point[i].GetY();
    }
    MIN_X = MIN_X - 10;
    MIN_Y = MIN_Y - 10;
    MAX_X = MAX_X + 10;
    MAX_Y = MAX_Y + 50;
    //cout<<MAX_Y<<endl;
    Point A, B, C;
    if (fabs(MAX_X - MIN_X) > (MAX_Y - MIN_Y))
    {
        A.SetX(2 * MIN_X - fabs(MAX_X - MIN_X));
        A.SetY(2 * MAX_Y);
        B.SetX(2 * MAX_X + fabs(MAX_X - MIN_X));
        B.SetY(2 * MAX_Y);
        C.SetX(MIN_X + fabs(MAX_X - MIN_X) * 0.5);
        C.SetY(MAX_Y - 1.8 * fabs(MAX_X - MIN_X) * 2);
    }
    if (fabs(MAX_X - MIN_X) <= (MAX_Y - MIN_Y))
    {
        A.SetX((MIN_X + MAX_Y) - 2 * fabs(MAX_Y - MIN_Y));
        A.SetY(2 * MAX_Y);
        B.SetX((MIN_X + MAX_Y) + 2 * fabs(MAX_Y - MIN_Y));
        B.SetY(2 * MAX_Y);
        C.SetX(0.5 * (MIN_X + MAX_Y));
        C.SetY(MAX_Y - 1.8 * fabs(MAX_Y - MIN_Y) * 2);
    }

    //cout<<"A=("<<A.GetX()<<", "<<A.GetY()<<") , B=("<<B.GetX()<<" ,"<<B.GetY()<<")"<<" , C=("<<C.GetX()<<" ,"<<C.GetY()<<")"<<endl;
    //cout<<"MIN=("<<MIN_X<<", "<<MIN_Y<<") MAX=("<<MAX_X<<", "<<MAX_Y<<")"<<endl;
    Triangle F;
    F.Set_P(A);
    F.Set_P(B);
    F.Set_P(C);
    F.Set_I(-1);
    TR.push_back(F);
    vector <Segment> Obolochka;
    Segment OB;
    OB.Set_A(A);
    OB.Set_B(B);
    Obolochka.push_back(OB);
    OB.Set_A(B);
    OB.Set_B(C);
    Obolochka.push_back(OB);
    OB.Set_A(C);
    OB.Set_B(A);
    Obolochka.push_back(OB);
    for (int i = 0; i < All_Point.size(); i++)
    {
        vector <Segment> Rbr;
        vector <int> Int;
        //cout<<"TR.size()="<<TR.size()<<endl;
        for (int j = 0; j < TR.size(); j++)
        {
            if (TR[j].Belongs(All_Point[i]) == 1)
            {
                //cout<<"Rbr.size()="<<Rbr.size()<<" "<<TR[j].Belongs(All_Point[i])<<endl;
                Segment Seg;
                int k = 0;
                Seg.Set_A(TR[j].Get_P(0));
                Seg.Set_B(TR[j].Get_P(1));
                if (k == 0) Rbr.push_back(Seg);

                Seg.Set_A(TR[j].Get_P(1));
                Seg.Set_B(TR[j].Get_P(2));
                if (k == 0) Rbr.push_back(Seg);

                Seg.Set_A(TR[j].Get_P(2));
                Seg.Set_B(TR[j].Get_P(0));

                if (k == 0) Rbr.push_back(Seg);
                Int.push_back(j);
                // cout<<"Rbr.size()="<<Rbr.size()<<endl;
            }
        }

        for (int k = 0; k < Int.size(); k++)
        {
            for (int g = 0; g < Int.size() - 1; g++)
            {
                if (Int[g] < Int[g + 1])
                {
                    int a = Int[g + 1];
                    Int[g + 1] = Int[g];
                    Int[g] = a;
                }
            }
        }

        //    for(int k=0; k<Int.size(); k++)
        //    {
        //        cout<<"Int["<<k<<"]="<<Int[k]<<endl;
        //    }
        for (int p = 0; p < Int.size(); p++)
        {
            for (int k = Int[p]; k < TR.size() - 1; k++)
            {
                TR[k] = TR[k + 1];
            }
            if (TR.size() > 1) TR.pop_back();

        }
        //cout<<"TR.size()="<<TR.size()<<endl;
        string s = "TR_";
        string b = to_string(2 * i);
        s = s + b;
        s = s + ".txt";
        string fi = s;
        fi.pop_back();
        fi.pop_back();
        fi.pop_back();
        fi = fi + "plt";
        ofstream g1, h1;
        g1.open(s);
        h1.open(fi);
        h1 << "set xrange[" << A.GetX() - 5 << ":" << B.GetX() + 5 << "] " << endl;
        h1 << "set yrange[" << C.GetY() - 5 << ":" << B.GetY() + 5 << "] " << endl;
        h1 << "plot 'Point.txt', 'TR_" << 2 * i << ".txt' u 1:2 w lp," << endl;
        for (int j = 0; j < TR.size(); j++)
        {
            //    if((!(TR[j].Get_P(0).GetX()==A.GetX()|| TR[j].Get_P(1).GetX()==A.GetX()||TR[j].Get_P(2).GetX()==A.GetX()))
            //     &&(!(TR[j].Get_P(0).GetX()==B.GetX()|| TR[j].Get_P(1).GetX()==B.GetX()||TR[j].Get_P(2).GetX()==B.GetX()))
            //     &&(!(TR[j].Get_P(0).GetY()==C.GetY()|| TR[j].Get_P(1).GetY()==C.GetY()||TR[j].Get_P(2).GetY()==C.GetY())) )
            //    {
            g1 << TR[j].Get_P(0).GetX() << " " << TR[j].Get_P(0).GetY() << endl;
            g1 << TR[j].Get_P(1).GetX() << " " << TR[j].Get_P(1).GetY() << endl;
            g1 << TR[j].Get_P(2).GetX() << " " << TR[j].Get_P(2).GetY() << endl;
            g1 << TR[j].Get_P(0).GetX() << " " << TR[j].Get_P(0).GetY() << endl;
            g1 << endl << endl;
            //   }

        }
        g1.close();
        h1.close();

        //    cout<<"TR.size()="<<TR.size()<<" Rbr.size()="<<Rbr.size()<<endl;
        //    cout<<"TR20.size()="<<TR20.size()<<endl;
        for (int k = 0; k < Rbr.size(); k++)
        {
            for (int s = 0; s < TR.size(); s++)
            {
                if (TR[s].Belongs_S(Rbr[k]) == 1)
                {
                    Triangle F;
                    F.Set_P(Rbr[k].Get_A());
                    F.Set_P(Rbr[k].Get_B());
                    F.Set_P(All_Point[i]);
                    //                    cout<<"A=("<<Rbr[k].Get_A().GetX()<<", "<<Rbr[k].Get_A().GetY()<<")"<<endl;
                    //                    cout<<"B=("<<Rbr[k].Get_B().GetX()<<", "<<Rbr[k].Get_B().GetY()<<")"<<endl;
                    TR20.push_back(F);
                }
            }
        }
        //    cout<<"TR20.size()="<<TR20.size()<<endl;
        for (int p = 0; p < TR20.size(); p++)
        {
            TR.push_back(TR20[p]);
        }
        if (i == 0)
        {
            for (int p = 0; p < TR.size() - 1; p++)
            {
                TR[p] = TR[p + 1];
            }
            if (TR.size() > 1) TR.pop_back();
        }

        for (int p = 0; p < 3; p++)
        {
            int s = 0;
            for (int k = 0; k < TR.size(); k++)
            {
                if (TR[k].Belongs_S(Obolochka[p]) == 1) s = 1;
            }
            if (s == 0)
            {
                Triangle F;
                F.Set_P(Obolochka[p].Get_A());
                F.Set_P(Obolochka[p].Get_B());
                F.Set_P(All_Point[i]);
                //            cout<<"A=("<<Obolochka[p].Get_A().GetX()<<", "<<Obolochka[p].Get_A().GetY()<<")"<<endl;
                //            cout<<"B=("<<Obolochka[p].Get_B().GetX()<<", "<<Obolochka[p].Get_B().GetY()<<")"<<endl;
                TR.push_back(F);
            }
        }

        Rbr.clear();
        Int.clear();
        TR20.clear();
        //   cout<<"TR.size()="<<TR.size()<<endl;
        //   cout<<"TR20.size()="<<TR20.size()<<endl;
        //   cout<<"Rbr.size()="<<Rbr.size()<<endl;
        //   cout<<"Int.size()="<<Int.size()<<endl<<endl<<endl;
        s = "TR_";
        b = to_string(2 * i + 1);
        s = s + b;
        s = s + ".txt";
        fi = s;
        fi.pop_back();
        fi.pop_back();
        fi.pop_back();
        fi = fi + "plt";
        g1, h1;
        g1.open(s);
        h1.open(fi);
        h1 << "set xrange[" << A.GetX() - 5 << ":" << B.GetX() + 5 << "] " << endl;
        h1 << "set yrange[" << C.GetY() - 5 << ":" << B.GetY() + 5 << "] " << endl;
        h1 << "plot 'Point.txt', 'TR_" << 2 * i + 1 << ".txt' u 1:2 w lp," << endl;
        for (int j = 0; j < TR.size(); j++)
        {
            //    if((!(TR[j].Get_P(0).GetX()==A.GetX()|| TR[j].Get_P(1).GetX()==A.GetX()||TR[j].Get_P(2).GetX()==A.GetX()))
            //     &&(!(TR[j].Get_P(0).GetX()==B.GetX()|| TR[j].Get_P(1).GetX()==B.GetX()||TR[j].Get_P(2).GetX()==B.GetX()))
            //     &&(!(TR[j].Get_P(0).GetY()==C.GetY()|| TR[j].Get_P(1).GetY()==C.GetY()||TR[j].Get_P(2).GetY()==C.GetY())) )
            //    {
            g1 << TR[j].Get_P(0).GetX() << " " << TR[j].Get_P(0).GetY() << endl;
            g1 << TR[j].Get_P(1).GetX() << " " << TR[j].Get_P(1).GetY() << endl;
            g1 << TR[j].Get_P(2).GetX() << " " << TR[j].Get_P(2).GetY() << endl;
            g1 << TR[j].Get_P(0).GetX() << " " << TR[j].Get_P(0).GetY() << endl;
            g1 << endl << endl;
            //   }

        }
        g1.close();
        h1.close();

        //cout<<"Int.size()="<<Int.size()<<endl<<endl<<endl;
        //cout<<"nagmite dlya prodolgeniya"<<endl;
        //int a;
        //scanf("%d",&a);
        //cout<<"Rbr.size()="<<Rbr.size()<<endl<<endl<<endl;
    }

    //char o;
    //cout<<"nagmite dlya prodolgeniya"<<endl;
    //scanf("%s",&o);
    ofstream g, h;
    g.open("TR.txt");
    h.open("TR.plt");
    h << "set xrange[" << A.GetX() - 5 << ":" << B.GetX() + 5 << "] " << endl;
    h << "set yrange[" << C.GetY() - 5 << ":" << B.GetY() + 5 << "] " << endl;
    h << "plot 'Point.txt', 'TR.txt' u 1:2 w lp," << endl;
    for (int j = 0; j < TR.size(); j++)
    {
        if ((!(TR[j].Get_P(0).GetX() == A.GetX() || TR[j].Get_P(1).GetX() == A.GetX() || TR[j].Get_P(2).GetX() == A.GetX()))
            && (!(TR[j].Get_P(0).GetX() == B.GetX() || TR[j].Get_P(1).GetX() == B.GetX() || TR[j].Get_P(2).GetX() == B.GetX()))
            && (!(TR[j].Get_P(0).GetY() == C.GetY() || TR[j].Get_P(1).GetY() == C.GetY() || TR[j].Get_P(2).GetY() == C.GetY())))
        {
            g << TR[j].Get_P(0).GetX() << " " << TR[j].Get_P(0).GetY() << endl;
            g << TR[j].Get_P(1).GetX() << " " << TR[j].Get_P(1).GetY() << endl;
            g << TR[j].Get_P(2).GetX() << " " << TR[j].Get_P(2).GetY() << endl;
            g << TR[j].Get_P(0).GetX() << " " << TR[j].Get_P(0).GetY() << endl;
            g << endl << endl;
        }

    }
    //cout<<"TR.size()="<<TR.size()<<endl;

    string Animate = "Triangulation_Animate.plt";
    ofstream Anim;
    Anim.open(Animate);
    Anim << "set xrange[" << A.GetX() - 5 << ":" << B.GetX() + 5 << "] " << endl;
    Anim << "set yrange[" << C.GetY() - 5 << ":" << B.GetY() + 5 << "] " << endl;
    Anim << "set term gif animate optimize delay 15 background \"#ffeedf\" font \" Times-Roman,10 \" size 1280,960 " << endl;
    Anim << "set output \"Triangulation_algoritm.gif\" " << endl;
    Anim << "set size square" << endl;
    Anim << "set title \"Triangulation-algoritm\" " << endl;
    Anim << "do for[i=0:" << 4 * All_Point.size() << "]{" << endl;
    Anim << "plot 'Point.txt', 'TR_'.i.'.txt' u 1:2 w lp," << endl;
    Anim << "}" << endl;

    return 0;
}

Point Field::IntersectL(double A, double B, double C, double A1, double B1, double C1)
{

    //cout<<"("<<((A*C1)-(A1*C))/(A*B1-A1*B)<<")=y"<<endl;
   // cout<<"L_1: "<<A<<"x+ "<<B<<"y ="<<C<<endl;
    //cout<<"L_2: "<<A1<<"x+ "<<B1<<"y ="<<C1<<endl;
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

Point Field::Intersection_Parabol(Point Focus, Point Focus_R, Point Focus_L, double d)
{
    double a, b, c, a1, b1, c1, A, B;

    //    cout<<" Focus="<<Focus.GetX()<<","<<Focus.GetY()<<endl;
    //    cout<<" Focus_R="<<Focus_R.GetX()<<","<<Focus_R.GetY()<<endl;
    //    cout<<" Focus_L="<<Focus_L.GetX()<<","<<Focus_L.GetY()
    cout << " d=" << d << endl;
    double x_0 = Focus.GetX();
    double y_0 = Focus.GetY();
    double x_1 = Focus_R.GetX();
    double y_1 = Focus_R.GetY();
    double x_2 = Focus_L.GetX();
    double y_2 = Focus_L.GetY();
    if (Focus_R.GetX() == Focus_L.GetX() && Focus_R.GetY() == Focus_L.GetY())
    {
        cout << "Vlogennye paraboly:" << endl;
        a = 0.5 / (y_0 - d);
        a1 = 0.5 / (y_1 - d);
        b = x_0 / (d - y_0);
        b1 = x_1 / (d - y_1);
        c = 0.5 * (x_0 * x_0 + y_0 * y_0 - d * d) / (y_0 - d);
        c1 = 0.5 * (x_1 * x_1 + y_1 * y_1 - d * d) / (y_1 - d);
        cout << "" << a << "x^2+ " << b << "x+ " << c << endl;
        cout << "" << a1 << "x^2+ " << b1 << "x+ " << c1 << endl;
        a = a - a1;
        b = b - b1;
        c = c - c1;
        //cout<<""<<a<<"x^2+ "<<b<<"x+ "<<c<<"=0"<<endl<<endl;
        if (a != 0)
        {
            A = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
            B = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        }
        else
        {
            A = (-c) / b;
            B = A;
        }

        Point AB;
        AB.SetX(A);
        AB.SetY(B);
        return AB;
    }
    else
    {
        cout << "Smegnye paraboly:" << endl;
        a = 0.5 / (y_0 - d);
        a1 = 0.5 / (y_1 - d);
        b = x_0 / (d - y_0);
        b1 = x_1 / (d - y_1);
        c = 0.5 * (x_0 * x_0 + y_0 * y_0 - d * d) / (y_0 - d);
        c1 = 0.5 * (x_1 * x_1 + y_1 * y_1 - d * d) / (y_1 - d);
        cout << "" << a << "x^2+ " << b << "x+ " << c << endl;
        cout << "" << a1 << "x^2+ " << b1 << "x+ " << c1 << endl;
        a = a - a1;
        b = b - b1;
        c = c - c1;
        //cout<<""<<a<<"x^2+ "<<b<<"x+ "<<c<<"=0"<<endl<<endl;
        if (a != 0)
        {
            A = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
            B = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        }
        else
        {
            A = (-c) / b;
            B = A;
        }

        if (a * A * A + b * A + c < a * B * B + b * B + c) B = A;
        Point AB;
        AB.SetY(B);

        a = 0.5 / (y_0 - d);
        a1 = 0.5 / (y_2 - d);
        b = x_0 / (d - y_0);
        b1 = x_2 / (d - y_2);
        c = 0.5 * (x_0 * x_0 + y_0 * y_0 - d * d) / (y_0 - d);
        c1 = 0.5 * (x_2 * x_2 + y_2 * y_2 - d * d) / (y_2 - d);
        cout << "" << a << "x^2+ " << b << "x+ " << c << endl;
        cout << "" << a1 << "x^2+ " << b1 << "x+ " << c1 << endl;
        a = a - a1;
        b = b - b1;
        c = c - c1;
        //cout<<""<<a<<"x^2+ "<<b<<"x+ "<<c<<"=0"<<endl<<endl;
        if (a != 0)
        {
            A = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
            B = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        }
        else
        {
            A = (-c) / b;
            B = A;
        }

        if (a * A * A + b * A + c < a * B * B + b * B + c) B = A;

        AB.SetX(B);
        return AB;
    }
}

