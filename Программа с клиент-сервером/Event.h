
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"
#include "Segment.h"

class Event
{
private:
    int Tip; // 0-sobytie tochki 1-sobytie kruga
    Point P; // koordinaty tochki
    int N; // nomer tochki roditelya (sluchay sobytiya tochki)
    vector <Point> Parent; // koordinaty roditelya
    vector <int> NW; // nomera identifikatory obrazuyushih voln
public:
    Event(const Event& p) = default;
    Event() = default;
    ~Event() = default;

    void Set_Tip(const int& T) { Tip = T; }
    void Set_P(const Point& PP) { P = PP; }
    void Set_N(const int& NN) { N = NN; }
    void Set_Parent(const Point& PP)
    {
        Parent.push_back(PP);
    }
    void Set_NW(const int& n)
    {
        NW.push_back(n);
    }

    int Get_Tip() { return Tip; }
    Point Get_P() { return P; }
    int Get_N() { return N; } // nomer tochki roditelya (sluchay sobytiya tochki)
    Point Get_Parent(const int& n) { return Parent[n]; } // koordinaty roditelya
    int Get_NW(const int& n) { return NW[n]; }
};
