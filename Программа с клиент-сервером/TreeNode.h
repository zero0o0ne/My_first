//211-Pushkareva-Anna-2021
#pragma once
#include "Point.h"
class TreeNode
{
private:
    Point Po;
    double h;
    int ip, il, ir;

public:
    TreeNode() = default;
    ~TreeNode() = default;
    TreeNode(const TreeNode& point) = default;
    void  SetPoint(const Point& B) { Po = B; }
    Point GetPoint() { return Po; }
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
