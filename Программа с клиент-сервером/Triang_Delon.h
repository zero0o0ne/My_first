//211-Pushkareva-Anna-2021
#pragma once
#include "Triangle.h"

class Triang_Delon
{
private:
    vector <Triangle> TD;
public:
    Triang_Delon(const Triang_Delon& p) = default;
    Triang_Delon() = default;
    ~Triang_Delon() = default;

    void Set_Triangle(const Triangle& PP)
    {
        TD.push_back(PP);
    }
    Triangle Get_Triangle(int n) { return TD[n]; }
    int Get_N() { return TD.size(); }

};

