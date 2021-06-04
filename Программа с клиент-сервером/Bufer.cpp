
//Programma Semenova Nikity iz 211 gruppy
#include "Bufer.h"

void Bufer::Get_Field(Field& FI)
{
    F = FI;
    nf = 1;
}
void Bufer::Get_Cloud(Cloud& c)
{
    //if(nc==0){return;}
   //printf("void Bufer::Get_Cloud(Cloud &c)\n");
  // printf("c.GetSize()=%d\n",c.GetSize());
  // printf("C.GetSize()=%d\n",C.GetSize());
    C = c;
    // printf("C.GetSize()=%d\n",C.GetSize());
    nc = 1;
}
Cloud& Bufer::Set_Cloud()
{
    //if(nc==0){return;}
   // printf("Cloud Bufer::Set_Cloud()\n");
    //printf("C[n].GetSize()=%d\n",C.GetSize());
    nf = 0;
    Cloud& K = C;
    return K;
}
Field& Bufer::Set_Field()
{
    Field& k = F;//if(nf==0){return ;}
    return k;
    nf = 0;
}
void Bufer::Rotation_Cloud(double centr_x, double centr_y, double a)
{
    C.Rotation(centr_x, centr_y, a);
}
void Bufer::Rotation_Field(double centr_x, double centr_y, double a)
{
    F.Rotation(centr_x, centr_y, a);
}
void Bufer::Compr_Cloud(double centr_x, double centr_y, double a)
{
    C.Compr(centr_x, centr_y, a);
}
void Bufer::Compr_Field(double centr_x, double centr_y, double a)
{
    F.Compr(centr_x, centr_y, a);
}
void Bufer::Move_Field(double centr_x, double centr_y)
{
    //printf("void Bufer::Move_Field(double centr_x, double centr_y)\n");
    F.Move(centr_x, centr_y);
}
void Bufer::Move_Cloud(double centr_x, double centr_y)
{
    C.Move(centr_x, centr_y);
}
