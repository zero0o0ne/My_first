//Semenov Nikita 211
#pragma once
#include "H_Point.h"

class TreeNode_H
{

private:
    H_Point Po;
    double h;
    int ip, il, ir;

public:
    TreeNode_H() = default;
    ~TreeNode_H() = default;
    TreeNode_H(const TreeNode_H& point) = default;
    void  SetPoint(const H_Point& B) { Po = B; }
    H_Point GetPoint() { return Po; }
    int GetP() { return ip; }
    int GetL() { return il; }
    int GetR() { return ir; }
    double Get_H() { return h; }
    void SetP(int i) { ip = i; }
    void SetL(int i) { il = i; }
    void SetR(int i) { ir = i; }
    void SetH(double H) { h = H; }
    int GetID() { return Po.GetID(); }
    double GetX() { return Po.GetX(); }
    double GetY() { return Po.GetY(); }

};

