
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
using namespace std;
class Point
{
private:
	double x, y, F;
	int ID;
	vector <Point> Sosedi;

public:
	Point();
	Point(double xx, double yy);
	Point(const Point& p);
	~Point() = default;
	double GetX();
	double GetY();
	int size_S() { return Sosedi.size(); }
	Point GetS(int i) { return Sosedi[i]; }


	void SetX(double xx) { x = xx; }
	void SetY(double yy) { y = yy; }
	void SetS(Point& P) { Sosedi.push_back(P); }
	int GetID();
	void SetID(int n);


	const Point& operator=(const Point& b);
	void  Print(FILE* f, int n);
	double Get_F() { return F; }
	void Set_F(double SS) { F = SS; }
};
