//211-Pushkareva-Anna-2021
#include "Algoritm_Triangulation.h"

Triang_Delon Algoritm_Triangulation::Start(vector<Point>& All_Point)
{
    //cout<<"int Field::Triangulation()"<<endl;
    double MIN_X, MAX_X, MIN_Y, MAX_Y;
    Triang_Delon TD;
    vector <Triangle> TR;
    vector <Triangle> TR20;
    MIN_X = All_Point[0].GetX();
    MAX_X = All_Point[0].GetX();
    MIN_Y = All_Point[0].GetX();
    MAX_Y = All_Point[0].GetX();
    for (int i = 0; i < All_Point.size(); i++)
    {
        if (MIN_X > All_Point[i].GetX()) MIN_X = All_Point[i].GetX();
        if (MAX_X < All_Point[i].GetX()) MAX_X = All_Point[i].GetX();
        if (MIN_Y > All_Point[i].GetY()) MIN_Y = All_Point[i].GetY();
        if (MAX_Y < All_Point[i].GetY()) MAX_Y = All_Point[i].GetY();
    }
    MIN_X = MIN_X - 10;
    MIN_Y = MIN_Y - 10;
    MAX_X = MAX_X + 10;
    MAX_Y = MAX_Y + 50;
    //cout<<MAX_Y<<endl;
    Point A, B, C;
    if (fabs(MAX_X - MIN_X) > (MAX_Y - MIN_Y))
    {
        A.SetX(2 * MIN_X - fabs(MAX_X - MIN_X));
        A.SetY(2 * MAX_Y);
        B.SetX(2 * MAX_X + fabs(MAX_X - MIN_X));
        B.SetY(2 * MAX_Y);
        C.SetX(MIN_X + fabs(MAX_X - MIN_X) * 0.5);
        C.SetY(MAX_Y - 1.8 * fabs(MAX_X - MIN_X) * 2);
    }
    if (fabs(MAX_X - MIN_X) <= (MAX_Y - MIN_Y))
    {
        A.SetX((MIN_X + MAX_Y) - 2 * fabs(MAX_Y - MIN_Y));
        A.SetY(2 * MAX_Y);
        B.SetX((MIN_X + MAX_Y) + 2 * fabs(MAX_Y - MIN_Y));
        B.SetY(2 * MAX_Y);
        C.SetX(0.5 * (MIN_X + MAX_Y));
        C.SetY(MAX_Y - 1.8 * fabs(MAX_Y - MIN_Y) * 2);
    }

  
    Triangle F;
    F.Set_P(A);
    F.Set_P(B);
    F.Set_P(C);
    F.Set_I(-1);
    TR.push_back(F);
    vector <Segment> Obolochka;
    Segment OB;
    OB.Set_A(A);
    OB.Set_B(B);
    Obolochka.push_back(OB);
    OB.Set_A(B);
    OB.Set_B(C);
    Obolochka.push_back(OB);
    OB.Set_A(C);
    OB.Set_B(A);
    Obolochka.push_back(OB);

    for (int i = 0; i < All_Point.size(); i++)
    {
        vector <Segment> Rbr;
        vector <int> Int;
        //cout<<"TR.size()="<<TR.size()<<endl;
        for (int j = 0; j < TR.size(); j++)
        {
            if (TR[j].Belongs(All_Point[i]) == 1)
            {
                //cout<<"Rbr.size()="<<Rbr.size()<<" "<<TR[j].Belongs(All_Point[i])<<endl;
                Segment Seg;
                int k = 0;
                Seg.Set_A(TR[j].Get_P(0));
                Seg.Set_B(TR[j].Get_P(1));
                if (k == 0) Rbr.push_back(Seg);

                Seg.Set_A(TR[j].Get_P(1));
                Seg.Set_B(TR[j].Get_P(2));
                if (k == 0) Rbr.push_back(Seg);

                Seg.Set_A(TR[j].Get_P(2));
                Seg.Set_B(TR[j].Get_P(0));

                if (k == 0) Rbr.push_back(Seg);
                Int.push_back(j);
                // cout<<"Rbr.size()="<<Rbr.size()<<endl;
            }
        }

        for (int k = 0; k < Int.size(); k++)
        {
            for (int g = 0; g < Int.size() - 1; g++)
            {
                if (Int[g] < Int[g + 1])
                {
                    int a = Int[g + 1];
                    Int[g + 1] = Int[g];
                    Int[g] = a;
                }
            }
        }

        for (int p = 0; p < Int.size(); p++)
        {
            for (int k = Int[p]; k < TR.size() - 1; k++)
            {
                TR[k] = TR[k + 1];
            }
            if (TR.size() > 1) TR.pop_back();

        }

        for (int k = 0; k < Rbr.size(); k++)
        {
            for (int s = 0; s < TR.size(); s++)
            {
                if (TR[s].Belongs_S(Rbr[k]) == 1)
                {   
                    Point A = Rbr[k].Get_A();
                    Point B = Rbr[k].Get_B();
                    Point All = All_Point[i];
                    A.SetS(B);
                    A.SetS(All);
                    B.SetS(A);
                    B.SetS(All);
                    All.SetS(A);
                    All.SetS(B);
                    Triangle F;
                    F.Set_P(A);
                    F.Set_P(B);
                    F.Set_P(All);
                    //                    cout<<"A=("<<Rbr[k].Get_A().GetX()<<", "<<Rbr[k].Get_A().GetY()<<")"<<endl;
                    //                    cout<<"B=("<<Rbr[k].Get_B().GetX()<<", "<<Rbr[k].Get_B().GetY()<<")"<<endl;
                    TR20.push_back(F);
                }
            }
        }
        //    cout<<"TR20.size()="<<TR20.size()<<endl;
        for (int p = 0; p < TR20.size(); p++)
        {
            TR.push_back(TR20[p]);
        }
        if (i == 0)
        {
            for (int p = 0; p < TR.size() - 1; p++)
            {
                TR[p] = TR[p + 1];
            }
            if (TR.size() > 1) TR.pop_back();
        }

        for (int p = 0; p < 3; p++)
        {
            int s = 0;
            for (int k = 0; k < TR.size(); k++)
            {
                if (TR[k].Belongs_S(Obolochka[p]) == 1) s = 1;
            }
            if (s == 0)
            {
                Point A = Obolochka[p].Get_A();
                Point B = Obolochka[p].Get_B();
                Point All = All_Point[i];
                A.SetS(B);
                A.SetS(All);
                B.SetS(A);
                B.SetS(All);
                All.SetS(A);
                All.SetS(B);
                Triangle F;
                F.Set_P(A);
                F.Set_P(B);
                F.Set_P(All);
                TR.push_back(F);
            }
        }

        Rbr.clear();
        Int.clear();
        TR20.clear();
    }

    for (int i = 0; i < TR.size(); i++)
    {
        TD.Set_Triangle(TR[i]);
    }
    return TD;
}
