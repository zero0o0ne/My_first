//211-Pushkareva-Anna-2021
#include "Algoritm_Wave.h"

Find_Claster Algoritm_Wave::Start(int N, vector <Binary_Matrix> B, vector <Point> All_Point)
{
    int i, j, k, p;
    string S = "Klassik Wave";
    Find_Claster Q;
    double R = B[N - 1].GetR();
    Q.SetAlfa(R);
    Q.SetS(S);
    vector <int> A;
    for (i = 0; i < All_Point.size(); i++)
    {
        A.push_back(0);
    }

    cout << B[0].Get(0, 0) << endl;
    //cout<<"B[0].GetSize()="<<B[0].GetSize()<<endl;
    cout << "N=" << N << endl;
    cout << "All_Point.size()=" << All_Point.size() << endl;
    i = 0;
    while (i < All_Point.size())
    {  //cout <<"i="<<i<<endl;
        if (A[i] == 0)
        {
            // cout<<"i="<<i<<"\n";
            vector<Point> Claster;
            A[i] = 1;
            Claster.push_back(All_Point[i]);
            p = Graf_Volna_Chain(i, N, 1, Claster, B, All_Point, Q, A);
            if (p == 0)
            {
                vector<Point> PrintP;
                PrintP.push_back(All_Point[i]);
                Q.SetPrint(PrintP);
                PrintP.clear();
            }

            Q.SetClaster(Claster);
            Claster.clear();
            //cout <<"FC.SetClaster(Claster);"<<endl;
        }
        i++;
        //cout<<"i="<<i<<endl;
    }
    //cout<<"Finish"<<endl;
    return Q;
}

int Algoritm_Wave::Graf_Volna_Chain(int N, int u, int t, vector<Point>& Claster, vector <Binary_Matrix>& B, vector <Point>& All_Point, Find_Claster& Q, vector <int>& A)
{
    //cout <<"int Field::Graf_Volna_Chain(int N, double d, int t, vector<Point>& Claster)"<<endl;
    int k = 1;
    int p;
    int n = All_Point.size();
    vector<Point> PP;
    PP.push_back(All_Point[N]);
    //cout<<"N="<<N<<endl;
    //cout<<"All_Point.size()="<<All_Point.size()<<endl;
    //cout<<"t="<<t<<endl;
    int h = 0;
    for (int j = 0; j < n; j++)
    {
        if (A[j] == 0)
        {
            h++;
        }
    }
    //cout<<" h="<<h<<endl;
    for (int j = 0; j < n; j++)
    {
        p = 0;
        //cout<<"B["<<u-1<<"].Get("<<N<<","<<j<<")=="<<B[u-1].Get(N,j)<<")&&(All_Point["<<j<<"].GetA()=="<<All_Point[j].GetA()<<")"<<endl;
        if ((B[u - 1].Get(N, j) == 1) && (A[j] == 0))
        {
            p++;
            A[j] = (t + 1);
            Claster.push_back(All_Point[j]);
            PP.push_back(All_Point[j]);
            //PP[PP.size()-1].SetTip(All_Point[j].GetTip());
            //cout<<"PP.["<<PP.size()-1<<"]).GetTip()="<< PP[PP.size()-1].GetTip()<<"="<<All_Point[j].GetTip()<<endl;
            k = Graf_Volna_Chain(j, u, t + 1, Claster, B, All_Point, Q, A);
            Q.SetPrint(PP);
            PP.clear();
            PP.push_back(All_Point[N]);
            if (N > k)k = N;
        }
        //cout<<"p="<<p<<endl;
    }
    return p;
}
