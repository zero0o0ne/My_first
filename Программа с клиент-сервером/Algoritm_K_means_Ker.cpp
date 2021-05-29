//211-Pushkareva-Anna-2021
#include "Algoritm_K_means_Ker.h"

#include <string>
double Algoritm_K_means_Ker::d(Point& A, Point& B)
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

Find_Claster Algoritm_K_means_Ker::Start(int k, int u, vector <Point>& All_Point)
{
    vector <Point> Arr;
    //vector <double> A[k];
    vector<vector <double>> A;
    vector < vector <Point> > All_Point_1;
    int o = 0;

    double m;
    double c;
    for (int i = 0; i < k * u; i++)
    {
        Point AA;
        Arr.push_back(AA);
    }
    for (int i = 0; i < k; i++)
    {
        vector <double> aa;
        A.push_back(aa);
    }
    Arr[0 * u + 0] = All_Point[0];


    for (int p = 1; p < k; p++)
    {
        int I;
        m = 0;
        for (int i = 0; i < (All_Point.size()); i++)
        {
            o = 0;
            for (int s = 0; s < p; s++)
            {
                if (Arr[s * u + 0].GetID() == All_Point[i].GetID()) { o = -1; }
            }

            if (o != -1)
            {
                c = 0;
                for (int j = 0; j < p; j++)
                {
                    c = c + d(Arr[j * u + 0], All_Point[i]);

                }

                if (m < c)
                {
                    // cout << "m="<<m<<"\n";
                    I = i;
                    m = c;
                }
            }
            //cout << "\n";
            //cout<<"d(Arr["<<p<<"],All_Point["<<i<<"])"<<d(Arr[p],All_Point[i])<<endl;
        }
        Arr[p * u + 0] = All_Point[I];
        // cout<<Arr[p*u+0].GetID()<<" "<<All_Point[I].GetID()<<" "<<o<<endl;
    }



    for (int i = 0; i < All_Point.size(); i++)
    {
        double h = d(Arr[0 * u + 0], All_Point[i]);
        int F = 0;
        for (int f = 0; f < k; f++)
        {
            //cout<<"d(Arr["<<f*u+0<<"],All_Point["<<i<<"])="<<d(Arr[f*u+0],All_Point[i])<<" F="<<F<<endl;
            if (h > d(Arr[f * u + 0], All_Point[i]))
            {
                h = d(Arr[f * u + 0], All_Point[i]);
                F = f;
            }
        }

        for (int f = 0; f < k; f++)
        {
            if (f == F) { A[f].push_back(1); }
            if (f != F) { A[f].push_back(0); }
        }
    }

    ofstream g, h;
    g.open("C:\\C_A_Result\\K_means_Ker.txt");
    //g.open("C:\\My_Program\\INT\\Algoritms\\K_means_Ker.txt");
    h.open("C:\\C_A_Result\\\\K_means_Ker_GP.plt");
    h << "set xrange[-20:20] " << endl;
    h << "set yrange[-10:10] " << endl;
    h << "plot 'Point.txt' u 1:2 w p,";
    for (int a = 0; a < k; a++)
    {
        for (int z = 0; z < All_Point.size(); z++)
        {
            if (A[a][z] == 1)
            {
                g << All_Point[z].GetX() << " " << All_Point[z].GetY() << endl;
                //g<< Arr[a*u+0].GetX()<<" "<< Arr[a*u+0].GetY()<<endl;
                //cout<< All_Point[z].GetX()<<" "<< All_Point[z].GetY()<<endl;
                //cout<< Arr[a].GetX()<<" "<< Arr[a].GetY()<<endl;
            }
        }
        h << "'K_means_Ker.txt' index " << a << " w points title '" << a << "' ,\\" << endl;
        g << endl;
        g << endl;
        g << endl;
        g << endl;
        //cout<<endl;

    }
    h.close();
    g.close();

    for (int i = 0; i < k; i++)
    {
        vector <Point> ASH;
        All_Point_1.push_back(ASH);
    }

    c = 1;
    int iteraciya = 0;

    while (c == 1)
    {
        iteraciya++;
        c = 0;
        //Шаг 1
        for (int j = 0; j < k; j++)
        {
            All_Point_1[j].clear();
        }
        for (int i = 0; i < All_Point.size(); i++)
        {

            for (int j = 0; j < k; j++)
            {
                if (A[j][i] == 1) { All_Point_1[j].push_back(All_Point[i]); }
            }
        }

        for (int n = 0; n < k; n++)
        {
            vector <Point> Arr_1;
            vector <vector <double>> A_1;
            for (int i = 0; i < u; i++)
            {
                Point AA;
                vector <double> BB;
                Arr_1.push_back(AA);
                A_1.push_back(BB);
            }

            int i, j, p, I, f, F, o = 0;

            double m = 0;
            double c_1;

            Arr_1[0] = All_Point_1[n][0];

            for (p = 1; p < u; p++)
            {
                m = 0;
                for (i = 0; i < (All_Point_1[n].size()); i++)
                {
                    o = 0;
                    for (int s = 0; s < p; s++)
                    {
                        if (Arr_1[s].GetID() == All_Point_1[n][i].GetID()) { o = -1; }
                    }
                    if (o != -1)
                    {
                        c_1 = 0;
                        for (int j = 0; j < p; j++)
                        {
                            c_1 = c_1 + d(Arr_1[j], All_Point_1[n][i]);

                        }

                        if (m < c_1)
                        {
                            // cout << "m="<<m<<"\n";
                            I = i;
                            m = c_1;
                        }
                    }
                    //cout << "\n";
                    //cout<<"d(Arr["<<p<<"],All_Point["<<i<<"])"<<d(Arr[p],All_Point[i])<<endl;
                }
                Arr_1[p] = All_Point_1[n][I];
                //cout<<Arr[p].GetX()<<" "<<Arr[p].GetY()<<endl;
            }


            for (i = 0; i < All_Point_1[n].size(); i++)
            {
                double h = d(Arr_1[0], All_Point_1[n][i]);
                F = 0;
                for (f = 0; f < u; f++)
                {
                    //cout<<"d(Arr["<<f<<"],All_Point["<<i<<"])="<<d(Arr[f],All_Point[i])<<"  ";
                    if (h > d(Arr_1[f], All_Point_1[n][i]))
                    {
                        h = d(Arr_1[f], All_Point_1[n][i]);
                        F = f;
                    }
                }
                //cout<<"h="<<h<<" "<<"F="<<F<<endl;
                for (f = 0; f < u; f++)
                {
                    if (f == F) { A_1[f].push_back(1); }
                    if (f != F) { A_1[f].push_back(0); }
                }
            }

            c_1 = 1;

            while (c_1 == 1)
            {
                c_1 = 0;

                for (int f = 0; f < u; f++)
                {
                    double x = 0, y = 0;
                    int a = 0;
                    for (i = 0; i < All_Point_1[n].size(); i++)
                    {
                        x = x + (All_Point_1[n][i].GetX() * A_1[f][i]);
                        y = y + (All_Point_1[n][i].GetY() * A_1[f][i]);
                        a = a + A_1[f][i];

                    }
                    char prov;

                    Arr_1[f].SetX(x / a);
                    Arr_1[f].SetY(y / a);
                }
                //cout<<"n="<<n<<endl;
                for (i = 0; i < All_Point_1[n].size(); i++)
                {

                    double p = d(Arr_1[0], All_Point_1[n][i]);
                    F = 0;
                    for (int f = 0; f < u; f++)
                    {
                        if (p > d(Arr_1[f], All_Point_1[n][i]))
                        {
                            p = d(Arr_1[f], All_Point_1[n][i]);
                            F = f;
                            //cout<<"p="<<p<<endl;
                        }
                    }
                    //þcout<<"F="<<F<<endl;
                    for (int f = 0; f < u; f++)
                    {
                        double a_0 = A_1[f][i];
                        if (f == F) { A_1[f][i] = 1; }
                        if (f != F) { A_1[f][i] = 0; }
                        if (a_0 != A_1[f][i]) { c_1 = 1; }

                    }
                }

            }

            for (int j = 0; j < u; j++)
            {
                Arr[n * u + j] = Arr_1[j];
            }

        }


        ofstream g, h;
        string Str = "C:\\C_A_Result\\K_means_Ker_";
        string B;
        B = std::to_string(iteraciya);
        Str += B;
        B = Str;
        B += ".plt";
        Str += ".txt";

        g.open(Str);
        h.open(B);
        h << "set xrange[-20:20] " << endl;
        h << "set yrange[-10:10] " << endl;
        h << "plot ";
        for (int a = 0; a < k; a++)
        {
            for (int z = 0; z < All_Point.size(); z++)
            {
                if (A[a][z] == 1)
                {
                    g << All_Point[z].GetX() << " " << All_Point[z].GetY() << endl;
                    //g<< Arr[a*u].GetX()<<" "<< All_Point[z].GetY()<<endl;
                    //cout<< All_Point[z].GetX()<<" "<< All_Point[z].GetY()<<endl;
                    //cout<< Arr[a].GetX()<<" "<< Arr[a].GetY()<<endl;
                }
            }
            g << endl;
            g << endl;
            for (int z = 0; z < u; z++)
            {
                g << Arr[a * u + z].GetX() << " " << Arr[a * u + z].GetY() << endl;
            }

            h << "'K_means_Ker_" << iteraciya << ".txt' index " << 2 * a << " w points title '" << 2 * a << "' ,\\" << endl;
            h << "'K_means_Ker_" << iteraciya << ".txt' index " << 2 * a + 1 << " w points title '" << 2 * a + 1 << "' ,\\" << endl;

            g << endl;
            g << endl;
            //cout<<endl;

        }
        h.close();
        g.close();



        //Шаг 2
        for (int i = 0; i < All_Point.size(); i++)
        {
            double p = d(Arr[0 * u + 0], All_Point[i]);
            int F = 0;
            for (int j = 0; j < u; j++)
            {
                for (int f = 0; f < k; f++)
                {
                    if (p > d(Arr[f * u + j], All_Point[i]))
                    {
                        p = d(Arr[f * u + j], All_Point[i]);
                        F = f;

                    }
                }
            }

            //cout<<"F="<<F<<endl;
            for (int f = 0; f < k; f++)
            {
                double a_0 = A[f][i];
                if (f == F) { A[f][i] = 1; }
                if (f != F) { A[f][i] = 0; }
                if (a_0 != A[f][i]) { c = 1; }

            }

        }
    }


    string Animate = "C:\\C_A_Result\\K_means_Ker_Animate.plt";
    ofstream Anim;
    Anim.open(Animate);
    Anim << "set xrange[-15:20] " << endl;
    Anim << "set yrange[-15:20] " << endl;
    Anim << "set term gif animate optimize delay 100 background \"#ffeedf\" font \" Times-Roman,10 \" " << endl;
    Anim << "set output \"K_means_Ker_algoritm.gif\" " << endl;
    Anim << "set size square" << endl;
    Anim << "set title \"K_means_Ker-algoritm\" " << endl;
    Anim << "do for[i=1:" << iteraciya << "]{" << endl;
    Anim << "plot ";
    for (int m = 0; m < k; m++)
    {
        Anim << " 'K_means_Ker_'.i.'.txt' index " << 2 * m << " w p  ,\\" << endl;
        Anim << " 'K_means_Ker_'.i.'.txt' index " << 2 * m + 1 << " w p lc rgb \"red\" ,\\" << endl;
    }
    Anim << "}" << endl;

    string S = "K_means_Ker";
    Find_Claster Q;
    Q.SetS(S);

    for (int f = 0; f < k; f++)
    {
        vector <Point> PrintP;
        vector <Point> Cluster;
        for (int i = 0; i < All_Point.size(); i++)
        {
            if (A[f][i] == 1)
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

