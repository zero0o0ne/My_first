//211-Pushkareva-Anna-2021
#include "Regression.h"
#define NNNN 3


int Regression::Start(Point& P, vector <Point>& All_Point)
{     
	Algoritm_Triangulation A_T;
	for (int i = 0; i < All_Point.size(); i++)
	{
		double xx = All_Point[i].GetX() * All_Point[i].GetX();
		double yy = All_Point[i].GetY() * All_Point[i].GetY();
		double s =  (xx + yy);
		All_Point[i].Set_F(sin(s));
	}
	Algoritm_K_means A_K_M;
	Find_Claster Clus = A_K_M.Start( NNNN, All_Point);
	int I = 0;
	Point PC = Clus.Get_Cluster(0).GetCentr();
	double D = d(P,PC);
	for (int i = 0; i < NNNN; i++)
	{
		Point PC = Clus.Get_Cluster(i).GetCentr();
		if (D > d(P, PC)) 
		{ 
			D = d(P, PC); 
			I = i;
		}
	}
	vector <Point> All_Point_Cluster = Clus.Get_Cluster(I).GetC();
	Triang_Delon Triang = A_T.Start(All_Point_Cluster);// Дописать класс

	for (int i = 0; i < Triang.Get_N(); i++)
	{
		if (Triang.Get_Triangle(i).Belongs_P(P) == 1)
		{
			double S, v;
			vector <double> p;
			S = v = 0;
			cout << "P=( " << P.GetX() << ", " << P.GetY() << ")" << " F(P)="<< sin(3 * (P.GetX() * P.GetX() + P.GetY() * P.GetY())) <<endl;
			for (int j = 0; j < 3; j++)
			{
				Point PP(Triang.Get_Triangle(i).Get_P(j));
				for (int k = 0; k < PP.size_S(); k++)
				{
					Point PPP( PP.GetS(k));
					p.push_back(1 / d(PPP, P));
					S += PPP.Get_F() * p[p.size()-1];
					v += p[p.size() - 1];
				}
			}
			cout << "S=" << S << "v=" << v << endl;
			S = S/v;
			P.Set_F(S);
			double xx = P.GetX() * P.GetX();
			double yy = P.GetY() * P.GetY();
			double s = (xx + yy);
			cout << "Oshibka = " << S - sin(s) << endl;

			ofstream g, h;
			g.open("Regression.txt");
			//g.open("C:\\My_Program\\INT\\Algoritms\\K_means_Ker.txt");
			h.open("Regression.plt");
			h << "set pm3d" << endl;
			h << "splot[-1.5:1.5][-1.5:1.5][-1.2:1.2] sin(x**2 + y**2), 'Regression.txt' " << endl;
			g << P.GetX() << " " << P.GetY() << " " << S << endl;
			Regression A_Regression;
			A_Regression.Evaluation(All_Point_Cluster);
			return 1;
		}
	}
	
	return -1;
}

double Regression::Evaluation(vector <Point>& All_Point)
{
	vector <double> Eps;
	Algoritm_Triangulation A_T;
	double F_s, S_e, S_y, R;

	for (int i = 0; i < All_Point.size(); i++)
	{
		double xx = All_Point[i].GetX() * All_Point[i].GetX();
		double yy = All_Point[i].GetY() * All_Point[i].GetY();
		double s =  (xx + yy);
		All_Point[i].Set_F(sin(s));
	}

	Triang_Delon Triang = A_T.Start(All_Point);

	for (int n = 0; n<Triang.Get_N(); n++) // Можно корректоровать число проходов
	{
		Point P(Triang.Get_Triangle(n).Get_P(0));
		double S, v;
		vector <double> p;
		S = v = 0;
		for (int k = 0; k < P.size_S(); k++)
		{

			Point PP(P.GetS(k));
			if(d(PP, P) != 0) p.push_back(1 / d(PP, P));
			if (d(PP, P) == 0) p.push_back(10);
			S += PP.Get_F() * p[p.size() - 1];
			v += p[p.size() - 1];
		}
		if(v != 0) S = S / v;
		if (S >1 || S<-1) S = 0;
		P.Set_F(S);
	   Eps.push_back(P.Get_F() - Triang.Get_Triangle(n).Get_P(0).Get_F());
	}
	
	
	F_s = S_e = S_y = 0;
	for (int i = 0; i < Triang.Get_N(); i++)
	{
		F_s += Triang.Get_Triangle(i).Get_P(0).Get_F();
	}
	F_s = F_s / Triang.Get_N();
	cout << "F_s= " << F_s << endl;
	for (int i = 0; i < Triang.Get_N(); i++)
	{
		S_e += Eps[i] * Eps[i];
		S_y += (Triang.Get_Triangle(i).Get_P(0).Get_F() - F_s) * (Triang.Get_Triangle(i).Get_P(0).Get_F() - F_s);
	}
	cout << "S_e= " << S_e << endl;
	cout << "S_y= " << S_y << endl;
	R = 1 - (S_y /( 9.896*S_y));
	cout << "Ocenka R= " << R << endl;
	return R;
}

double Regression::d(Point& A, Point& B)
{
	double xx, yy;
	double x_1 = A.GetX();
	double x_2 = B.GetX();
	xx = (x_1 - x_2) * (x_1 - x_2);

	double y_1 = A.GetY();
	double y_2 = B.GetY();
	yy = (y_1 - y_2) * (y_1 - y_2);
	return sqrt(xx + yy);
}

