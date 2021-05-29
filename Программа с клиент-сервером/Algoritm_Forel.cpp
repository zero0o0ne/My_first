//211-Pushkareva-Anna-2021
#include "Algoritm_Forel.h"

#include <string>
#define E 0.01
#define pi 3.1415926535
double Algoritm_Forel::d(Point& A, Point& B)
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


vector <Find_Claster> Algoritm_Forel::Start(double R, int n, vector <Point>& All_Point)
{

    vector <Find_Claster> QQ;
    vector <Point> M;
    vector <vector <Point>> forel;
    vector <vector < vector <Point> >>  Okrestnost;

    for (int i = 0; i < n; i++)
    {
        vector <Point> Q;
        vector < vector <Point> > QQ;
        forel.push_back(Q);
        Okrestnost.push_back(QQ);
    }

    for (int N = 0; N < n; N++)
    {

        if (N != 0) { M.clear(); }
        if (N == 0)
        {
            for (int i = 0; i < All_Point.size(); i++)
            {
                M.push_back(All_Point[i]);
            }
        }
        // cout<<"Sos"<<endl;
        if (N != 0)
        {
            for (int i = 0; i < forel[N - 1].size(); i++)
            {
                M.push_back(forel[N - 1][i]);
            }
        }
        int o;
        //       cout<<"M.size()= "<<M.size()<<endl;

        while (M.size() > 0)
        {
            //            cout<<"M.size()= "<<M.size()<<endl;
            //            cout<<"M.size()= "<<M.size()<<endl;
            //            cout<<"dlya prodolgeniya nagmite 0"<<endl;
            //            scanf("%d",&o);
            vector <Point>  BBB;
            Okrestnost[N].push_back(BBB);
            forel[N].push_back(M[0]);
            int ind = 1;

            while (ind == 1)
            {
                ind = 0;
                //cout<<"M.size()= "<<M.size()<<endl;
                for (int j = 0; j < M.size(); j++)
                {
                    // cout<<"d()="<<d(forel[N][forel[N].size()-1],M[j])<<endl;
                    if (d(forel[N][forel[N].size() - 1], M[j]) < R * pow(2, N))
                    {
                        Okrestnost[N][forel[N].size() - 1].push_back(M[j]);
                        //M[j].SetA(1);

                        //cout<<"d()="<<d(forel[N][forel[N].size()-1],M[j])<<endl<<endl;
                    }
                }
                //cout<<"M.size()= "<<M.size()<<endl;
                double x, y;
                x = y = 0;
                //cout<<"^)";
                for (int i = 0; i < Okrestnost[N][forel[N].size() - 1].size(); i++)
                {
                    x += Okrestnost[N][forel[N].size() - 1][i].GetX() / Okrestnost[N][forel[N].size() - 1].size();
                    y += Okrestnost[N][forel[N].size() - 1][i].GetY() / Okrestnost[N][forel[N].size() - 1].size();
                }
                Point Centr(x, y);
                //  cout<<Centr.GetX() - forel[N][forel[N].size()-1].GetX()<<" || "<<Centr.GetY()- forel[N][forel[N].size()-1].GetY()<<" "<<E<<endl;
                if (fabs(Centr.GetX() - forel[N][forel[N].size() - 1].GetX()) > E || fabs(Centr.GetY() - forel[N][forel[N].size() - 1].GetY()) > E)
                {
                    forel[N][forel[N].size() - 1] = Centr;
                    ind = 1;
                    Okrestnost[N][forel[N].size() - 1].clear();
                }
                //cout<<"ind="<<ind<<endl;

            }

            vector <Point> S;
            for (int i = 0; i < M.size(); i++)
            {
                int k = 0;
                for (int j = 0; j < Okrestnost[N][forel[N].size() - 1].size(); j++)
                {
                    if (M[i].GetX() == Okrestnost[N][forel[N].size() - 1][j].GetX() && M[i].GetY() == Okrestnost[N][forel[N].size() - 1][j].GetY()) { k = 1; }
                }

                if (k != 1) { S.push_back(M[i]); }
            }

            M.clear();
            for (int i = 0; i < S.size(); i++)
            {
                M.push_back(S[i]);
            }

            ofstream out, com, cir, ele;
            /*string Cir = "C:\\My_Program\\INT\\Algoritms\\Forel_circle_";
            string Ele = "C:\\My_Program\\INT\\Algoritms\\Forel_elements_";
            string file = "C:\\My_Program\\INT\\Algoritms\\Forel_";
            string file_GP = "C:\\My_Program\\INT\\Algoritms\\GP_Forel_";*/
            string Cir = "C:\\C_A_Result\\Forel_circle_";
            string Ele = "C:\\C_A_Result\\Forel_elements_";
            string file = "C:\\C_A_Result\\Forel_";
            string file_GP = "C:\\C_A_Result\\GP_Forel_";
            string b;
            b = std::to_string(N);
            Ele += b + "_";
            Cir += b + "_";
            file += b + "_";
            file_GP += b + "_";
            b = to_string(forel[N].size() - 1);
            Ele += b + ".txt";
            Cir += b + ".txt";
            file += b + ".txt";
            file_GP += b + ".plt";
            ele.open(Ele);
            cir.open(Cir);
            out.open(file);
            com.open(file_GP);

            com << "set xrange[-20:20] " << endl;
            com << "set yrange[-9:9] " << endl;


            for (int k = 0; k < forel[N].size(); k++)
            {
                com << "set object " << k + 1 << " circle center " << forel[N][k].GetX() << "," << forel[N][k].GetY() << " size " << R * pow(2, N) << endl;
                cir << forel[N][k].GetX() << " " << forel[N][k].GetY() << " " << R * pow(2, N) << endl;
                ele << forel[N][k].GetX() << " " << forel[N][k].GetY() << endl;
            }
            com << "plot ";
            for (int i = 0; i < M.size(); i++)
            {
                out << M[i].GetX() << " " << M[i].GetY() << endl;
            }
            com << "'" << file << "' index 0 w points title '0' ,\\" << endl;
            out << endl << endl;
            for (int k = 0; k < forel[N].size(); k++)
            {
                for (int i = 0; i < Okrestnost[N][k].size(); i++)
                {
                    out << Okrestnost[N][k][i].GetX() << " " << Okrestnost[N][k][i].GetY() << endl;
                }
                com << "'" << file << "' index " << k + 1 << " w points title '" << k + 1 << "' ,\\" << endl;
                out << endl << endl;
            }
            for (int k = 0; k < forel[N].size(); k++)
            {
                out << forel[N][k].GetX() << " " << forel[N][k].GetY() << endl;
            }
            com << "'" << file << "' index " << forel[N].size() + 1 << " w points title '" << forel[N].size() + 1 << "' ,\\" << endl;
            out.close();
            cir.close();
            ele.close();
            com.close();

            //         cout<<"dlya prodolgeniya nagmite 0"<<endl;
            //         scanf("%d",&o);
            //         cout<<"M.size()="<<M.size()<<endl;
        }

        vector <int> B;
        vector <int> Ind;
        vector <int> Group;
        for (int i = 0; i < forel[N].size(); i++)
        {
            Ind.push_back(0);
            Group.push_back(0);
        }
        for (int i = 0; i < forel[N].size() * forel[N].size(); i++)
        {
            B.push_back(0);
        }
        for (int i = 0; i < forel[N].size(); i++)
        {
            for (int j = i; j < forel[N].size(); j++)
            {
                //cout<<"d(forel[N]["<<i<<"],forel[N]["<<j<<"])="<<d(forel[N][i],forel[N][j])<<" R*pow(2,N+1)="<<R*pow(2,N+1)<<endl;
                if (d(forel[N][i], forel[N][j]) < R * pow(2, N + 1) && d(forel[N][i], forel[N][j]) != 0)
                {
                    B[i * forel[N].size() + j] = B[j * forel[N].size() + i] = 1;
                    // cout<<B[i*forel[N].size()+j]<<" ";
                }
                //else{cout<<B[i*forel[N].size()+j]<<" ";}
            }
            //             cout<<endl;
            //             for(int fff=0; fff<i+1; fff++)
            //             {
            //                 cout<<"  ";
            //             }
        }
        cout << endl;
        for (int h = 0; h < forel[N].size(); h++)
        {
            if (Group[h] == 0)
            {
                Group[h] = h + 1;
                Ind[h] = 1;
                //cout<<"Ind["<<h<<"]="<<Ind[h]<<endl;
                int s = 1;
                int k = 0;

                while (s == 1)
                {
                    s = 0;
                    for (int i = 0; i < forel[N].size(); i++)
                    {
                        //cout<<"Ind["<<i<<"]="<<Ind[i]<<" k+1="<<k+1<<" && Group["<<i<<"]="<<Group[i]<<"h="<<h<<endl;
                        if (Ind[i] == k + 1 && Group[i] == h + 1)
                        {
                            for (int j = 0; j < forel[N].size(); j++)
                            {
                                //cout<<"B["<<i*forel[N].size()+j<<"]="<<B[i*forel[N].size()+j]<<" && Ind["<<j<<"]="<<Ind[j]<<endl;
                                if (B[i * forel[N].size() + j] == 1 && Ind[j] == 0)
                                {
                                    // cout<<"Group["<<i<<"]="<<Group[i]<<endl;
                                     //cout<<"Group["<<j<<"]="<<Group[j]<<endl;
                                    Ind[j] = Ind[i] + 1;
                                    s = 1;
                                    Group[j] = Group[i];
                                    //cout<<"Group["<<j<<"]="<<Group[j]<<endl;
                                }
                            }
                        }

                    }

                    k++;
                }
            }
        }



        ofstream out, com, cir;
        /*string Cir = "C:\\My_Program\\INT\\Algoritms\\Forel_circle_";
        string file = "C:\\My_Program\\INT\\Algoritms\\Forel_";
        string file_GP = "C:\\My_Program\\INT\\Algoritms\\GP_Forel_";*/

        string file = "C:\\C_A_Result\\Forel_";
        string file_GP = "C:\\C_A_Result\\GP_Forel_";
        string Cir = "C:\\C_A_Result\\Forel_circle_";
        string b;
        b = to_string(N);
        Cir += b + "_";
        file += b + "_";
        file_GP += b + "_";
        b = to_string(forel[N].size());
        Cir += b + ".txt";
        file += b + ".txt";
        file_GP += b + ".plt";
        cir.open(Cir);
        out.open(file);
        com.open(file_GP);

        com << "set xrange[-20:20] " << endl;
        com << "set yrange[-10:10] " << endl;
        com << "set nokey" << endl;



        for (int k = 0; k < forel[N].size(); k++)
        {
            com << "set object " << k + 1 << " circle center " << forel[N][k].GetX() << "," << forel[N][k].GetY() << " size " << R * pow(2, N) << endl;
            cir << forel[N][k].GetX() << " " << forel[N][k].GetY() << " " << R * pow(2, N) << endl;
        }

        com << "plot ";
        for (int f = 1; f <= forel[N].size(); f++)
        {
            for (int i = 0; i < forel[N].size(); i++)
            {
                if (Group[i] == f)
                {
                    for (int k = 0; k < Okrestnost[N][i].size(); k++)
                    {
                        out << Okrestnost[N][i][k].GetX() << " " << Okrestnost[N][i][k].GetY() << endl;
                    }

                }
            }

            out << endl << endl;
        }

        for (int k = 0; k < Group.size(); k++)
        {
            //cout<<"Group["<<k<<"]="<<Group[k]<<endl;
            com << "'" << file << "' index " << k << " w points title '" << k << "' ,\\" << endl;
        }



        out.close();

        com.close();



        /*string Animate = "C:\\My_Program\\INT\\Algoritms\\Forel_Animate_";*/
        string Animate = "C:\\Users\\C_A_Result\\Forel_Animate_";
        Animate += to_string(N) + ".plt";
        ofstream Anim;
        Anim.open(Animate);
        Anim << "set xrange[-15:20] " << endl;
        Anim << "set yrange[-15:20] " << endl;
        Anim << "set term gif animate optimize delay 40 background \"#ffeedf\" font \" Times-Roman,10 \" " << endl;
        Anim << "set output \"Forel_Animate_" << N << ".gif\" " << endl;
        Anim << "set size square" << endl;
        Anim << "set nokey" << endl;
        Anim << "set title \"Forel-algoritm\" " << endl;
        Anim << "do for[i=0:" << forel[N].size() << "]{" << endl;
        Anim << "plot ";
        for (int m = 0; m < forel[N].size() + 1; m++)
        {
            Anim << " 'Forel_" << N << "_'.i.'.txt' index " << m << " with points  ,\\" << endl;
        }
        Anim << "'Forel_circle_" << N << "_'.i.'.txt' using 1:2:3 with circle lc rgb \"red\" " << endl;
        // Anim<<"'Forel_elements_"<<N<<"_'.i.'.txt' using 1:2 with points  "<<endl;
        Anim << "}" << endl;

        string S = "Forel";
        Find_Claster Q;

        Q.SetS(S);

        for (int f = 1; f <= forel[N].size(); f++)
        {
            vector <Point> Cluster;

            for (int i = 0; i < forel[N].size(); i++)
            {
                if (Group[i] == f)
                {
                    for (int k = 0; k < Okrestnost[N][i].size(); k++)
                    {
                        Cluster.push_back(Okrestnost[N][i][k]);
                    }

                }
            }
            Q.SetClaster(Cluster);
        }

        QQ.push_back(Q);
        // cout<<"kak dela"<<endl;
    }
    return QQ;
}

