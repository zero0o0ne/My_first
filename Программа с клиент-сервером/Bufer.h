
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include "Cloud.h"
#include "Field.h"

class Bufer
{
private:
    Field F;
    Cloud C;
    int nf, nc;
public:
    Bufer() { nf = 0; nc = 0; }
    void Get_Cloud(Cloud& c);
    void Get_Field(Field& FI);
    Cloud& Set_Cloud();
    Field& Set_Field();
    void Rotation_Cloud(double centr_x, double centr_y, double a);
    void Rotation_Field(double centr_x, double centr_y, double a);
    void Compr_Cloud(double centr_x, double centr_y, double a);
    void Compr_Field(double centr_x, double centr_y, double a);
    void Move_Field(double centr_x, double centr_y);
    void Move_Cloud(double centr_x, double centr_y);
};

