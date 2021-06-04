
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"

class Cloud
{
private:
	vector <Point> P;
	int NP;
	double R, D;
	Point Cenr1[2], Peref[2];


public:
	Cloud();
	Cloud(const Cloud& c);
	~Cloud() = default;
	Point& GetPoint(int index);
	int NamPointX(double a, double b);
	int NamPointY(double a, double b);
	void SetPoint(Point& p);
	const Cloud& operator=(const Cloud& b);
	int Get_NP() { NP = P.size(); return NP; }
	void Set_NP(int n) { NP = n; }
	int GetSize();
	int GetSize() const;
	void Rotation(double centr_x, double centr_y, double a);
	void Compr(double centr_x, double centr_y, double a);
	void Move(double centr_x, double centr_y);
	double Get_Point_X(int n);
	double Get_Point_Y(int n);
	int Get_Point_ID(int n);
	double Get_R();
	double Get_D();
	void  Set_R(double n);
	void  Set_D(double n);
	double MAX_X();
	double MIN_X();
	double MAX_Y();
	double MIN_Y();
	void Print_Cloud(string& file_name);

	//void Print(FILE *f);
};
