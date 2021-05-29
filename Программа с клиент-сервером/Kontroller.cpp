//211-Pushkareva-Anna-2021
#include "Kontroller.h"
#include <iomanip>
#include <ctime>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

Kontroller::Kontroller()
{
    protokol = 1;
    file = "logK.txt";
}
Field Kontroller::Get_Field()
{
    //time_t t;
    //t = time(0);
    //cout << puts(ctime(&t));
    //cout << std::put_time(local, "%F") << std::endl;
    //cout << std::put_time(local, "%T") << std::endl;

    Log << "Get_Field " << endl << endl;
    return FI;
}
Cloud Kontroller::Get_Cloud(int index)
{
    std::time_t t = std::time(0);
    std::tm* local = std::localtime(&t);
    Log << std::put_time(local, "%F") << std::endl;
    Log << std::put_time(local, "%T") << std::endl;
    Log << "Get_Cloud " << endl << endl;
    return FI.GetCloud(index);
}
void Kontroller::Field_Info()
{

    time_t t;
    t = time(0);
    cout << puts(ctime(&t));
    Log << "Field_Info " << endl << endl;
    printf("Informaciya o pole:\n");
    printf("Chislo oblakov       -  %d\n", FI.Get_NC());
    printf("Chislo tochek        -  %d\n", FI.Get_NP());
    printf("Chislo Find_Claster  -  %d\n", FI.Get_NFC());
    printf("Chislo Binary_Matrix -  %d\n", FI.Get_NBM());
    Log << "Informaciya o pole:" << endl;
    Log << "Chislo oblakov       -  " << FI.Get_NC() << endl;
    Log << "Chislo tochek        -  " << FI.Get_NP() << endl;
    Log << "Chislo Find_Claster  -  " << FI.Get_NFC() << endl << endl;
    //Log<<"Chislo Binary_Matrix -  "<<FI.Get_NBM()<<endl<<endl;
}
void Kontroller::Find_Cluster_Info()
{
    time_t t;
    t = time(0);
    cout << puts(ctime(&t));
    Log << "Find_Cluster_Info " << endl << endl;
    Log << Find_Cluster_Info_1() << endl << endl;
}
void Kontroller::Set_Field()
{
    time_t t;
    t = time(0);
    cout << puts(ctime(&t));
    Log << "Set_Field " << endl << endl;
    Bufer.Get_Field(FI);
}
void Kontroller::Get_F()
{
    FI = Bufer.Set_Field();
}
void Kontroller::Set_Cloud(int n)
{
    time_t t;
    t = time(0);
    cout << puts(ctime(&t));
    Log << "Set_Cloud " << n << endl << endl;
    Cloud K;
    K = FI.GetCloud(n - 1);
    Bufer.Get_Cloud(K);
}
void Kontroller::Get_Cloud()
{
    time_t t;
    t = time(0);
    cout << puts(ctime(&t));
    Log << "Get_Cloud " << endl << endl;
    Cloud K;
    K = Bufer.Set_Cloud();
    FI.SetCloud(K);
}

void Kontroller::Gen_Cloud(double& centr_x, double& centr_y, double& dispersiya_x, double& dispersiya_y, int& n)
{
    
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Gen_Cloud " << centr_x << " " << centr_y << " " << dispersiya_x << " " << dispersiya_y << " " << n << endl << endl;

    int i, j, xx, yy, bx, by;
    double sum_x, sum_y;
    vector <double> massiv_x, massiv_y;
    //massiv_x[n * 3], massiv_y[n * 3];
    Point centr(centr_x, centr_y);
    Cloud Cl;

    for (int i = 0; i < n * 3; i++)
    {
        double a;
        massiv_x.push_back(a);
        massiv_y.push_back(a);
    }
    srand(time_t(NULL));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n * 3; j++)
        {
            xx = rand();
            yy = rand();
            bx = xx % 4;
            //printf("bx=%d\n",bx);
            //printf("by=%d\n",by);
            by = yy % 4;

            if (bx == 0 || bx == 1)
            {
                massiv_x[j] = (((double)xx) / RAND_MAX);
            }
            else
            {
                xx = xx * (-1);
                massiv_x[j] = (((double)xx) / RAND_MAX);
            }
            if (by == 0 || by == 1)
            {
                massiv_y[j] = (((double)yy) / RAND_MAX);
            }
            else
            {
                yy = yy * (-1);
                massiv_y[j] = (((double)yy) / RAND_MAX);
            }

        }

        sum_x = sum_y = 0;
        for (j = 0; j < n * 3; j++)
        {
            sum_x = sum_x + massiv_x[j];
            sum_y = sum_y + massiv_y[j];
            //printf("sum_x=%lf sum_y=%lf\n",sum_x,sum_y);
        }
        //printf("sum_x=%lf sum_y=%lf\n",sum_x,sum_y);
        //printf("\n");
        sum_x = centr.GetX() + ((sum_x / (n * 3)) * dispersiya_x);
        sum_y = centr.GetY() + ((sum_y / (n * 3)) * dispersiya_y);

        Point G(sum_x, sum_y);
        //printf("sum_x=%lf sum_y=%lf i=%d\n",G.GetX(),G.GetY(),i);
        //printf("\n");

        Cl.SetPoint(G);
    }
    //printf("FI.GetSize() %d\n",FI.GetSize());
    FI.SetCloud(Cl);
    //printf("FI.GetSize() %d\n",FI.GetSize());
    //printf("2\n");

}
void Kontroller::Rotation(double centr_x, double centr_y, double a)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Move_Cloud " << centr_x << " " << centr_y << " " << a << endl << endl;
    Bufer.Rotation_Field(centr_x, centr_y, a);
}
void Kontroller::Rotation_Cloud(double centr_x, double centr_y, double a)
{
    time_t t;
    t = time(0);
    Log << puts(ctime(&t))<<endl;
    Log << "Rotation_Cloud " << centr_x << " " << centr_y << " " << a << endl << endl;
    Bufer.Rotation_Cloud(centr_x, centr_y, a);
}
void Kontroller::Compr(double centr_x, double centr_y, double a)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Move_Cloud " << centr_x << " " << centr_y << " " << a << endl << endl;
    Bufer.Compr_Field(centr_x, centr_y, a);
}
void Kontroller::Compr_Cloud(double centr_x, double centr_y, double a)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Move_Cloud " << centr_x << " " << centr_y << " " << a << endl << endl;
    Bufer.Compr_Cloud(centr_x, centr_y, a);
}
void Kontroller::Move(double centr_x, double centr_y)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Move_Cloud " << centr_x << " " << centr_y << endl << endl;
    Bufer.Move_Field(centr_x, centr_y);
}
void Kontroller::Move_Cloud(double centr_x, double centr_y)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Move_Cloud " << centr_x << " " << centr_y << endl << endl;
    Bufer.Move_Cloud(centr_x, centr_y);
}


void Kontroller::Print_Field(string& file_name)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Print_Claster " << file_name << endl << endl;
    FI.Print_Field(file_name);
}
void Kontroller::Print_Claster(string& file_name, int n)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Print_Claster " << file_name << " " << n << endl << endl;
    //FI.Print_Claster(file_name, n);
    FC[n - 1].Print(file_name);
}
void Kontroller::Print_Cloud(string& file_name, int& n)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Print_Cloud " << file_name << " " << n << endl << endl;
    FI.Print_Cloud(file_name, n);
}


void Kontroller::Gistogram(double& nx, double& ny, string& file_name_x, string& file_name_y)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Gistogram " << file_name_x << " " << file_name_y << " " << nx << " " << ny << endl << endl;
    FI.Gistogram(file_name_x, file_name_y, nx, ny);
}
void Kontroller::Gistogram(double& nx, double& ny, string& file_name_x, string& file_name_y, int n)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Gistogram " << file_name_x << " " << file_name_y << " " << nx << " " << ny << " " << n << endl << endl;
    FI.Gistogram(file_name_x, file_name_y, nx, ny, n);
}
void Kontroller::Calc_Dist_Matrix()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Calc_Dist_Matrix " << endl << endl;
    FI.Calc_Dist_Matrix();
}
void Kontroller::Binary(double R)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Binary " << R << endl << endl;
    FI.Binary(R);
}

void Kontroller::Wave(int n)
{

    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Wave " << n << endl << endl;

    B = FI.Get_B();
    All_Point = FI.Get_All();
    if (n > B.size()) {
        cout << "Nevernoe N" << endl;
        return;
    }
    FC.push_back(A_Wave.Start(n, B, All_Point));

}
void Kontroller::DBSCAN(int k, int n)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "DBSCAN " << k << " " << n << endl << endl;
    B = FI.Get_B();
    All_Point = FI.Get_All();
    if (n > B.size()) {
        cout << "Nevernoe n" << endl;
        return;
    }
    Sostoyanie = 0;
    FC.push_back(A_DBSCAN.Start(k, n, B, All_Point));

    //FI.DBSCAN(k,n);
}

void Kontroller::Regression(double x, double y)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Regression " << x <<" "<<y<< endl << endl;
    All_Point = FI.Get_All();
    Sostoyanie = 1;
    Point P(x, y);
    A_Regression.Start(P, All_Point);
    
}
void Kontroller::K_means(int k)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "K_means " << k << endl << endl;
    All_Point = FI.Get_All();
    Sostoyanie = 1;
    FC.push_back(A_K_means.Start(k, All_Point));
}
void Kontroller::EM(int k)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    All_Point = FI.Get_All();
    Log << "EM " << k << endl << endl;
    Sostoyanie = 1;
    FC.push_back(A_EM.Start(k, All_Point));
}
void Kontroller::K_means_Ker(int k, int u)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "K_means_Ker " << k << " " << u << endl << endl;
    All_Point = FI.Get_All();
    Sostoyanie = 1;
    FC.push_back(A_K_means_Ker.Start(k, u, All_Point));
}
void Kontroller::S_Tree()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "S_Tree" << endl << endl;

    B = FI.Get_B();
    All_Point = FI.Get_All();
    D = FI.Get_D_Matrix();

    if (D.GetZ() == 0) { cout << "Oshibka - Matrica D ne sozdana" << endl; return; }
    A_S_Tree.Start(STree, All_Point, D);
    ofstream com;
    string d = "Command_GP_";
    string file_name = "Print_Tree.txt";
    d = d + file_name.c_str();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d = d + "plt";
    com.open(d);
    com << "set xrange[-20:20] " << endl;
    com << "set yrange[-10:10] " << endl;
    com << "plot 'Point.txt' u 1:2 w p,";
    com << " 'Print_Tree.txt' u 1:2 w linespoints," << endl;
    com.close();
    //cout<<"ok"<<endl;
    Print_Tree();
}
void Kontroller::Print_Tree()
{
    time_t t;
    t = time(0);
    Log << puts(ctime(&t));
    Log << "Print_Tree()" << endl << endl;
    ofstream f;
    string file_name = "Print_Tree.txt";
    f.open("Print_Tree.txt");
    int n = D.GetN();

    for (int i = 0; i < All_Point.size(); i++)
    {
        for (int j = 0; j < All_Point.size(); j++)
        {
            if (STree[i * n + j] == 1)
            {
                f << All_Point[i].GetX() << "  " << All_Point[i].GetY() << "  " << endl;
                f << All_Point[j].GetX() << "  " << All_Point[j].GetY() << "  " << endl;
                f << endl;
                f << endl;
            }

        }
    }

    f.close();
}
void Kontroller::S_Tree_Gist()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "S_Tree_Gist()" << endl << endl;
    if (D.GetZ() == 0) {
        cout << "Oshibka - Matrica D ne sozdana" << endl;
        return;
    }

    vector <double> V;
    vector <int> G;
    int i, j;
    int n = All_Point.size();

    for (i = 0; i < All_Point.size(); i++)
    {
        for (j = 0; j < i + 1; j++)
        {
            if (STree[i * n + j] == 1) { V.push_back(D.Get(i, j)); }
        }
    }
    double M, m;
    M = m = V[0];
    for (i = 0; i < V.size(); i++)
    {
        if (m > V[i]) { m = V[i]; }
        if (M < V[i]) { M = V[i]; }
    }
    for (double j = 1; j < (M - m) * 2 / m; j++)
    {
        for (i = 0; i < V.size(); i++)
        {
            G.push_back(0);
        }
    }
    for (double j = 1; j < (M) * 2 / m + 1; j++)
    {
        for (i = 0; i < V.size(); i++)
        {
            //cout<<"i="<<i<<" "<<V[i]<<"<="<<m/2*j<<" && "<<V[i]<<">"<<m/2*(j-1)<<endl;
            if (V[i] <= m * j && V[i] > m * (j - 1)) { G[j - 1]++; }
        }

    }
    cout << "m=" << m << endl;
    cout << "M=" << M << endl;
    M = G[0];
    for (i = 0; i < G.size(); i++)
    {
        if (M < G[i]) { M = G[i]; }
    }
    ofstream f;
    ofstream com;
    string file_name = "S_Tree_Gist.txt";
    f.open(file_name.c_str());
    if (!f.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
        return;
    }

    for (i = 0; unsigned(i) < G.size(); i++)
    {
        f << G[i] << endl;
    }
    f.close();

    com.open("Command_GP_Gist_Tree.plt");
    if (!com.is_open())
    {
        cout << "Oshibka otkrytiya fila" << endl;
    }
    else
    {
        com << "set xrange[0:" << V.size() << "] " << endl;
        com << "set yrange[0:]" << endl;
        com << "set style data histogram" << endl;
        com << "set style fill solid " << endl;
        com << "set style fill solid " << endl;
        com << "set boxwidth 3" << endl;
        com << "plot 'S_Tree_Gist.txt' " << endl;
        //printf("com <<plot 'Gist_x.txt', 'Gist_y.txt' << endl;\n");

    }
    com.close();
}
void Kontroller::Forel(double R, int n)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Forel(double " << R << ",int " << n << ")" << endl;
    if (R <= 0 || n <= 0) { Log << "Nevernye parametry vvoda" << endl << endl; return; }
    All_Point = FI.Get_All();
    Sostoyanie = 1;
    vector <Find_Claster> QQ;
    QQ = A_Forel.Start(R, n, All_Point);
    for (int i = 0; unsigned(i) < QQ.size(); i++)
    {
        FC.push_back(QQ[i]);
    }
}
void Kontroller::Hierarchy(int n)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Hierarchy (int " << n << ")" << endl << endl;
    All_Point = FI.Get_All();
    Sostoyanie = 1;
    FC.push_back(A_Hierarchy.Start(n, All_Point));
}
void Kontroller::Find_Factor()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Find_Factor()" << endl << endl;
    FI.Find_Factor();
}
int Kontroller::Triangulation()
{
    FI.sostoyanie(0);
    time_t now = time(0);
    char* dt = ctime(&now);
    Log << dt;
    Log << "Triangulation()" << endl << endl;
    return FI.Triangulation();

}

string Kontroller::Find_Cluster_Info_1()
{
    int n, i;
    n = FC.size();
    string Str;
    printf("Informaciya o Find_Claster:\n");
    Str = "Informaciya o Find_Claster:\n";
    printf("Chislo Find_Claster -  %d\n", FC.size());
    Str += "Chislo Find_Claster - " + to_string(FC.size()) + "\n";
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << ") Algoritm - ";
        cout << FC[i].GetS();
        cout << " Kolichestvo clusterov=";
        cout << FC[i].GetSize();
        cout << " R=";
        cout << FC[i].GetAlfa();
        if (FC[i].GetS() == "DBSCAN") { cout << " k=" << FC[i].GetK() << endl; }
        cout << "\n";
        Str += to_string(i + 1) + ") Algoritm - " + FC[i].GetS();
        Str += " Kolichestvo clusterov=" + to_string(FC[i].GetSize()) + " R=" + to_string(FC[i].GetAlfa()) + "\n";
    }

    return Str;
}
