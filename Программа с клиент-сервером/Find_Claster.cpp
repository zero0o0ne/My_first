//211-Pushkareva-Anna-2021
#include "Find_Claster.h"

void Find_Claster::SetAlfa(double p)
{
    alfa = p;
}
string Find_Claster::GetS()
{
    return S;
}
void Find_Claster::SetS(string s)
{
    S = s;
}
void Find_Claster::Print(string& file_name)
{
    int i, j, k;
    ofstream f;
    ofstream com;
    // cout <<"void Find_Claster::Print(string &file_name)"<< endl;
    f.open(file_name.c_str());
    if (!f.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        //f.setprecision(6);
        k = 0;
        for (i = 0; i < Print_Point.size(); i++)
        {
            k = k + Print_Point[i].size();
            //cout<<"Print_Point["<<i<<"].size()="<<Print_Point[i].size()<<"\n";
        }
        //cout <<"Print_Point.size()="<<k<<endl;

        if (S == "Klassik Wave")
        {
            for (i = 0; i < Print_Point.size(); i++)
            {
                // cout<<i;
                for (j = 0; j < Print_Point[i].size(); j++)
                {
                    // cout <<"FC[i][j].GetX())="<<Print_Point[i][j].GetX()<< endl;
                    f << Print_Point[i][j].GetX() << "\t" << Print_Point[i][j].GetY() << "\t" << endl;

                }
                f << endl;
                f << endl;
                f << endl;
                f << endl;


            }





            f.close();

            string d = "Command_GP_";
            d = d + file_name.c_str();
            d.pop_back();
            d.pop_back();
            d.pop_back();
            //char c=".plt";
            d = d + "plt";
            com.open(d);
            //cout << "com.open('Command_GP_Claster.txt');" <<endl;
            if (!com.is_open())
            {
                cout << "Oshibka otkrytiya fila" << endl;
            }
            else
            {
                k = 0;
                com << "set xrange[-50:50] " << endl;
                com << "set yrange[-25:25] " << endl;
                com << " plot ";
                com << "'Point.txt' u 1:2 w p, '" << file_name << "' u 1:2 w linespoints" << endl;
                com << endl;
            }
            com.close();
            f.close();
        }

        if (S == "DBSCAN")
        {
            ofstream F[3];
            string M_0 = "B_";
            M_0 = M_0 + file_name.c_str();
            string M_1 = "P_";
            M_1 += file_name.c_str();
            string M_2 = "pyl_";
            M_2 += file_name.c_str();
            F[0].open(M_0);
            F[1].open(M_1);
            F[2].open(M_2);

            if (!F[0].is_open() && !F[1].is_open() && !F[2].is_open())
            {
                cout << "Oshibka otkrytiya fila" << endl;
            }
            string d;
            d = "Command_GP_";
            d = d + file_name.c_str();
            d.pop_back();
            d.pop_back();
            d.pop_back();
            //char c=".plt";
            d = d + "plt";
            //cout <<d<<endl;
            com.open(d);
            //cout << "com.open('Command_GP_Claster.txt');" <<endl;
            if (!com.is_open())
            {
                cout << "Oshibka otkrytiya fila" << endl;
            }
            else
            {
                k = 0;
                com << "set xrange[-50:50] " << endl;
                com << "set yrange[-25:25] " << endl;
                com << " plot ";
                com << "'Point.txt' u 1:2 w p, 'B_" << file_name << "' u 1:2 w p, 'P_" << file_name << "' u 1:2 w p, 'pyl_" << file_name << "' u 1:2 w p, '" << file_name << "' u 1:2 w linespoints " << endl;
                com << endl;
            }
            //cout<<"Print_Point.size()="<<Print_Point.size()<<endl;

            for (i = 0; i < Print_Point.size(); i++)
            {
                // cout<<i;
                for (j = 0; j < Print_Point[i].size(); j++)
                {
                    // cout <<"FC[i][j].GetX())="<<Print_Point[i][j].GetX()<< endl;
                    f << Print_Point[i][j].GetX() << "\t" << Print_Point[i][j].GetY() << "\t" << endl;
                    // cout<<"Print_Point["<<i<<"]["<<j<<"].GetTip()="<<Print_Point[i][j].GetTip()<<"\n";

                }
                f << endl;
                f << endl;
                f << endl;
                f << endl;


            }

            for (i = 0; i < Pyl.size(); i++)
            {
                F[2] << Pyl[i].GetX() << "\t" << Pyl[i].GetY() << "\t" << endl;
            }
            for (i = 0; i < Bas.size(); i++)
            {
                F[0] << Bas[i].GetX() << "\t" << Bas[i].GetY() << "\t" << endl;
            }
            for (i = 0; i < Peref.size(); i++)
            {
                F[1] << Peref[i].GetX() << "\t" << Peref[i].GetY() << "\t" << endl;
            }

            f.close();

            com.close();
            //cout<<"ok :) "<<endl;
            return;
        }
        if (S == "K_means")
        {

            string d = "Command_GP_";
            d = d + file_name.c_str();
            d.pop_back();
            d.pop_back();
            d.pop_back();
            d = d + "plt";
            com.open(d);
            com << "set xrange[-20:20] " << endl;
            com << "set yrange[-10:10] " << endl;
            com << "plot 'Point.txt' u 1:2 w p,";
            for (i = 0; i < Print_Point.size(); i++)
            {
                for (j = 0; j < Print_Point[i].size(); j++)
                {
                    f << Print_Point[i][j].GetX() << "  " << Print_Point[i][j].GetY() << "  " << endl;
                }
                f << endl;
                f << endl;
                f << endl;
                f << endl;

                com << "'" << file_name << "' index " << i << " w linespoints title '" << i << "' ,\\" << endl;

            }

            f.close();
            com.close();
            return;
        }
        if (S == "EM")
        {

            string d = "Command_GP_";
            d = d + file_name.c_str();
            d.pop_back();
            d.pop_back();
            d.pop_back();
            d = d + "plt";
            com.open(d);
            com << "set xrange[-20:20] " << endl;
            com << "set yrange[-10:10] " << endl;
            com << "plot 'Point.txt' u 1:2 w p,";
            for (i = 0; i < Print_Point.size(); i++)
            {
                for (j = 0; j < Print_Point[i].size(); j++)
                {
                    f << Print_Point[i][j].GetX() << "  " << Print_Point[i][j].GetY() << "  " << endl;
                }
                f << endl;
                f << endl;
                f << endl;
                f << endl;

                com << "'" << file_name << "' index " << i << " w linespoints title '" << i << "' ,\\" << endl;

            }

            f.close();
            com.close();
            return;
        }
    }
}
void Find_Claster::SetClaster(vector<Point>& A)
{
    Cluster C;
    FC.push_back(C);
    FC[FC.size() - 1].SetC(A);
    double x, y;
    x = y = 0;
    for (int i = 0; i < A.size(); i++)
    {
        x += A[i].GetX();
        y += A[i].GetY();
    }
    Point P(x / A.size(), y / A.size());
    FC[FC.size() - 1].SetCentr(P);
    double D, R, M;

    M = D = R = 0;
    vector <int> I;
    for (int k = 0; k < 4; k++) { I.push_back(0); }
    for (int i = 0; i < A.size(); i++)
    {
        int J=0;
        M = d(A[i], A[0]);
        for (int j = 0; j < A.size(); j++)
        {
            if (d(A[i], A[j]) != 0 && d(A[i], A[j]) > M) { M = d(A[i], A[j]); J = j; }
        }

        if (D < M) { D = M; I[0] = i; I[1] = J; }
        if (R == 0) { R = M; }
        if (R >= M) { R = M; I[2] = i; I[3] = J; }

    }
    for (int i = 0; i < 4; i++)
    {
        if (A.size() > 0) 
        { 
            FC[FC.size() - 1].Set_Pereferiya(A[I[i]]); 
        }
    }
    FC[FC.size() - 1].SetD(D);
    FC[FC.size() - 1].SetR(R);

    //cout<<"R="<<R<<" D="<<D<<" x="<<x<<" y="<<y<<endl;
}
void Find_Claster::SetPrint(vector<Point>& A)
{
    //cout<<"Print_Point.size()="<<Print_Point.size()<<endl;
    Print_Point.push_back(A);
}
void Find_Claster::SetPyl(Point& A)
{
    Pyl.push_back(A);
}
void Find_Claster::SetPeref(Point& A)
{
    Peref.push_back(A);
}
void Find_Claster::SetBas(Point& A)
{
    Bas.push_back(A);
}
int Find_Claster::GetPrintSize()
{
    return Print_Point.size();
}
void Find_Claster::Calc_Dist_Matrix()
{
    int n, k;
    int i, j, f;
    vector <double> r;
    double Min, Max = 0;
    double xx, yy;
    //cout<<"n=" << n <<endl;
    for (k = 0; k < FC.size(); k++)
    {
        n = FC[k].Size();
        vector <double> D;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                double x_1 = FC[k].GetX(i);
                double x_2 = FC[k].GetX(j);
                xx = (x_1 - x_2) * (x_1 - x_2);

                double y_1 = FC[k].GetY(i);
                double y_2 = FC[k].GetY(j);
                yy = (y_1 - y_2) * (y_1 - y_2);
                D.push_back(sqrt(xx + yy));
            }
        }

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("%15lf ", D[i * n + j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");

    }
}
