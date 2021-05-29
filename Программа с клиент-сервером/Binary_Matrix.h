//211-Pushkareva-Anna-2021
#pragma once
#include <vector>
class Binary_Matrix
{
private:
    std::vector <double> B;
    int n;
    double r;
public:
    Binary_Matrix() { n = r = 0.0; }
    ~Binary_Matrix() = default;
    int GetN() { return n; }
    int GetSize() { return B.size(); }
    void SetN(int k) {
        int i;
        n = k;
        B.clear();
        for (i = 0; i < n * n; i++)
        {

            B.push_back(0);
        }
    }
    double GetR() { return r; }
    void SetR(double k) { r = k; }
    double Get(int i, int j) {
        /*cout<<"\n";
        cout<<"i*n+j="<<i*n+j<<"\n";
        cout<<"B.size()="<<B.size()<<"\n";
        cout<<"B[i*n+j]="<<B[i*n+j]<<"\n";
        cout<<"B[0]="<<B[0]<<"\n";*/
        return B[i * n + j];
    }
    void Set(int i, int j, double a) { B[i * n + j] = a; }
};

