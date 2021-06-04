
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include <vector>

class Dist_Matrix
{
private:
    std::vector <double> D;
    int n;
    int z;
public:
    Dist_Matrix() { z = n = 0; }
    ~Dist_Matrix() = default;
    int GetZ() { return z; }
    void SetZ(int p) { z = p; }
    int GetN() { return n; }
    void SetN(int k) {
        int i;
        n = k;
        D.clear();
        for (i = 0; i < n * n; i++)
        {

            D.push_back(0);
        }
    }
    double Get(int i, int j)
    {
        //cout <<"i*n+j"<<i*n+j<<endl;
       // cout<<"n="<<n<<endl;
        return D[i * n + j];
    }
    void Set(int i, int j, double a) { D[i * n + j] = a; }
};


