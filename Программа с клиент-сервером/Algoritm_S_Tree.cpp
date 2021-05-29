//211-Pushkareva-Anna-2021
#include "Algoritm_S_Tree.h"

void Algoritm_S_Tree::Start(vector <int>& STree, vector <Point>& All_Point, Dist_Matrix& D)
{
    vector <int> Tree;
    for (int i = 0; i < All_Point.size(); i++)
    {
        for (int j = 0; j < All_Point.size(); j++)
        {
            STree.push_back(0);

        }
    }
    double m = 0;
    int n = D.GetN();
    cout << "n=" << n << endl;
    for (int i = 0; i < D.GetN(); i++) {
        for (int j = 0; j < D.GetN(); j++) {

            if (m < D.Get(i, j)) {

                m = D.Get(i, j);
            }
        }
    }

    cout << "m= " << m << endl;

    //All_Point[0].SetTree(1);
    for (int r = 0; r < All_Point.size(); r++)
    {
        Tree.push_back(0);
    }
    Tree[0] = 1;
    for (int k = 1; k < All_Point.size(); k++)
    {
        double M = m;
        int I, J;
        for (int i = 0; i < All_Point.size(); i++)
        {
            if (Tree[i] == 1) {

                for (int j = 0; j < All_Point.size(); j++)
                {
                    if (M > D.Get(i, j) && Tree[j] != 1 && D.Get(i, j) != 0) {
                        //cout<<"ok"<<endl;
                        M = D.Get(i, j);
                        J = j;
                        I = i;
                    }
                }
            }
        }

        STree[I * n + J] = STree[J * n + I] = 1;
        Tree[J] = 1;
        //cout<<"k= "<<k<<endl;
    }
}

