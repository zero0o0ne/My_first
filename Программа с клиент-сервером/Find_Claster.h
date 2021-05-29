//211-Pushkareva-Anna-2021
#pragma once
#include "Point.h"
#include "Cluster.h"
#include "TreeNode.h"
#include "TreeNode_H.h"
class Find_Claster
{
private:
    double alfa;
    vector <Cluster> FC;
    vector <TreeNode_H> Tree;
    vector< vector <Point> > Print_Point;
    vector <Point>  Pyl;
    vector <Point>  Peref;
    vector <Point>  Bas;
    vector < vector <double>> Ind_valyu;
    string S;
    int k;
public:
    Find_Claster(const Find_Claster& p) = default;
    Find_Claster() { k = alfa = 0; }
    void SetAlfa(double p);
    double GetAlfa() { return alfa; }
    Cluster Get_Cluster(int i) { return FC[i];}
    void SetS(string s);
    string GetS();

    void SetPyl(Point& A);
    void SetPeref(Point& A);
    void SetBas(Point& A);
    void SetTree(vector <TreeNode_H> T) { Tree = T; }
    int GetK() { return k; }
    void SetK(int kk) { k = kk; }
    void SetInd(vector < vector <double>> Ind) { Ind_valyu = Ind; }
    void SetClaster(vector<Point>& A);
    int GetPrintSize();
    void SetPrint(vector<Point>& A);
    int GetSize() { return FC.size(); }
    void Calc_Dist_Matrix();
    void Print(string& file_name);
    double d(Point A, Point B) { return sqrt((A.GetX() - B.GetX()) * (A.GetX() - B.GetX()) + (A.GetY() - B.GetY()) * (A.GetY() - B.GetY())); }

};

