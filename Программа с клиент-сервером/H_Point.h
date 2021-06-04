
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>

class H_Point
{
public:
    H_Point();
    H_Point(double xx, double yy);
    H_Point(const H_Point& p);
    ~H_Point() = default;
    double GetX();
    double GetY();
    int GetV() { return ves; }
    void SetV(int u) { ves = u; }

    void SetX(double xx) { x = xx; }
    void SetY(double yy) { y = yy; }

    double GetTree() { return tree; }
    void SetTree(int xx) { tree = xx; }

    int GetID();
    void SetID(int n);

    void SetA(int n);
    int GetA();

    const H_Point& operator=(const H_Point& b);
    void  Print(FILE* f, int n);



private:
    double x, y;
    int ID;
    int a, b, tree;
    int ves;
};

