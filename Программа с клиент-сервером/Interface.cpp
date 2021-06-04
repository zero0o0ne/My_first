
//Programma Semenova Nikity iz 211 gruppy
#include "Interface.h"

#pragma warning(disable : 4996)

Interface::Interface()
{
    ID = 1;
    protokol = 1;
    //scanf("null",&Comand);
}

int Interface::Command()
{
    /*vector <char> Comand;
    vector <char> C;*/
    char* Comand[30];
    //string Comand;
    string Com[10];
    string K;
    ifstream fin;
    ofstream Log;
    int i, p, k = 0, cykl = 0;
    int exit = 0;
    string l = ";";
    char file[250];

    Log.open("Log_Int.txt");
    Kontroller.Log_On();
    while (exit == 0)
    {

        printf("Esli comandy schityvautsya is fayla vvedite 0  \n");
        scanf_s("%d", &p);
        if (p == 0)
        {
            printf("Vvedite imya fayla\n");
            scanf_s("%s", file, sizeof(file));

            fin.open(file);
            if (!fin.is_open())
            {
                cout << "Fayl ne nayden!" << endl;
                return -1;
            }
            else
            {
                cout << "File otkryt!" << endl;
            }
            i = 0;
            cykl = 0;
            while (!fin.eof())
            {

                fin >> Com[i];
                time_t now = time(0);
                char* dt = ctime(&now);
                if (cykl == 0) {  Log << dt;}
                Log << Com[i] << " ";



                // cout << "Com["<<i<<"]"<<Com[i]<< endl;

                k = 0;
                cykl++;
                if (Com[i] == l)
                {
                    cykl = 0;
                    Log << endl;
                    if (Com[0] == "Help")
                    {
                        string  path = "HELP.txt";
                        ifstream H;
                        H.open(path);
                        if (!H.is_open())
                        {
                            cout << "Fayl ne nayden!" << endl;
                        }
                        char ch;
                        while (H.get(ch))
                        {
                            cout << ch;
                        }
                        H.close();
                        if (i == 1) { k = 1; }
                        else { k = 0; }

                    }

                    if (Com[0] == "Gen_Cloud")
                    {

                        double centr_x = atof(Com[1].c_str());
                        double centr_y = atof(Com[2].c_str());
                        double dispersiya_x = atof(Com[3].c_str());
                        double dispersiya_y = atof(Com[4].c_str());
                        int n = atoi(Com[5].c_str());
                        Kontroller.Gen_Cloud(centr_x, centr_y, dispersiya_x, dispersiya_y, n);
                        if (i == 6) { k = 1; }
                        else { k = 0; }
                    }

                    if (Com[0] == "Triangulation")
                    {
                        int err = Kontroller.Triangulation();
                        if (err == 0) { k = 1; }
                    }
                    if (Com[0] == "Set_Field")
                    {
                        Kontroller.Set_Field();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Get_Field")
                    {
                        Kontroller.Get_F();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Set_Cloud")
                    {
                        int n = atoi(Com[1].c_str());
                        Kontroller.Set_Cloud(n);
                        if (i == 2) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Get_Cloud")
                    {
                        Kontroller.Get_Cloud();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Regression")
                    {
                        double x = atof(Com[1].c_str());
                        double y = atof(Com[2].c_str());
                        Kontroller.Regression(x,y);
                        if (i == 3) { k = 1; }
                        else { k = 0; }
                    }

                    if (Com[0] == "Rotation")
                    {
                        double centr_x = atof(Com[1].c_str());
                        double centr_y = atoi(Com[2].c_str());
                        double a = atoi(Com[3].c_str());

                        Kontroller.Rotation(centr_x, centr_y, a);
                        if (i == 4) { k = 1; }
                        else { k = 0; }
                    }

                    if (Com[0] == "Rotation_Cloud")
                    {
                        double centr_x = atof(Com[1].c_str());
                        double centr_y = atoi(Com[2].c_str());
                        double a = atoi(Com[3].c_str());

                        Kontroller.Rotation_Cloud(centr_x, centr_y, a);
                        if (i == 4) { k = 1; }
                        else { k = 0; }
                    }

                    if (Com[0] == "Move")
                    {
                        double centr_x = atoi(Com[1].c_str());
                        double centr_y = atoi(Com[2].c_str());
                        Kontroller.Move(centr_x, centr_y);
                        if (i == 3) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Move_Cloud")
                    {
                        double centr_x = atoi(Com[1].c_str());
                        double centr_y = atoi(Com[2].c_str());
                        Kontroller.Move_Cloud(centr_x, centr_y);
                        if (i == 3) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Compr")
                    {
                        double centr_x = atoi(Com[1].c_str());
                        double centr_y = atoi(Com[2].c_str());
                        double a = atoi(Com[3].c_str());
                        Kontroller.Compr(centr_x, centr_y, a);
                        if (i == 4) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Compr_Cloud")
                    {
                        double centr_x = atoi(Com[1].c_str());
                        double centr_y = atoi(Com[2].c_str());
                        double a = atoi(Com[3].c_str());
                        Kontroller.Compr_Cloud(centr_x, centr_y, a);
                        if (i == 4) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Print")
                    {
                        if (i == 2)
                        {
                            //printf("if(Com[0]=='Print') 1");
                            Kontroller.Print_Field(Com[1]);
                            //printf("if(Com[0]=='Print') 2");
                            k = 1;
                        }
                        if (i == 3)
                        {
                            int n = atoi(Com[2].c_str());
                            //printf("n=%d",n);
                            Kontroller.Print_Cloud(Com[1], n);
                            k = 1;
                        }
                    }
                    if (Com[0] == "Print_Claster")
                    {

                        //printf("if(Com[0]=='Print') 1");
                        int n = atoi(Com[2].c_str());
                        Kontroller.Print_Claster(Com[1], n);
                        //printf("if(Com[0]=='Print') 2");
                        if (i == 3) { k = 1; }
                        else { k = 0; }

                    }

                    if (Com[0] == "Gistogram")
                    {
                        double nx = atoi(Com[1].c_str());
                        double ny = atoi(Com[2].c_str());
                        if (i == 5)
                        {
                            Kontroller.Gistogram(nx, ny, Com[3], Com[4]);
                            k = 1;
                        }
                        if (i == 6)
                        {
                            int n = atoi(Com[5].c_str());
                            Kontroller.Gistogram(nx, ny, Com[3], Com[4], n);
                            k = 1;
                        }
                    }

                    if (Com[0] == "S_Tree_Gist")
                    {
                        Kontroller.S_Tree_Gist();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Print_Tree")
                    {
                        Kontroller.Print_Tree();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Exit")
                    {
                        return 0;
                    }

                    if (Com[0] == "Field_Info")
                    {
                        Kontroller.Field_Info();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Find_Cluster_Info")
                    {
                        //int n=atoi(Com[1].c_str());
                        Kontroller.Find_Cluster_Info();
                        k = 1;
                    }
                    if (Com[0] == "Calc_Dist_Matrix")
                    {
                        Kontroller.Calc_Dist_Matrix();
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Binary")
                    {
                        double R = atof(Com[1].c_str());
                        Kontroller.Binary(R);
                        if (i == 2) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "Wave")
                    {
                        //cout<< "if(Com[0]=='Graf_Volna')"<<endl;
                        double d = atoi(Com[1].c_str());
                        if (d <= 0) {
                            cout << "Nevernyy parametr Wave" << endl;
                            return -1;
                        }
                        Kontroller.Wave(d);
                        if (i == 2) { k = 1; }
                        else { k = 0; }
                    }
                    if (Com[0] == "DBSCAN")
                    {
                        //cout<< "if(Com[0]=='Graf_Volna')"<<endl;
                    // double d=atof(Com[1].c_str());
                        int p = atoi(Com[1].c_str());
                        int n = atoi(Com[2].c_str());
                        Kontroller.DBSCAN(p, n);
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 3) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }
                    if (Com[0] == "K_means")
                    {
                        int p = atoi(Com[1].c_str());
                        Kontroller.K_means(p);
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 2) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }
                    if (Com[0] == "K_means_Ker")
                    {
                        int p = atoi(Com[1].c_str());
                        int a = atoi(Com[2].c_str());
                        Kontroller.K_means_Ker(p, a);
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 3) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }

                    if (Com[0] == "Forel")
                    {
                        double p = atof(Com[1].c_str());
                        int a = atoi(Com[2].c_str());
                        Kontroller.Forel(p, a);
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 3) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }

                    if (Com[0] == "Hierarchy")
                    {
                        int p = atoi(Com[1].c_str());
                        Kontroller.Hierarchy(p);
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 2) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }


                    if (Com[0] == "EM")
                    {
                        int p = atoi(Com[1].c_str());
                        Kontroller.EM(p);
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 2) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }
                    if (Com[0] == "S_Tree")
                    {
                        Kontroller.S_Tree();
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }
                    if (Com[0] == "Find_Factor")
                    {
                        Kontroller.Find_Factor();
                        //cout<<" if(Com[0]=='DBSCAN')"<<endl;
                        if (i == 1) { k = 1; }
                        else { k = 0; }
                        // cout<<"k="<<k<<"i="<<i<<endl;
                    }
                    //cout<<"k="<<k<<"i="<<i<<endl;
       //            if(Com[0]=="Wave_DB")
       //            {
       //             //cout<< "if(Com[0]=='Wave_DB')"<<endl;
       //             double d=atoi(Com[1].c_str());
       //             if(d<=0) {
       //             cout <<"Nevernyy parametr Wave_DB"<<endl;
       //             return -1;}
       //             Kontroller.Wave_DB(d);
       //             if(i==2){k=1;}
       //             else{k=0;}
       //            }
                    i = -1;
                    //cout<<Com[0]<<endl;
                    if (k == 0)
                    {
                        printf("Oshibka vvoda\n");
                        Log << endl << "Oshibka vvoda\n";
                        return -1;
                    }
                    Log << endl;
                }

                i++;
                //printf("%d\n",i);

                if (i > 30)
                {
                    printf("Oshibka vvoda\n");
                    Log << endl << "Oshibka vvoda\n";
                    return -1;
                }
            }
        }
        if (p !=0 )
        {
            cout << "Oshibka vvoda" << endl;
            exit = 1;
        }
        cout << "Esli vy hotite prodolgat vvedite 0 inache vvedite 1" << endl;
        scanf_s("%d", &exit);
        if (!(exit == 1 || exit == 0)) {
            cout << "Oshibka vvoda" << endl;
            exit = 1;
        }
        cout << endl;
        fin.close();
    }

}
