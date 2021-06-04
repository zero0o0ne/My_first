
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Field.h"
#include "Bufer.h"
#include "Algoritm_Wave.h"
#include "Algoritm_DBSCAN.h"
#include "Algoritm_S_Tree.h"
#include "Algoritm_K_means.h"
#include "Algoritm_K_means_Ker.h"
#include "Algoritm_EM.h"
#include "Algoritm_Forel.h"
#include "Algoritm_Hierarchy.h"
#include "Regression.h"
#include <chrono>
class Kontroller
{
private:
    int protokol;
    string file;
    ofstream Log;
    Field FI;
    Bufer Bufer;
    int Sostoyanie;
    vector <Find_Claster> FC;
    vector <Binary_Matrix> B;
    Dist_Matrix D;
    vector <Point> All_Point;

    Algoritm_Wave A_Wave;
    Algoritm_DBSCAN A_DBSCAN;
    Algoritm_S_Tree A_S_Tree;
    Algoritm_K_means A_K_means;
    Algoritm_K_means_Ker A_K_means_Ker;
    Algoritm_EM A_EM;
    Algoritm_Forel A_Forel;
    Algoritm_Hierarchy A_Hierarchy;
    Regression A_Regression; 

    vector <int> STree;

public:
    Kontroller();
    void Field_Info();
    string Find_Cluster_Info_1();
    void Find_Cluster_Info();
    void Log_On() { Log.open("Log_Kontr.txt"); }
    void Gistogram(double& nx, double& ny, string& file_name_x, string& file_name_y);
    void Gistogram(double& nx, double& ny, string& file_name_x, string& file_name_y, int n);
    void Gen_Cloud(double& centr_x, double& centr_y, double& dispersiya_x, double& dispersiya_y, int& n);

    void Rotation(double centr_x, double centr_y, double a);
    void Rotation_Cloud(double centr_x, double centr_y, double a);
    void Compr(double centr_x, double centr_y, double a);
    void Compr_Cloud(double centr_x, double centr_y, double a);
    void Move(double centr_x, double centr_y);
    void Move_Cloud(double centr_x, double centr_y);

    void Print_Field(string& file_name);
    void Print_Claster(string& file_name, int n);
    void Print_Cloud(string& file_name, int& n);
    void Calc_Dist_Matrix();
    void Binary(double R);
    void K_means(int k);
    void K_means_Ker(int k, int u);
    void EM(int k);
    Field Get_Field();
    Cloud Get_Cloud(int index);
    void Wave(int n);
    void DBSCAN(int k, int n);
    //void Wave_DB(int n);
    void S_Tree();

    void Set_Field();
    void Get_F();
    void Set_Cloud(int n);
    void Get_Cloud();
    void S_Tree_Gist();
    void Print_Tree();
    void Forel(double R, int n);
    void Hierarchy(int n);
    void Find_Factor();
    int  Triangulation();
    void Regression(double x, double y);
};

