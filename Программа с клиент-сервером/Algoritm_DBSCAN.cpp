//211-Pushkareva-Anna-2021
#include "Algoritm_DBSCAN.h"

Find_Claster Algoritm_DBSCAN::Start(int k, int N, vector <Binary_Matrix>& B, vector <Point>& All_Point)
{
    int i, j, p, n;
    n = All_Point.size();
    vector <double> Tip;
    for (i = 0; i < n; i++) { Tip.push_back(-1); }


    ofstream g, h;

    g.open("DB.txt");
    h.open("DB_GP.plt");
    h << "set xrange[-20:20] " << endl;
    h << "set yrange[-10:10] " << endl;
    h << "plot 'Point.txt' u 1:2 w p, 'DB.txt' u 1:2 w linespoints ";
    for (i = 0; i < n; i++)
    {
        p = 0;
        for (j = 0; j < n; j++)
        {
            if (B[N - 1].Get(i, j) == 1)
            {
                p++;
            }
        }
        if (p >= k)
        {
            for (j = 0; j < n; j++)
            {
                if (B[N - 1].Get(i, j) == 1)
                {
                    g << All_Point[i].GetX() << " " << All_Point[i].GetY() << endl;
                    g << All_Point[j].GetX() << " " << All_Point[j].GetY() << endl;
                    g << endl;
                    g << endl;
                }
            }
            Tip[i] = 0;
            //0cout <<"All_Point["<<i<<"].SetTip(0)"<<endl;
        }
    }
    h.close();
    g.close();

    //cout<<"Vvedite o"<<endl;
    //scanf("%d",&bljblj);
      //cout << "for(i=0;i<N;i++)"<< endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if ((B[N - 1].Get(i, j) == 1) && (Tip[j] == 0) && (Tip[i] != 0))
            {
                Tip[i] = 1;
            }
        }
    }
    Find_Claster Q;
    Q.SetK(k);
    string S = "DBSCAN";
    int u = B.size() - 1;

    Q.SetS(S);
    double R = B[N - 1].GetR();
    Q.SetAlfa(R);
    vector <double> A;
    for (i = 0; i < n; i++)
    {
        A.push_back(0);
    }
    i = 0;
    while (i < All_Point.size())
    {
        if (Tip[i] == -1)
        {
            Q.SetPyl(All_Point[i]);
            //cout<<")) All_Point["<<i<<"].GetTip()="<<All_Point[i].GetTip()<<"\n";
        }
        if (Tip[i] == 1)
        {
            // cout << i <<endl;
            Q.SetPeref(All_Point[i]);
        }
        if (Tip[i] == 0)
        {
            Q.SetBas(All_Point[i]);
        }
        i++;
    }


    i = 0;
    while (i < All_Point.size())
    {
        if (A[i] == 0)
        {
            vector<Point> Claster;
            if (Tip[i] != -1)
            {
                //cout<<"All_Point["<<i<<"].GetTip()="<<All_Point[i].GetTip()<<endl;
                A[i] = 1;
                Claster.push_back(All_Point[i]);
                // cout <<"a="<<All_Point[i].GetA()<<endl;
                p = Graf_Volna_Chain_DB(i, N, 1, Claster, B, All_Point, Q, A, Tip);
                //cout<<"p="<<p<<"\n";
                if (p == 0) {
                    //cout<<"p="<<p<<endl;
                    vector<Point> PrintP;
                    PrintP.push_back(All_Point[i]);
                    /*cout<<"All_Point["<<i<<"].GetTip()="<<All_Point[i].GetTip()<<"="<<PrintP[PrintP.size()-1].GetTip()<<"\n";
                    cout<<"All_Point["<<i<<"].GetX()="<<All_Point[i].GetX()<<"="<<PrintP[PrintP.size()-1].GetX()<<"\n";
                    cout<<":("<<endl;*/
                    Q.SetPrint(PrintP);
                    PrintP.clear();
                }
                // FC.push_back(Q);
                Q.SetClaster(Claster);
            }

            Claster.clear();
        }
        i++;

    }
    return Q;
}


int Algoritm_DBSCAN::Graf_Volna_Chain_DB(int N, int u, int t, vector<Point>& Claster, vector <Binary_Matrix>& B, vector <Point>& All_Point, Find_Claster& Q, vector <double>& A, vector <double>& Tip)
{
    int p, k = 1;
    int n = All_Point.size();
    vector<Point> PP;
    PP.push_back(All_Point[N]);
    //cout<<"(All_Point["<<N<<"].GetTip()="<<All_Point[N].GetTip()<<"\n";
    for (int j = 0; j < n; j++)
    {
        p = 0;
        //cout<<"(All_Point["<<j<<"].GetTip()="<<All_Point[j].GetTip()<<"B["<<u-1<<"].Get("<<N<<","<<j<<")="<<B[u-1].Get(N,j)<<"All_Point["<<j<<"].GetA()"<<All_Point[j].GetA()<<"\n";
        if ((B[u - 1].Get(N, j) == 1) && (A[j] == 0) && ((Tip[j] == 1 || Tip[j] == 0)))
        {
            //cout<<"(All_Point["<<j<<"].GetTip()="<<All_Point[j].GetTip()<<"\n";
            p++;
            A[j] = (t + 1);
            Claster.push_back(All_Point[j]);
            PP.push_back(All_Point[j]);
            //PP[PP.size()-1].SetTip(Tip[j]);
            //cout<<"(All_Point["<<j<<"].GetTip()="<<All_Point[j].GetTip()<<"="<<PrintP[PrintP.size()-1].GetTip()<<"\n";
            //scanf("%s",&kyfl);
            k = Graf_Volna_Chain_DB(j, u, t + 1, Claster, B, All_Point, Q, A, Tip);
            //cout<<";)"<<endl;
            Q.SetPrint(PP);
            //cout<<"FC[FC.size()-1].GetPrintSize()="<<FC[FC.size()-1].GetPrintSize()<<"\n";;
            PP.clear();
            PP.push_back(All_Point[N]);
            if (N > k)k = N;
        }

    }
    return p;
}
