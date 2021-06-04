
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Point.h"
#include "Dist_Matrix.h"
#include "TreeNode.h"
#include "Find_Claster.h"
#include "H_Point.h"
#include "TreeNode_H.h"
#include <string>
#define E 0.01
#define pi 3.1415926535
class Algoritm_Hierarchy
{
public:
    Find_Claster Start(int n, vector <Point>& All_Point);
    double d(H_Point& A, H_Point& B);

};
