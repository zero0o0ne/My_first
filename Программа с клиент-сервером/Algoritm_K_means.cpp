//211-Pushkareva-Anna-2021
#include "Algoritm_K_means.h"

Find_Claster Algoritm_K_means::Start(int k, vector <Point>& All_Point)
{
    vector <Point> Arr;
    vector <vector <double>> A;
    int i, j, p, I, f, F, o = 0;

    double m = 0;
    double c;

    for (int i = 0; i < k; i++)
    {
        Point P;
        vector <double> AA;
        Arr.push_back(P);
        A.push_back(AA);
    }
    Arr[0] = All_Point[0];


    for (p = 1; p < k; p++)
    {
        m = 0;
        for (i = 0; i < (All_Point.size()); i++)
        {
            o = 0;
            for (int s = 0; s < p; s++)
            {
                if (Arr[s].GetID() == All_Point[i].GetID()) { o = -1; }
            }
            if (o != -1)
            {
                c = 0;
                for (int j = 0; j < p; j++)
                {
                    c = c + d(Arr[j], All_Point[i]);

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
        Arr[p] = All_Point[I];
        //cout<<Arr[p].GetX()<<" "<<Arr[p].GetY()<<endl;
    }
    //cout<<Arr[0].GetX()<<" "<<Arr[0].GetY()<<endl;
//cout<<endl;

    for (i = 0; i < All_Point.size(); i++)
    {
        double h = d(Arr[0], All_Point[i]);
        F = 0;
        for (f = 0; f < k; f++)
        {
            //cout<<"d(Arr["<<f<<"],All_Point["<<i<<"])="<<d(Arr[f],All_Point[i])<<"  ";
            if (h > d(Arr[f], All_Point[i]))
            {
                h = d(Arr[f], All_Point[i]);
                F = f;
            }
        }
        //cout<<"h="<<h<<" "<<"F="<<F<<endl;
        for (f = 0; f < k; f++)
        {
            if (f == F) { A[f].push_back(1); }
            if (f != F) { A[f].push_back(0); }
        }
    }

    ofstream g, h;
    //g.open("C:\\My_Program\\INT\\Algoritms\\K_means_0.txt");
    //h.open("C:\\My_Program\\INT\\Algoritms\\K_means_GP.plt");
    g.open("C:\\C_A_Result\\K_means_0.txt");
    h.open("C:\\C_A_Result\\K_means_GP.plt");
    /*g.open("dir//Algoritms//K_means_0.txt");
    h.open("Algoritms\\K_means_GP.plt");*/
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
                g << Arr[a].GetX() << " " << Arr[a].GetY() << endl;
                //cout<< All_Point[z].GetX()<<" "<< All_Point[z].GetY()<<endl;
            }
        }
        h << "'K_means_0.txt' index " << a << " w linespoints title '" << a << "' ,\\" << endl;
        g << endl;
        g << endl;
        g << endl;
        g << endl;
        //cout<<endl;

    }
    h.close();
    g.close();



    c = 1;
    int iteraciya = 0;
    while (c == 1)
    {


        c = 0;
        for (int f = 0; f < k; f++)
        {
            double x = 0, y = 0;
            int a = 0;
            for (i = 0; i < All_Point.size(); i++)
            {
                x = x + (All_Point[i].GetX() * A[f][i]);
                // cout<<"x="<<x<<"+(All_Point["<<i<<"].GetX()*A["<<f<<"]["<<i<<"])="<<x<<endl;
                y = y + (All_Point[i].GetY() * A[f][i]);
                a = a + A[f][i];
            }
            //cout<<"a="<<a<<endl;
            Arr[f].SetX(x / a);
            Arr[f].SetY(y / a);
        }
        ofstream g, h;
        /*string Str = "C:\\My_Program\\INT\\Algoritms\\K_means_";*/
        string Str = "C:\\C_A_Result\\K_means_";
        string B;
        B = std::to_string(2 * iteraciya);
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
                    g << Arr[a].GetX() << " " << Arr[a].GetY() << endl;
                    //g<< Arr[a*u].GetX()<<" "<< All_Point[z].GetY()<<endl;
                    //cout<< All_Point[z].GetX()<<" "<< All_Point[z].GetY()<<endl;
                    //cout<< Arr[a].GetX()<<" "<< Arr[a].GetY()<<endl;
                }
            }
            g << endl;
            g << endl;

            h << "'K_means_" << 2 * iteraciya << ".txt' index " << a << " w linespoints title '" << a << "' ,\\" << endl;


            g << endl;
            g << endl;
            //cout<<endl;

        }
        h.close();
        g.close();


        for (i = 0; i < All_Point.size(); i++)
        {
            double p = d(Arr[0], All_Point[i]);
            F = 0;
            for (int f = 0; f < k; f++)
            {
                if (p > d(Arr[f], All_Point[i]))
                {
                    p = d(Arr[f], All_Point[i]);
                    F = f;
                    //cout<<"p="<<p<<endl;
                }
            }
            //þcout<<"F="<<F<<endl;
            for (int f = 0; f < k; f++)
            {
                double a_0 = A[f][i];
                if (f == F) { A[f][i] = 1; }
                if (f != F) { A[f][i] = 0; }
                if (a_0 != A[f][i]) { c = 1; }
            }
        }


         Str = "C:\\C_A_Result\\K_means_";
        //Str = "C:\\My_Program\\INT\\Algoritms\\K_means_";
        B;
        B = std::to_string(2 * iteraciya + 1);
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
                    g << Arr[a].GetX() << " " << Arr[a].GetY() << endl;
                    //cout<< All_Point[z].GetX()<<" "<< All_Point[z].GetY()<<endl;
                    //cout<< Arr[a].GetX()<<" "<< Arr[a].GetY()<<endl;
                }
            }
            g << endl;
            g << endl;

            h << "'K_means_" << 2 * iteraciya + 1 << ".txt' index " << a << " w linespoints title '" << a << "' ,\\" << endl;


            //cout<<endl;

        }
        h.close();
        g.close();
        iteraciya++;

    }

    string Animate = "C:\\C_A_Result\\K_means_Animate.plt";
    //string Animate = "C:\\My_Program\\INT\\Algoritms\\K_means_Animate.plt";
    ofstream Anim;
    Anim.open(Animate);
    Anim << "set xrange[-15:20] " << endl;
    Anim << "set yrange[-15:20] " << endl;
    Anim << "set term gif animate optimize delay 100 background \"#ffeedf\" font \" Times-Roman,10 \" " << endl;
    Anim << "set output \"K_means_algoritm.gif\" " << endl;
    Anim << "set size square" << endl;
    Anim << "set title \"K-means-algoritm\" " << endl;
    Anim << "do for[i=0:" << 2 * iteraciya - 1 << "]{" << endl;
    Anim << "plot ";
    for (int m = 0; m < k; m++)
    {
        Anim << " 'K_means_'.i.'.txt' index " << m << " w lp  ,\\" << endl;
    }
    Anim << "}" << endl;

    string S = "K_means";
    Find_Claster Q;

    Q.SetS(S);

    for (f = 0; f < k; f++)
    {
        vector <Point> PrintP;
        vector <Point> Cluster;
        for (i = 0; i < All_Point.size(); i++)
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

double Algoritm_K_means::d(Point& A, Point& B)
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
