
//Programma Semenova Nikity iz 211 gruppy
#include "Algoritm_Hierarchy.h"

double Algoritm_Hierarchy::d(H_Point& A, H_Point& B)
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

Find_Claster Algoritm_Hierarchy::Start(int n, vector <Point>& All_Point)
{

    vector <H_Point> M;
    vector <H_Point> S;
    vector <TreeNode_H> Tree;
    vector <int> Nomer;


    int I, J;
    for (int i = 0; i < All_Point.size(); i++)
    {
        H_Point H;
        H.SetX(All_Point[i].GetX());
        H.SetY(All_Point[i].GetY());
        M.push_back(H);
    }

    for (int k = 0; k < All_Point.size() - 1; k++)
    {

        double Min;
        for (int i = 0; i < M.size(); i++)
        {
            if (d(M[0], M[i]) > E) { Min = d(M[0], M[i]); }
        }

        I = J = 0;
        //cout<<"M.size()="<<M.size()<<endl;
        for (int i = 0; i < M.size(); i++)
        {
            for (int j = i; j < M.size(); j++)
            {
                if (d(M[i], M[j]) <= Min && d(M[i], M[j]) != 0)
                {
                    Min = d(M[i], M[j]);
                    I = i; J = j;

                }
            }
        }
        double x = (M[I].GetV() * M[I].GetX() + M[J].GetX() * M[J].GetV()) / (M[J].GetV() + M[I].GetV());
        double y = (M[I].GetV() * M[I].GetY() + M[J].GetY() * M[J].GetV()) / (M[J].GetV() + M[I].GetV());
        H_Point Centr(x, y);
        Centr.SetV(M[J].GetV() + M[I].GetV());
        Centr.SetTree(1);
        if (M[I].GetTree() == 0)
        {
            M[I].SetTree(1);
            M[I].SetA(Tree.size());
            TreeNode_H Right;
            Right.SetPoint(M[I]);
            Right.SetL(Tree.size());
            Right.SetR(Tree.size());
            Right.SetH(0);
            Tree.push_back(Right);

        }

        if (M[J].GetTree() == 0)
        {
            M[J].SetTree(1);
            TreeNode_H Right;
            M[J].SetA(Tree.size());
            Right.SetPoint(M[J]);
            Right.SetL(Tree.size());
            Right.SetR(Tree.size());
            Right.SetH(0);
            Tree.push_back(Right);
        }


        TreeNode_H Right;
        Right.SetPoint(Centr);
        Right.SetL(M[J].GetA());
        Right.SetR(M[I].GetA());
        Right.SetH(Min);
        Tree.push_back(Right);
        Centr.SetA(Tree.size() - 1);

        S.clear();
        //cout<<"I="<<I<<" J="<<J<<endl;
        for (int i = 0; i < M.size(); i++)
        {
            if (i != I && i != J)
            {
                S.push_back(M[i]);
                // cout<<"i="<<i<<endl;
            }
        }
        //cout<<"S.size()="<<S.size()<<endl<<endl;
        S.push_back(Centr);
        M.clear();
        ofstream Cen;
        string centr = "C:\\C_A_Result\\Algoritms\\";
        centr += std::to_string(k);
        centr += "Hierarchy_Centr.txt";
        Cen.open(centr);

        for (int i = 0; i < S.size(); i++)
        {

            M.push_back(S[i]);
            Cen << S[i].GetX() << " " << S[i].GetY() << endl;
        }
        Cen.close();

        ofstream out, com;
        string Dendr = "C:\\C_A_Result\\";
        Dendr += std::to_string(k);
        Dendr += "Hierarchy.txt";
        string Dendr_GP = "C:\\C_A_Result\\";
        Dendr_GP += std::to_string(k);
        Dendr_GP += "Hierarchy_GP.plt";
        out.open(Dendr);
        com.open(Dendr_GP);

        for (int j = 0; j < Tree.size(); j++)
        {
            out << Tree[Tree[j].GetL()].GetPoint().GetX() << " " << Tree[Tree[j].GetL()].GetPoint().GetY() << endl;
            out << Tree[j].GetPoint().GetX() << " " << Tree[j].GetPoint().GetY() << endl;
            out << Tree[Tree[j].GetR()].GetPoint().GetX() << " " << Tree[Tree[j].GetR()].GetPoint().GetY() << endl << endl << endl;

        }
        com << "set xrange[-20:20] " << endl;
        com << "set yrange[-20:20] " << endl;
        com << "plot '" << Dendr << "' using 1:2 w l, '" << centr << "' using 1:2 w p  " << endl;

        com.close();
        out.close();
    }

    string Animate = "C:\\C_A_Result\\Hierarchy_animate";
    Animate += ".plt";
    ofstream Anim;
    Anim.open(Animate);
    Anim << "set xrange[-20:20] " << endl;
    Anim << "set yrange[-20:20] " << endl;
    Anim << "set term gif animate optimize delay 10 background \"#ffeedf\" font \" Times-Roman,10 \" " << endl;
    Anim << "set output \"Hierarchy_Animate.gif\" " << endl;
    Anim << "set size square" << endl;
    Anim << "set nokey" << endl;
    Anim << "set title \"Hierarchy-algoritm\" " << endl;
    Anim << "do for[i=0:" << All_Point.size() - 1 << "]{" << endl;
    Anim << "plot ''.i.'Hierarchy.txt' using 1:2 w l, ''.i.'Hierarchy_Centr.txt' using 1:2 w p  " << endl;

    Anim << "}" << endl;

    string String = "Hierarchy";
    Find_Claster Q;
    Q.SetS(String);
    Q.SetTree(Tree);
    return Q;

}



