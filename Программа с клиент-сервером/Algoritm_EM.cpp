//211-Pushkareva-Anna-2021
#include "Algoritm_EM.h"

using namespace std;

//std::to_string();
#define E 0.01
Find_Claster Algoritm_EM::Start(int k, vector <Point>& All_Point)
{
    vector <double> W;
    vector <double> Mu;
    vector < vector <double> > Sigma;
    vector < vector <double> > A;
    vector < vector <double> > AA;
    vector < vector <double> > Sigma_1;
    vector < vector <double> > P_x_c;
    int n = 0;
    for (int i = 0; i < k; i++)
    {
        double m = 1;
        W.push_back(m / k);
    }
    for (int j = 0; j < k; j++)
    {
        vector <double> C;
        A.push_back(C);
        AA.push_back(C);
        for (int i = 0; unsigned(i) < All_Point.size(); i++)
        {
            A[j].push_back(0);
            AA[j].push_back(0);
        }
    }
    for (int i = 0; i < k; i++)
    {
        vector <double> d;
        P_x_c.push_back(d);
        for (int j = 0; unsigned(j) < All_Point.size(); j++)
        {
            P_x_c[i].push_back(0);
        }
    }
    for (int i = 0; i < 2 * k; i++)
    {
        Mu.push_back(0);
    }
    vector <int> N;
    for (int i = 0; i < k; i++)
    {
        N.push_back(0);
    }

    for (int i = 0; unsigned(i) < All_Point.size(); i++)
    {
        Mu[(i % k) * 2] = Mu[(i % k) * 2] + All_Point[i].GetX();
        Mu[(i % k) * 2 + 1] = Mu[(i % k) * 2 + 1] + All_Point[i].GetY();
        N[(i % k)]++;
    }

    for (int i = 0; i < k; i++)
    {
        Mu[(i % k) * 2] = Mu[(i % k) * 2] / N[i];
        Mu[(i % k) * 2 + 1] = Mu[(i % k) * 2 + 1] / N[i];
    }

    for (int j = 0; j < k; j++)
    {
        vector <double> d;
        Sigma.push_back(d);
        Sigma_1.push_back(d);
        Sigma[j].push_back(1);
        Sigma[j].push_back(0);
        Sigma[j].push_back(0);
        Sigma[j].push_back(1);

        for (int i = 0; i < 4; i++)
        {
            Sigma_1[j].push_back(1);
        }
    }


    double Stop = 1;
    char o;
    int Nomer;
    while (Stop == 1)
    {
        //E - шаг
        Stop = 0;
        for (int i = 0; i < k; i++)
        {
            double DetSigma = Sigma[i][0] * Sigma[i][3] - Sigma[i][1] * Sigma[i][2];
            double ABSDetSigma = abs(DetSigma);
            Sigma_1[i][0] = (Sigma[i][3]) / DetSigma;
            Sigma_1[i][1] = (-Sigma[i][1] / DetSigma);
            Sigma_1[i][2] = (-Sigma[i][2] / DetSigma);
            Sigma_1[i][3] = (Sigma[i][0] / DetSigma);
            //     cout<<Sigma[i][0]<<"  "<<Sigma[i][1]<<endl;
            //     cout<<Sigma[i][2]<<"  "<<Sigma[i][3]<<endl;
            //     cout<<Sigma_1[i][0]<<"  "<<Sigma_1[i][1]<<endl;
            //     cout<<Sigma_1[i][2]<<"  "<<Sigma_1[i][3]<<endl;
            for (int j = 0; j < All_Point.size(); j++)
            {
                double e = (All_Point[j].GetX() - Mu[i * 2]);
                double r = (All_Point[j].GetY() - Mu[i * 2 + 1]);
                e = e * (Sigma_1[i][0] * (All_Point[j].GetX() - Mu[i * 2]) + Sigma_1[i][1] * (All_Point[j].GetY() - Mu[i * 2 + 1]));
                r = r * (Sigma_1[i][2] * (All_Point[j].GetX() - Mu[i * 2]) + Sigma_1[i][3] * (All_Point[j].GetY() - Mu[i * 2 + 1]));
                r = (-0.5) * (e + r);
                P_x_c[i][j] = (1 / sqrt(2 * pi * ABSDetSigma));
                //       cout<<"P_x_c["<<i<<"]["<<j<<"]"<<P_x_c[i][j]<<endl;
                //       cout<<"r="<<r<<endl;
                P_x_c[i][j] = P_x_c[i][j] * exp(r);
            }

        }
        for (int i = 0; i < All_Point.size(); i++)
        {
            double Summa = 0;
            for (int j = 0; j < k; j++)
            {
                Summa = Summa + P_x_c[j][i] * W[j];
            }

            for (int p = 0; p < k; p++)
            {
                A[p][i] = P_x_c[p][i] * W[p] / Summa;
            }

        }
        string s       = "C:\\C_A_Result\\EM_";
        string PointP  = "C:\\C_A_Result\\EM_point_";
        string Ellipse = "C:\\C_A_Result\\EM_ellipse_";
        string b = std::to_string(n);
        PointP = PointP + b;
        Ellipse += b;
        s = s + b;
        PointP = PointP + ".plt";
        Ellipse += ".plt";
        s = s + ".txt";
        string fi = s;
        fi.pop_back();
        fi.pop_back();
        fi.pop_back();
        fi = fi + "plt";
        int F;
        for (int i = 0; i < All_Point.size(); i++)
        {
            for (int f = 0; f < k; f++)
            {
                AA[f][i] = 0;
            }
        }

        for (int i = 0; i < All_Point.size(); i++)
        {
            double M = A[0][i];
            F = 0;
            for (int f = 0; f < k; f++)
            {
                if (A[f][i] >= M)
                {
                    M = A[f][i];
                    F = f;
                }
            }
            AA[F][i] = 1;
        }
        vector <Point> Arr;
        for (int f = 0; f < k; f++)
        {
            Point point(Mu[f * 2], Mu[f * 2 + 1]);
            Arr.push_back(point);
        }

        ofstream g, h, point, ellipse;
        point.open(PointP);
        ellipse.open(Ellipse);
        g.open(s);
        h.open(fi);
        h << "set xrange[-20:20] " << endl;
        h << "set yrange[-10:10] " << endl;
        vector <double> x_1, x_2, psi;

        for (int i = 0; i < k; i++)
        {
            x_1.push_back(0.5 * ((Sigma[i][0] + Sigma[i][3]) + sqrt((Sigma[i][0] + Sigma[i][3]) * (Sigma[i][0] + Sigma[i][3]) - 4 * (Sigma[i][0] * Sigma[i][3] - Sigma[i][1] * Sigma[i][2]))));
            x_2.push_back(0.5 * ((Sigma[i][0] + Sigma[i][3]) - sqrt((Sigma[i][0] + Sigma[i][3]) * (Sigma[i][0] + Sigma[i][3]) - 4 * (Sigma[i][0] * Sigma[i][3] - Sigma[i][1] * Sigma[i][2]))));
            if (sqrt(Sigma[i][1] * Sigma[i][1] + (Sigma[i][0] - x_1[i]) * (Sigma[i][0] - x_1[i])) == 0) { psi.push_back(0); }
            else {
                if (Sigma[i][0] - x_1[i] >= 0) { psi.push_back(acos(-Sigma[i][1] / (sqrt(Sigma[i][1] * Sigma[i][1] + (Sigma[i][0] - x_1[i]) * (Sigma[i][0] - x_1[i])))) * 180 / pi); }
                if (Sigma[i][0] - x_1[i] < 0) { psi.push_back(acos(Sigma[i][1] / (sqrt(Sigma[i][1] * Sigma[i][1] + (Sigma[i][0] - x_1[i]) * (Sigma[i][0] - x_1[i])))) * 180 / pi); }
            }

            h << "set object " << i + 1 << " ellipse center " << Mu[i * 2] << ", " << Mu[i * 2 + 1] << " size " << x_1[i] * 2 << ", " << x_2[i] * 2 << " angle " << psi[i] << " front fs empty bo " << i + 1 << endl;
            ellipse << Mu[i * 2] << " " << Mu[i * 2 + 1] << " " << x_1[i] * 2 << " " << x_2[i] * 2 << " " << psi[i] << endl;
            h << "plot '" << s << "' with points" << endl;
        }
        h << "plot 'Point.txt' u 1:2 w p,";
        int ol;
        for (int a = 0; a < k; a++)
        {
            for (int z = 0; z < All_Point.size(); z++)
            {
                if (AA[a][z] == 1)
                {
                    g << All_Point[z].GetX() << " " << All_Point[z].GetY() << endl;
                    point << All_Point[z].GetX() << " " << All_Point[z].GetY() << endl;
                    //g<< Arr[a].GetX()<<" "<< Arr[a].GetY()<<endl;
                    //cout<< All_Point[z].GetX()<<" "<< All_Point[z].GetY()<<endl;
                    //cout<< Arr[a].GetX()<<" "<< Arr[a].GetY()<<endl;
                }
            }
            h << "'" << s << "'index " << a << " w points title '" << a << "' ,\\" << endl;
            g << endl;
            g << endl;
            point << endl;
            point << endl;

            //cout<<endl;
            ol = a;
        }
        ol++;
        for (int m = 0; m < k; m++)
        {
            g << Arr[m].GetX() << " " << Arr[m].GetY() << endl;
            h << "'" << s << "'index " << ol << " w points title '" << ol << "' ,\\" << endl;
            g << endl;
            g << endl;
            g << endl;
            g << endl;
            ol++;
        }


        point.close();
        ellipse.close();
        h.close();
        g.close();

        n++;
        Nomer = n - 1;
        // M-шаг

        vector <double> W_1 = W;
        vector <double> Mu_1 = Mu;
        vector < vector <double> > Sigma_1 = Sigma;
        double Proverka = 0;
        for (int i = 0; i < k; i++)
        {
            W[i] = 0;
            for (int j = 0; j < All_Point.size(); j++)
            {
                W[i] = W[i] + A[i][j];
            }
            W[i] = W[i] / All_Point.size();
            Proverka += W[i];
        }

        for (int i = 0; i < k; i++)
        {
            Mu[i * 2] = Mu[i * 2 + 1] = 0;
            for (int j = 0; j < All_Point.size(); j++)
            {
                Mu[i * 2] = Mu[i * 2] + (A[i][j] / All_Point.size()) / W[i] * All_Point[j].GetX();
                Mu[i * 2 + 1] = Mu[i * 2 + 1] + (A[i][j] / All_Point.size()) / W[i] * All_Point[j].GetY();
            }
            //    cout<<"Mu[("<<i*2<<"]"<<Mu[i*2];
            //    cout<<" Mu[("<<i*2+1<<"]"<<Mu[i*2+1]<<endl;

        }

        for (int c = 0; c < k; c++)
        {
            Sigma[c][0] = Sigma[c][1] = Sigma[c][2] = Sigma[c][3] = 0;
            for (int p = 0; p < All_Point.size(); p++)
            {
                Sigma[c][0] = Sigma[c][0] + (A[c][p] / All_Point.size()) / W[c] * (All_Point[p].GetX() - Mu[c * 2]) * (All_Point[p].GetX() - Mu[c * 2]);
                Sigma[c][1] = Sigma[c][1] + (A[c][p] / All_Point.size()) / W[c] * (All_Point[p].GetX() - Mu[c * 2]) * (All_Point[p].GetY() - Mu[c * 2 + 1]);
                Sigma[c][2] = Sigma[c][2] + (A[c][p] / All_Point.size()) / W[c] * (All_Point[p].GetY() - Mu[c * 2 + 1]) * (All_Point[p].GetX() - Mu[c * 2]);
                Sigma[c][3] = Sigma[c][3] + (A[c][p] / All_Point.size()) / W[c] * (All_Point[p].GetY() - Mu[c * 2 + 1]) * (All_Point[p].GetY() - Mu[c * 2 + 1]);
            }
            //cout<<c<<" Sigma[c][0]="<<Sigma[c][0]<<" Sigma[c][1]="<<Sigma[c][1]<<" Sigma[c][2]="<<Sigma[c][2]<<" Sigma[c][3]="<<Sigma[c][3]<<endl;
        }

        for (int c = 0; c < k; c++)
        {
            if (abs(W_1[c] - W[c]) > E) { Stop = 1; }
            if (abs(Sigma_1[c][0] - Sigma[c][0]) > E) { Stop = 1; }
            if (abs(Sigma_1[c][1] - Sigma[c][1]) > E) { Stop = 1; }
            if (abs(Sigma_1[c][2] - Sigma[c][2]) > E) { Stop = 1; }
            if (abs(Sigma_1[c][3] - Sigma[c][3]) > E) { Stop = 1; }
            if (abs(Mu_1[c * 2] - Mu[c * 2] > E)) { Stop = 1; }
            if (abs(Mu_1[c * 2 + 1] - Mu[c * 2 + 1] > E)) { Stop = 1; }
        }

        //cout<<"Stop="<<Stop<<endl;
        //scanf("%s",&o);
    }


    string Animate = "C:\\C_A_Result\\EM_Animate.plt";
    ofstream Anim;
    Anim.open(Animate);
    Anim << "set xrange[-30:30] " << endl;
    Anim << "set yrange[-25:25] " << endl;
    Anim << "set term gif animate optimize delay 10 background \"#ffeedf\" font \" Times-Roman,10 \" " << endl;
    Anim << "set output \"em_algoritm.gif\" " << endl;
    Anim << "set size square" << endl;
    Anim << "set title \"EM-algoritm\" " << endl;
    Anim << "do for[i=0:" << Nomer << "]{" << endl;
    Anim << "plot ";
    for (int m = 0; m < k; m++)
    {
        Anim << " 'EM_point_'.i.'.plt' index " << m << " w p  ,\\" << endl;
    }
    Anim << " 'EM_ellipse_'.i.'.plt' using 1:2:3:4:5 with ellipses lc rgb \"red\" " << endl;
    Anim << "}" << endl;


    string S = "EM";
    Find_Claster Q;
    Q.SetS(S);
    Q.SetInd(A);

    vector <Point> Arr;
    for (int f = 0; f < k; f++)
    {
        Point point(Mu[f * 2], Mu[f * 2 + 1]);
        Arr.push_back(point);
    }

    for (int f = 0; f < k; f++)
    {
        vector <Point> PrintP;
        vector <Point> Cluster;
        for (int i = 0; i < All_Point.size(); i++)
        {
            if (AA[f][i] == 1)
            {
                PrintP.push_back(All_Point[i]);
                PrintP.push_back(Arr[f]);
                Cluster.push_back(All_Point[i]);
            }
        }
        Q.SetPrint(PrintP);
        Q.SetClaster(Cluster);
    }

    return Q;
}
