//Semenov Nikita 211
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;
#define CLOUD 20
#define E 0.01
#define pi 3.1415926535
#include "Point.h"
class Segment
{
private:
    Point A;
    Point B;
    int S; // ñîñòîÿíèå ðàâíî 1- äîñòðîåí 0-íåäîñòðîåí
public:
    Segment(const Segment& p) = default;
    Segment() = default;
    ~Segment() = default;

    void Set_Tip(const int& T) { S = T; }
    void Set_A(const Point& PP) { A = PP; }
    void Set_B(const Point& PP) { B = PP; }

    int Get_S() { return S; }
    Point Get_A() { return A; }
    Point Get_B() { return B; }
};


