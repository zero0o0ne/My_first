
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"
#include "Triang_Delon.h"
#include "TreeNode.h"
#include "Find_Claster.h"
#include "Dist_Matrix.h"
#include "Binary_Matrix.h"
#include "Cloud.h"
#include "Algoritm_Wave.h"
#include "Algoritm_DBSCAN.h"
#include "Algoritm_S_Tree.h"
#include "Algoritm_K_means.h"
#include "Algoritm_K_means_Ker.h"
#include "Algoritm_EM.h"
#include "Algoritm_Forel.h"
#include "Algoritm_Hierarchy.h"
class Field
{
private:
	Triang_Delon TD;
	//Diagramma_Voronogo DV;
	Cloud C[CLOUD];
	vector <Point> All_Point;
	Dist_Matrix D;
	vector <Binary_Matrix> B;
	//vector <vector <double>> B;
	vector <Find_Claster> FC;

	//vector <int> STree;
	int NC, NP;
	int Sostoyanie;
	TreeNode root;
	vector<int> XK;
	vector<int> YK;

public:
	int Get_NFC() { return FC.size(); }
	int Get_NBM() { return B.size(); }
	Field();
	Field(double xx);
	void SetCloud(Cloud& c);
	Cloud& GetCloud(int index);
	//Field(const Field &v);
	//~Field() = default;
	void sostoyanie(int n) { Sostoyanie = n; }
	const Field& operator=(const Field& b);
	int Get_NP();
	int Get_NC() { return NC; }
	int Get_NCL() { return FC.size(); }
	void Set_NC(int n) { NC = n; }
	int GetSize();
	void Set_NP(int n) { NP = n; }
	vector <Point> Get_All() { return All_Point; }
	Dist_Matrix Get_D_Matrix() { return D; }
	vector <Binary_Matrix> Get_B() { return B; }
	double MIN_X();
	double MIN_Y();
	double MAX_X();
	double MAX_Y();
	void VectorX(int nx);
	void VectorY(int ny);
	void VectorX(int nx, int n);
	void VectorY(int ny, int n);



	//void Wave (int N);
	//int Graf_Volna_Chain(int N, int u, int t, vector <Point>& Claster);

	void Rotation(double centr_x, double centr_y, double a);
	void Compr(double centr_x, double centr_y, double a);
	void  Move(double centr_x, double centr_y);

	void Print_Field(string& file_name);
	void Print_Claster(string& file_name, int n);
	void Print_Cloud(string& file_name, int& n);

	int GetSizeCloud(int n);
	int NamPointX(double a, double b);
	int NamPointY(double a, double b);
	void Gistogram(string& file_name_x, string& file_name_y, double nx, double ny);
	void Gistogram(string& file_name_x, string& file_name_y, double nx, double ny, int n);
	void Calc_Dist_Matrix();
	void Binary(double R);
	string Find_Cluster_Info();
	double d(Point& A, Point& B);
	void Find_Factor();
	int Triangulation();
	Point IntersectL(double A, double B, double C, double A1, double B1, double C1);//Ðàáîòàåò íà ïåðåñåêàþùèõñÿ ïðÿìûõ èíà÷å âîçâðàùàåò çíà÷åíèÿ íåâåðòíûå
	Point Intersection_Parabol(Point Focus, Point Focus_R, Point Focus_L, double d);// äëÿ íåâûðîæäåííûõ ïàðàáîë, âûâîäèò îòðåçîê ïåðåñå÷ííèÿ öåíòðàëüíîé ñ ïðàâîé è ëåâîé ïàðàáîëîé
};
static int Namber_point = 1;


