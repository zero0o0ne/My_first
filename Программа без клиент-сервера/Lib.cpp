//Programma Semenova Nikity iz 211 gruppy
#include "Lib.h"

using namespace std;

field::field()
{
    Np = 0;
    Nc = 0;

}

field::~field()
{
    for (auto& el : clouds) delete el;
    for (auto& el : clusters) delete el;
    for (auto& el : all_edges) delete el;
}

point::point(double xx, double yy)
{
    x = xx;
    y = yy;
    mark = 0;
    pid++;
    id = pid;
}

point::point(const point& p)
{
    x = p.x;
    y = p.y;
    mark = p.mark;
    pid++;
    id = pid;
}

point::point()
{
    x = 0;
    y = 0;
    mark = 0;
    pid++;
    id = pid;
}

point::~point()
{
    pid--;
}

edge::edge(point* b, point* e)
{
    begin = b;
    end = e;
    length = dist(b, e);
}

ostream& operator << (ostream& out, edge& e)
{
    out << e.begin->x << "\t" << e.begin->y << endl << e.end->x << "\t" << e.end->y << endl << endl << endl;
    return out;
}

bool operator != (point& e1, point& e2)
{
    return e1.x != e2.x || e1.y != e2.y;
}

bool operator < (edge& e1, edge& e2)
{
    return e1.length < e2.length;
}

bool operator > (edge& e1, edge& e2)
{
    return e1.length > e2.length;
}

controller::~controller()
{
    delete Field;
    delete Buffer;
}

cloud::cloud(double mX, double mY, double sX, double sY, int Np)
{
    cid++;
    Id = cid;
    N = Np;
    double tempx = 0, tempy = 0, constant = 0;
    srand(time_t(NULL));
    for (int i = 0; i < 5000; i++)
    {
        int t = rand();
        if ((t % 4) > 1) constant += (double)t * (-1) / 500;
        else constant += (double)t / 500;
    }
    for (int i = 0; i < Np; i++)
    {
        for (int j = 0; j < 150; j++)
        {
            int t = rand();
            if ((t % 4) > 1) tempx += (double)t * (-1) / constant;
            else tempx += (double)t / constant;
            t = rand();
            if ((t % 4) > 1) tempy += (double)t * (-1) / constant;
            else tempy += (double)t / constant;
        }
        point* Pnt = new point(mX + (tempx / 2400) * sX, mY + (tempy / 2400) * sY);
        points.push_back(Pnt);
        tempx = 0;
        tempy = 0;
    }
}

cloud::cloud()
{
    cid++;
    Id = cid;
    N = 0;
}

cloud::~cloud()
{
    for (auto& el : points) delete el;
}

cluster::cluster(vector<point*> a, vector<vector<int>>* it, int i, string type)
{
    method = type;
    clustid++;
    Id = clustid;
    if (type == "wave")
    {
        point* temp = new point(*a[i]);
        points.push_back(temp);
        set<int> old_front = { i };
        set<int> new_front;
        vector<point*> yet = { a[i] };
        while (old_front.size() != 0)
        {
            for (auto& el : old_front) for (int t = 0; t < (*it).size(); t++) if ((*it)[el][t] == 1)
            {
                original_edges.push_back(new edge(a[el], a[t]));
                if (find(yet.begin(), yet.end(), a[t]) == yet.end())
                {
                    yet.push_back(a[t]);
                    points.push_back(new point(*a[t]));
                }
                new_front.insert(t);
                (*it)[t][el] = (*it)[el][t] = 0;
            }
            old_front = new_front;
            new_front.clear();
        }
    }
    else if (type == "dbwave")
    {
        point* temp = new point(*a[i]);
        points.push_back(temp);
        set<int> old_front = { i };
        set<int> new_front;
        vector<point*> yet = { a[i] };
        while (old_front.size() != 0)
        {
            for (auto& el : old_front) for (int t = 0; t < (*it).size(); t++) if ((*it)[el][t] == 1 && a[t]->mark > 0)
            {
                original_edges.push_back(new edge(a[el], a[t]));
                if (find(yet.begin(), yet.end(), a[t]) == yet.end())
                {
                    yet.push_back(a[t]);
                    points.push_back(new point(*a[t]));
                }
                new_front.insert(t);
                (*it)[t][el] = (*it)[el][t] = 0;
            }
            old_front = new_front;
            new_front.clear();
        }
    }
}

cluster::cluster(string type)
{
    method = type;
    clustid++;
    Id = clustid;
}

cluster::~cluster()
{
    for (auto& el : points) delete el;
    for (auto& el : edges) delete el;
    for (auto& el : original_edges) delete el;
}

find_clusters::find_clusters(double r, vector<vector<double>>* D)
{
    distant = r;
    B_matrix New(r, D);
    B = New;
}

interface::interface()
{
    id++;
    ID = id;
}

interface::~interface()
{
    id--;
}

void interface::Log_access_denied(string command)
{
    lid++;
    ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/log#" + to_string(lid) + ".txt");
    out << "Ïîïûòêà èçìåíèòü ïîëå â ñîñòîÿíèè 0: îøèáêà äîñòóïà" << endl << "Êîìàíäà: " << command;
    out.close();
}

void interface::Log_wrong_command(string command)
{
    lid++;
    ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/log#" + to_string(lid) + ".txt");
    out << "Ââåäåíà íåïðàâèëüíàÿ êîìàíäà: " << command;
    out.close();
}

void interface::Log_wrong_means(string command)
{
    lid++;
    ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/log#" + to_string(lid) + ".txt");
    out << "Ââåäåíû íåïðàâèëüíûå ïàðàìåòðû ãåíåðàöèè: " << command;
    out.close();
}

string interface::GetCommand()
{
    string Command;
    getline(cin, Command);
    return (Command);
}

void interface::ReadCommand()
{
    ifstream in("C:/Users/nikit/source/repos/ConsoleApplication1/instructions.txt");
    if (!in) return;
    string temp;
    while (!in.eof())
    {
        getline(in, temp);
        instructions.push_back(temp);
    }
    in.close();
}

void controller::HELP()
{
    ifstream in("C:/Users/nikit/source/repos/ConsoleApplication1/ConsoleApplication1/help.txt");
    string temp;
    cout << endl << "Ñïèñîê âîçìîæíûõ êîìàíä:" << endl;
    while (!in.eof())
    {
        getline (in, temp);
        cout << temp << endl;
    }
    cout << endl;
    in.close();
}

void controller::GEN_CLOUD(double mX, double mY, double sX, double sY, int N)
{
    Field->Nc++;
    Field->Np += N;
    cloud* New = new cloud(mX, mY, sX, sY, N);
    for (auto& el : New->points) Field->all_points.push_back(el);
    Field->clouds.push_back(New);
}

int interface::Check(string cmd)
{
    for (auto& el : comands)
    {
        if (cmd.find(el) == 0 && el.length() == cmd.length()) return 1;
        else if (cmd.substr(0, cmd.find(" ")).find(el.substr(0, el.find(" "))) == 0)
        {
            string str = cmd + " ", ethalon = el + " ";
            str.erase(0, str.find(" ") + 1);
            ethalon.erase(0, ethalon.find(" ") + 1);
            while (ethalon.length() != 0)
            {
                if (ethalon.substr(0, ethalon.find(" ")) == "double")
                {
                    while (str <= "9" && str >= "-" && str.find("/") == string::npos) str.erase(0, 1);
                    if (str.find(" ") != 0) return 0;
                    str.erase(0, 1);
                    ethalon.erase(0, ethalon.find(" ") + 1);
                }

                if (ethalon.substr(0, ethalon.find(" ")) == "int")
                {
                    while (str <= ":" && str >= "-" & str.find("/") == string::npos && str.substr(0, str.find(" ")).find(".") == string::npos) str.erase(0, 1);
                    if (str.find(" ") != 0) return 0;
                    str.erase(0, 1);
                    ethalon.erase(0, ethalon.find(" ") + 1);
                }
            }
            if (str.length() == 0) return 1;
        }
    }
    return 0;
}

void interface::Fill()
{
    ifstream in("C:/Users/nikit/source/repos/ConsoleApplication1/help.txt");
    string temp;
    while (!in.eof())
    {
        getline(in, temp);
        comands.push_back(temp);
    }
    in.close();
}

int interface::CONTROLLER(string Command)
{
    if (Command == "INIT") Controller.INIT();
    if (Command == "INFO") Controller.INFO();
    if (Command == "HELP") Controller.HELP();
    if (Command == "MATRIX") Controller.Field->MATRIX();
    if (Command == "WAVE") Controller.Field->WAVE();
    if (Command == "DBWAVE") Controller.Field->DBWAVE();
    if (Command == "INFO_clusters") Controller.Field->INFO_clusters();
    if (Command == "INFO_marks") Controller.Field->INFO_marks();
    if (Command == "TRIANG") Controller.Field->TRIANG();
    if (Command.find("EM_algorythm") == 0 && Command.length() > 12)
    {
        string temp = Command;
        temp.erase(0, 13);
        if (!Controller.Field->EM_algorythm(stoi(temp))) return 0;
    }
    if (Command.find("IERARH") == 0 && Command.length() > 6)
    {
        string temp = Command;
        temp.erase(0, 7);
        if (!Controller.Field->IERARH(stoi(temp))) return 0;
    }
    if (Command.find("FOREL") == 0 && Command.length() > 5)
    {
        string temp = Command;
        temp.erase(0, 6);
        if (!Controller.Field->FOREL(stod(temp))) return 0;
    }
    if (Command.find("K_cores") == 0 && Command.length() > 7)
    {
        string temp = Command;
        temp.erase(0, 8);
        int p = stoi(temp.substr(0, temp.find(" ")));
        temp.erase(0, temp.find(" ") + 1);
        if (!Controller.Field->K_cores(p, stoi(temp))) return 0;
    }
    if (Command.find("TREE_histogram") == 0 && Command.length() > 6)
    {
        string temp = Command;
        temp.erase(0, 15);
        if (!Controller.Field->TREE_histogram(stoi(temp))) return 0;
    }
    if (Command.find("STREE") == 0 && Command.length() > 6)
    {
        string temp = Command;
        temp.erase(0, 6);
        Controller.Field->STREE(temp);
    }
    if (Command.find("K_means") == 0 && Command.length() > 7) 
    {
        string temp = Command;
        temp.erase(0, 8);
        if (!Controller.Field->K_means(stoi(temp))) return 0;
    }
    if (Command.find("BINARY") == 0 && Command.length() > 6)
    {
        string temp = Command;
        temp.erase(0, 7);
        if (!Controller.Field->BINARY(stod(temp))) return 0;
    }

    if (Command.find("DBSCAN") == 0 && Command.length() > 6)
    {
        string temp = Command;
        temp.erase(0, 7);
        if (!Controller.Field->DBSCAN(stoi(temp))) return 0;
    }

    if (Command.find("WAVE") == 0 && Command.length() > 4)
    {
        string temp = Command;
        temp.erase(0, 5);
        if (!Controller.Field->WAVE(stod(temp))) return 0;
    }

    if (Command.find("HISTOGRAM") == 0 && Command.length() > 9)
    {
        string temp = Command;
        temp.erase(0, 10);
        if (temp.find(" ") == string::npos) if (!Controller.HISTOGRAM(stoi(temp))) return 0;
        if (temp.find(" ") != string::npos)
        {
            int parametr = stoi(temp.substr(0, temp.find(" ")));
            temp.erase(0, temp.find(" ") + 1);
            if (!Controller.HISTOGRAM(parametr, stoi(temp))) return 0;
        }
    }

    if (Command == "BUFFER")
    {
        if (Controller.Field->state) Controller.BUFFER();
        else return 2;
    }

    else if (Command.find("BUFFER") == 0 && Command.length() > 6)
    {
        if (Controller.Field->state)
        {
            string temp = Command;
            temp.erase(0, 7);
            if (!Controller.BUFFER(stoi(temp))) return 0;
        }
        else return 2;
    }
  
    if (Command == "SET") if (Controller.Field->state) Controller.SET();

    if (Command.find("ROTATION") != string::npos)
    {
        string temp = Command;
        temp.erase(0, 9);
        double xo = stod(temp.substr(0, temp.find(" ")));
        temp.erase(0, temp.find(" ") + 1);
        double yo = stod(temp.substr(0, temp.find(" ")));
        temp.erase(0, temp.find(" ") + 1);
        double fi = stod(temp.substr(0, temp.find(" ")));
        Controller.ROTATION(xo, yo, fi);
    }

    if (Command.find("SHIFT") != string::npos)
    {
        string temp = Command;
        temp.erase(0, 6);
        double xo = stod(temp.substr(0, temp.find(" ")));
        temp.erase(0, temp.find(" ") + 1);
        double yo = stod(temp.substr(0, temp.find(" ")));
        Controller.SHIFT(xo, yo);
    }

    if (Command.find("HOMOTETIA") != string::npos)
    {
        string temp = Command;
        temp.erase(0, 10);
        double xo = stod(temp.substr(0, temp.find(" ")));
        temp.erase(0, temp.find(" ") + 1);
        double yo = stod(temp.substr(0, temp.find(" ")));
        temp.erase(0, temp.find(" ") + 1);
        double fi = stod(temp.substr(0, temp.find(" ")));
        Controller.HOMOTETIA(xo, yo, fi);
    }

    if (Command.find("GC") == 0)
    {
        if (Controller.Field->state)
        {
            double mX, mY, sX, sY, temp;
            int N;
            Command += " ";
            Command.erase(0, 3);
            mX = stod(Command.substr(0, Command.find(" ")));
            Command.erase(0, Command.find(" ") + 1);
            mY = stod(Command.substr(0, Command.find(" ")));
            Command.erase(0, Command.find(" ") + 1);
            sX = stod(Command.substr(0, Command.find(" ")));
            Command.erase(0, Command.find(" ") + 1);
            sY = stod(Command.substr(0, Command.find(" ")));
            Command.erase(0, Command.find(" ") + 1);
            temp = stod(Command.substr(0, Command.find(" ")));
            if ((double)((int)temp) != temp) return 0;
            N = (int)temp;
            if (N < 1) return 0;
            Controller.GEN_CLOUD(mX, mY, sX, sY, N);
        }
        else return 2;
    }
    return 1;
}

void controller::INIT()
{
    Field = new field;
    Buffer = new buffer;
}

void controller::INFO()
{
    for (auto& el : (*Field).clouds)
    {
        ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/cloud#" + to_string(el->Id) + ".txt");
        out.precision(6);
        for (auto& points : el->points) out << points->x << "\t" << points->y << endl;
        out.close();
    }
       
    ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/tree#1.txt");
    for (auto& el : Field->all_edges) out << *el << endl;


    /*for (auto& el : (*Field).clusters)
    {
        ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/cluster#" + to_string(el->Id) + ".txt");
        out.precision(6);
        for (auto& points : el->points) out << points->x << "\t" << points->y << endl;
        out.close();
    }*/
}

int controller::HISTOGRAM(int K)
{
    if (K < 2) return 0;
    vector<double> x, y;
    for (auto& el : Field->all_points)
    {
        x.push_back(el->x);
        y.push_back(el->y);
    }
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    double miny = *min_element(y.begin(), y.end());
    double maxy = *max_element(y.begin(), y.end());
    vector<int> histx, histy;
    for (int i = 0; i < K; i++) histx.push_back(count_if(x.begin(), x.end(), [minx, maxx, i, K](double val) {return (val >= minx + i * (maxx - minx) / K & val < minx + (i + 1) * (maxx - minx) / K); }));
    for (int i = 0; i < K; i++) histy.push_back(count_if(y.begin(), y.end(), [miny, maxy, i, K](double val) {return (val >= miny + i * (maxy - miny) / K & val < miny + (i + 1) * (maxy - miny) / K); }));
    ofstream outx("C:/Users/nikit/source/repos/ConsoleApplication1/histogram_x.txt");
    ofstream outy("C:/Users/nikit/source/repos/ConsoleApplication1/histogram_y.txt");
    outx << "number_of_piece amount_of_points" << endl;
    outy << "number_of_piece amount_of_points" << endl;
    int q = 0;
    for (auto& el : histx) outx << ++q << " " << el << endl;
    q = 0;
    for (auto& el : histy) outy << ++q << " " << el << endl;
    outx.close();
    outy.close();
    return 1;
}

int controller::HISTOGRAM(int K, int number)
{
    if (K < 2) return 0;
    vector<double> x, y;
    vector<cloud*>::iterator it = Field->clouds.begin();
    for (int i = 1; i < number; i++)
    {
        if (it != Field->clouds.end()) it++;
        else return 0;
    }
    for (auto& el : (*it)->points)
    {
        x.push_back(el->x);
        y.push_back(el->y);
    }
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    double miny = *min_element(y.begin(), y.end());
    double maxy = *max_element(y.begin(), y.end());
    vector<int> histx, histy;
    for (int i = 0; i < K; i++) histx.push_back(count_if(x.begin(), x.end(), [minx, maxx, i, K](double val) {return (val >= minx + i * (maxx - minx) / K & val < minx + (i + 1) * (maxx - minx) / K); }));
    for (int i = 0; i < K; i++) histy.push_back(count_if(y.begin(), y.end(), [miny, maxy, i, K](double val) {return (val >= miny + i * (maxy - miny) / K & val < miny + (i + 1) * (maxy - miny) / K); }));
    ofstream outx("C:/Users/nikit/source/repos/ConsoleApplication1/histogram_x.txt");
    ofstream outy("C:/Users/nikit/source/repos/ConsoleApplication1/histogram_y.txt");
    outx << "number_of_piece amount_of_points" << endl;
    outy << "number_of_piece amount_of_points" << endl;
    int q = 0;
    for (auto& el : histx) outx << ++q << " " << el << endl;
    q = 0;
    for (auto& el : histy) outy << ++q << " " << el << endl;
    outx.close();
    outy.close();
    return 1;
}

void controller::BUFFER()
{
    for (auto& el : Field->all_points)
    {
        point* t = new point(*el);
        Buffer->temp.push_back(t);
    }
}

int controller::BUFFER(int number)
{
    vector<cloud*>::iterator it = Field->clouds.begin();
    for (int i = 1; i < number; i++)
    {
        if (it != Field->clouds.end()) it++;
        else return 0;
    }
    for (auto& el : (*it)->points)
    {
        point* t = new point(*el);
        Buffer->temp.push_back(t);
    }
    return 1;
}

void controller::ROTATION(double xo, double yo, double fi)
{
    for (auto& el : Buffer->temp)
    {
        double r = el->x, p = el->y;
        el->x = (r - xo) * cos(fi) - (p - yo) * sin(fi) + xo;
        el->y = (r - xo) * sin(fi) + (p - yo) * cos(fi) + yo;
    }
}

void controller::HOMOTETIA(double xo, double yo, double fi)
{
    for (auto& el : Buffer->temp)
    {
        el->x = (el->x - xo) * fi + xo;
        el->y = (el->y - yo) * fi + yo;
    }
}

void controller::SHIFT(double xo, double yo)
{
    for (auto& el : Buffer->temp)
    {
        el->x = el->x + xo;
        el->y = el->y + yo;
    }
}

void controller::SET()
{
    cloud* New = new cloud();
    for (auto& el : Buffer->temp)
    {
        point* NEW = new point(*el);
        New->points.push_back(NEW);
    }
    for (auto& elp : New->points) Field->all_points.push_back(elp);
    Field->clouds.push_back(New);
    for (auto& el : Buffer->temp) delete el;
    Buffer->temp.clear();
}

buffer::~buffer()
{
    for (auto& el : temp) delete el;
}

D_matrix::D_matrix(vector<point*>* point)
{
    for (int i = 0; i < point->size(); i++)
    {
        vector<double> t;
        for (int j = 0; j < point->size(); j++) t.push_back(dist((*point)[i], (*point)[j]));
        D.push_back(t);
    }
}

D_matrix::D_matrix()
{
    D = {};
}

B_matrix::B_matrix(double r, vector<vector<double>>* D)
{
    Bid++;
    id = Bid;
    for (int i = 0; i < (*D).size(); i++)
    {
        vector<int> t;
        for (int j = 0; j < (*D).size(); j++) t.push_back((*D)[i][j] < r && (*D)[i][j] != 0);
        B.push_back(t);
    }
}

B_matrix::B_matrix()
{
    Bid++;
    id = Bid;
}

B_matrix::~B_matrix()
{
    Bid--;
}

void field::MATRIX()
{
    state = 0;
    D_matrix temp(&all_points);
    D = temp;
}

int field::BINARY(double r)
{
    if (r <= 0) return 0;
    find_clusters temp(r, &(D.D));
    Find_clusters.push_back(temp);
    return 1;
}

void field::WAVE()
{
    vector<vector<int>> B = Find_clusters.rbegin()->B.B;
    int K = B.size();
    for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) if (B[i][j])
    {
        cluster* New = new cluster(all_points, &B, i, "wave");
        Find_clusters.rbegin()->clusters.push_back(New);
        clusters.push_back(New);
    }
}

int field::WAVE(int K)
{
    if (Find_clusters.size() < K) return 0;
    vector<vector<int>> B = Find_clusters[K - 1].B.B;
    int N = B.size();
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (B[i][j] == 1)
    {
        cluster* New = new cluster(all_points, &B, i, "wave");
        Find_clusters.rbegin()->clusters.push_back(New);
        clusters.push_back(New);
    }
    return 1;
}

int field::DBSCAN(int k)
{
    if (k < 1) return 0;
    vector<vector<int>> B = Find_clusters.rbegin()->B.B;
    int s = 0, K = B.size();
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < K; j++) s += B[i][j];
        if (s >= k) all_points[i]->mark = 2;
        s = 0;
    }
    for (int i = 0; i < K; i++) 
        if (all_points[i]->mark == 2) 
            for (int t = 0; t < K; t++) 
                if ((B[i][t] == 1) && (all_points[t]->mark == 0))
                    all_points[t]->mark = 1;
    return 1;
}

void field::DBWAVE()
{
    vector<vector<int>> B = Find_clusters.rbegin()->B.B;
    int K = B.size();
    for (int i = 0; i < K; i++) for (int j = 0; j < K; j++) if (B[i][j] == 1 && all_points[i]->mark == 2)
    {
        cluster* New = new cluster(all_points, &B, i, "dbwave");
        Find_clusters.rbegin()->clusters.push_back(New);
        clusters.push_back(New);
    }
}

void field::INFO_clusters()
{
    for (auto& elc : clusters)
    {
        ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/cluster#"+ to_string(elc->Id) + ".txt");
        ofstream out_edge("C:/Users/nikit/source/repos/ConsoleApplication1/cluster_with_edges#" + to_string(elc->Id) + ".txt");
        for (auto& elp : elc->points) out << elp->x << "\t" << elp->y << endl;
        for (auto& ele : elc->original_edges) out_edge << *ele << endl;
    }
}

void field::INFO_marks()
{
    ofstream core("C:/Users/nikit/source/repos/ConsoleApplication1/core.txt");
    ofstream per("C:/Users/nikit/source/repos/ConsoleApplication1/per.txt");
    ofstream dust("C:/Users/nikit/source/repos/ConsoleApplication1/dust.txt");
    for (auto& el : all_points)
    {
        if (el->mark == 2) core << el->x << "\t" << el->y << endl;
        if (el->mark == 1) per << el->x << "\t" << el->y << endl;
        if (el->mark == 0) dust << el->x << "\t" << el->y << endl;
    }
    core.close();
    per.close();
    dust.close();
}

void field::STREE(string type)
{
    if (type == "clusters")
    {
        for (auto& elc : clusters) if (elc->points.size() > 1)
        {
            for (auto& elp : elc->points) for (auto& els : elc->points) if (elp != els) elc->edges.push_back(new edge(elp, els));
            sort(elc->edges.begin(), elc->edges.end(), [](edge* e1, edge* e2) {return *e1 < *e2; });
            ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/tree#" + to_string(elc->Id) + ".txt");
            out << **(elc->edges.begin());
            map<point*, set<point*>> B;
            for (auto& elp : elc->edges)
            {
                B.insert({ elp->begin, {} });
                B.insert({ elp->end, {} });
            }
            for (vector<edge*>::iterator ele = elc->edges.begin(); ele < elc->edges.end(); ele++)
            {
                if (!B[(*ele)->end].count((*ele)->begin))
                {
                    out << **ele;
                    B[(*ele)->begin].insert((*ele)->end);
                    B[(*ele)->end].insert((*ele)->begin);
                    for (auto& pair : B[(*ele)->end])
                    {
                        B[(*ele)->begin].insert(pair);
                        B[pair].insert((*ele)->begin);
                        for (auto& shitpair : B[(*ele)->begin])
                        {
                            B[shitpair].insert(pair);
                            B[pair].insert(shitpair);
                        }
                    }
                    for (auto& pair : B[(*ele)->begin])
                    {
                        B[(*ele)->end].insert(pair);
                        B[pair].insert((*ele)->end);
                        for (auto& shitpair : B[(*ele)->end])
                        {
                            B[shitpair].insert(pair);
                            B[pair].insert(shitpair);
                        }
                    }
                }
                else *ele = nullptr;
            }
            elc->edges.erase(remove_if(elc->edges.begin(), elc->edges.end(), [](auto& element) {return element == nullptr; }), elc->edges.end());
            out.close();
        }
    }
    else if (type == "field")
    {
        for (auto& elp : all_points)
        {
            for (auto& els : all_points) if (elp != els) all_edges.push_back(new edge(elp, els));
        }
        sort(all_edges.begin(), all_edges.end(), [](edge* e1, edge* e2) {return *e1 < *e2; });
        ofstream out("C:/Users/nikit/source/repos/ConsoleApplication1/all_tree.txt");
        out << **(all_edges.begin());
        map<point*, set<point*>> B;
        for (auto& elp : all_edges)
        {
            B.insert({ elp->begin, {} });
            B.insert({ elp->end, {} });
        }
        for (vector<edge*>::iterator ele = all_edges.begin(); ele < all_edges.end(); ele++)
        {
            if (!B[(*ele)->end].count((*ele)->begin))
            {
                out << **ele;
                B[(*ele)->begin].insert((*ele)->end);
                B[(*ele)->end].insert((*ele)->begin);
                for (auto& pair : B[(*ele)->end])
                {
                    B[(*ele)->begin].insert(pair);
                    B[pair].insert((*ele)->begin);
                    for (auto& shitpair : B[(*ele)->begin])
                    {
                        B[shitpair].insert(pair);
                        B[pair].insert(shitpair);
                    }
                }
                for (auto& pair : B[(*ele)->begin])
                {
                    B[(*ele)->end].insert(pair);
                    B[pair].insert((*ele)->end);
                    for (auto& shitpair : B[(*ele)->end])
                    {
                        B[shitpair].insert(pair);
                        B[pair].insert(shitpair);
                    }
                }
            }
            else *ele = nullptr;
        }
        all_edges.erase(remove_if(all_edges.begin(), all_edges.end(), [](auto& element) {return element == nullptr; }), all_edges.end());
        out.close();
    }
}

int field::TREE_histogram(int K)
{
    if (K < 2) return 0;
    vector<double> x;
    for (auto& el : all_edges) x.push_back(el->length);
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    vector<int> histx;
    for (int i = 0; i < K; i++) histx.push_back(count_if(x.begin(), x.end(), [minx, maxx, i, K](double val) {return (val >= minx + i * (maxx - minx) / K & val < minx + (i + 1) * (maxx - minx) / K); }));
    ofstream outx("C:/Users/nikit/source/repos/ConsoleApplication1/histogram_edges.txt");
    outx << "number_of_piece amount_of_points" << endl;
    int q = 0;
    for (auto& el : histx) outx << ++q << " " << el << endl;
    outx.close();
    return 1;
}

int field::EM_algorythm(int K)
{
    if (K < 1) return 0;
    vector<vector<double>> weights;
    vector<vector<double>> weights_new;
    double differences;
    vector<cluster*> clstr;
    vector<double> temp (all_points.size(), 0.);
    vector<double> x_dis;
    vector<double> y_dis;
    vector<double> x_m (K, 0);
    vector<double> y_m (K, 0);
    vector<double> x, y;
    for (auto& el : all_points)
    {
        x.push_back(el->x);
        y.push_back(el->y);
    }
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    double miny = *min_element(y.begin(), y.end());
    double maxy = *max_element(y.begin(), y.end());
    for (int i = 0; i < K; i++)
    {
        x_dis.push_back(1);
        y_dis.push_back(1);
        weights.push_back(vector<double>(all_points.size(), 1. / K));
        weights_new.push_back(vector<double>(all_points.size(), 0));
        for (int j = i; j < all_points.size(); j += K)
        {
            x_m[i] += all_points[j]->x / (all_points.size() / K);
            y_m[i] += all_points[j]->y / (all_points.size() / K);
        }
        clstr.push_back(new cluster("em"));
    }

    differences = K;
    int s = 0;

    while (differences > (K / (double) all_points.size()))
    {
        s++;
        differences = 0;
        for (int i = 0; i < K; i++)
        {
            for (int j = 0; j < all_points.size(); j++)
            {
                weights_new[i][j] = weights[i][j] * ro(all_points[j]->x, x_m[i], x_dis[i]) * ro(all_points[j]->y, y_m[i], y_dis[i]);
                temp[j] += weights_new[i][j];
            }
        }
        for (int i = 0; i < K; i++) for (int j = 0; j < all_points.size(); j++) weights_new[i][j] /= temp[j];
        for (int j = 0; j < all_points.size(); j++) temp[j] = 0;
        for (int i = 0; i < K; i++)
        {
            x_m[i] = 0;
            y_m[i] = 0;
        }
        vector<int> number (K, 0);
        for (int j = 0; j < all_points.size(); j++)
        {
            int index = 0;
            double max = weights_new[0][j];
            for (int i = 0; i < K; i++) if (weights_new[i][j] > max)
            {
                max = weights_new[i][j];
                index = i;
            }
            x_m[index] += all_points[j]->x / all_points.size();
            y_m[index] += all_points[j]->y / all_points.size();
            number[index] ++;
        }
        for (int i = 0; i < K; i++) if (number[i] > 0)
        {
            x_m[i] *= all_points.size() / number [i];
            y_m[i] *= all_points.size() / number[i];
        }

        for (int i = 0; i < K; i++)
        {
            x_dis[i] = 0;
            y_dis[i] = 0;
            number[i] = 0;
        }
        for (int j = 0; j < all_points.size(); j++)
        {
            int index = 0;
            double max = weights_new[0][j];
            for (int i = 0; i < K; i++) if (weights_new[i][j] > max)
            {
                max = weights_new[i][j];
                index = i;
            }
            x_dis[index] += (all_points[j]->x - x_m[index]) * (all_points[j]->x - x_m[index]) / all_points.size();
            y_dis[index] += (all_points[j]->y - y_m[index]) * (all_points[j]->y - y_m[index]) / all_points.size();
            number[index] ++;
        }
        for (int i = 0; i < K; i++) if (number[i] > 0)
        {
            x_dis[i] *= all_points.size() / number[i];
            y_dis[i] *= all_points.size() / number[i];
        }

        for (int i = 0; i < K; i++) for (int j = 0; j < all_points.size(); j++) differences += (weights_new[i][j] - weights[i][j]) * (weights_new[i][j] - weights[i][j]);
        ofstream first("C:/Users/nikit/source/repos/ConsoleApplication1/EM/cluster_1_step#" + to_string(s) + ".txt");
        ofstream second("C:/Users/nikit/source/repos/ConsoleApplication1/EM/cluster_2_step#" + to_string(s) + ".txt");
        ofstream third("C:/Users/nikit/source/repos/ConsoleApplication1/EM/cluster_3_step#" + to_string(s) + ".txt");
        ofstream fourth("C:/Users/nikit/source/repos/ConsoleApplication1/EM/cluster_4_step#" + to_string(s) + ".txt");
        for (int j = 0; j < all_points.size(); j++)
        {
            int index = 0;
            double max = weights[0][j];
            for (int i = 0; i < K; i++) if (weights[i][j] > max)
            {
                max = weights[i][j];
                index = i;
            }
            switch (index)
            {
            case 0:
                first << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            case 1:
                second << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            case 2:
                third << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            case 3:
                fourth << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            default:
                break;
            }
        }
        cout << differences << endl;
        weights = weights_new;
    }
    for (int j = 0; j < all_points.size(); j++)
    {
        int index = 0;
        double max = weights[0][j];
        for (int i = 0; i < K; i++) if (weights[i][j] > max)
        {
            max = weights[i][j];
            index = i;
        }
        clstr[index]->points.push_back(new point(*all_points[j]));
        clstr[index]->original_edges.push_back(new edge(all_points[j], new point(x_m[index], y_m[index])));
    }
    for (int i = 0; i < K; i++) clusters.push_back(clstr[i]);
}

int field::K_means(int K)
{
    if (K < 1) return 0;
    vector<cluster*> clustrs;
    vector<point*> means_new;
    vector<point*> means_old;
    vector<int> number;
    vector<double> x, y;
    for (auto& el : all_points)
    {
        x.push_back(el->x);
        y.push_back(el->y);
    }
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    double miny = *min_element(y.begin(), y.end());
    double maxy = *max_element(y.begin(), y.end());
    double distnt = sqrt ((maxx  - minx) * (maxx - minx) + (maxy - miny) * (maxy - miny));
    for (int i = 1; i <= K; i++)
    {
        means_new.push_back(new point((maxx + minx) / 2 + distnt * cos(2 * PI * i / K) / 4, (maxy + miny) / 2 + distnt * sin(2 * PI * i / K) / 4));
        means_old.push_back(new point(0, 0));
        number.push_back(0);
        clustrs.push_back(new cluster("k_means"));
    }
    bool temp = 1;
    int s = 0;
    while (temp)
    {
        s++;
        temp = 0;
        for (int i = 0; i < K; i++)
        {
            means_old[i]->x = means_new[i]->x;
            means_old[i]->y = means_new[i]->y;
            means_new[i]->x = 0;
            means_new[i]->y = 0;
            number[i] = 0;
        }
        for (auto& el : all_points)
        {
            double dis = dist(el, means_old[0]);
            int index = 0;
            for (int i = 0; i < K; i++) if (!(dist(el, means_old[i]) > dis))
            {
                dis = dist(el, means_old[i]);
                index = i;
            }
            if (el->ncl != index)
            {
                el->ncl = index;
                temp = 1;
            }
            means_new[index]->x += el->x;
            means_new[index]->y += el->y;
            number[index] ++;
        }

        ofstream first("C:/Users/nikit/source/repos/ConsoleApplication1/K_means/cluster_1_step#" + to_string(s) + ".txt");
        ofstream second("C:/Users/nikit/source/repos/ConsoleApplication1/K_means/cluster_2_step#" + to_string(s) + ".txt");
        ofstream third("C:/Users/nikit/source/repos/ConsoleApplication1/K_means/cluster_3_step#" + to_string(s) + ".txt");
        ofstream fourth("C:/Users/nikit/source/repos/ConsoleApplication1/K_means/cluster_4_step#" + to_string(s) + ".txt");
        for (int j = 0; j < all_points.size(); j++)
        {
            switch (all_points[j]->ncl)
            {
            case 0:
                first << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            case 1:
                second << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            case 2:
                third << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            case 3:
                fourth << all_points[j]->x << "\t" << all_points[j]->y << endl;
                break;
            default:
                break;
            }
        }

        for (int i = 0; i < K; i++)
        {
            means_new[i]->x /= number[i];
            means_new[i]->y /= number[i];
        }
    }
    for (auto& el : all_points)
    {
        point* temp = new point(*el);
        clustrs[el->ncl]->points.push_back(temp);
        clustrs[el->ncl]->original_edges.push_back(new edge (means_old[el->ncl], temp));
    }
    for (auto& el : clustrs) clusters.push_back(el);
    return 1;
}

int field::K_cores(int K, int p)
{
    if (K < 1 || p<1) return 0;
    vector<vector<point*>> clust;
    vector<vector<point*>> cores;
    vector<vector<point*>> clust_new (K);
    clust_new = init(all_points, K);
    cores = coresgen(clust_new, K, p);
    int s = 0;
    while (clust != clust_new)
    {
        s++;
        clust = clust_new;
        clust_new = newclust(cores, all_points, K, p, s);
        cores = coresgen(clust_new, K, p);
    }
    for (int j = 0; j < K; j++)
    {
        cluster* temp = new cluster("k_cores");
        for (auto& elp : clust[j])
        {
            temp->points.push_back(new point(*elp));
            vector<edge*> temporary;
            for (int i = 0; i < p; i++) temporary.push_back(new edge(elp, cores[j][i]));
            edge* best = temporary[0];
            for (int i = 0; i < p; i++) if (best->length > temporary[i]->length) best = temporary[i];
            temp->original_edges.push_back(best);
        }
        clusters.push_back(temp);
    }
}

int field::FOREL(double R)
{
    if (R <= 0) return 0;
    vector<point*> temp = all_points;
    while (temp.size() > 0) clusters.push_back(step_of_forel(&temp, R));
    return 1;
}

int field::IERARH(int K)
{
    if (K < 0) return 0;
    vector<vector<double>> graph(all_points.size());
    vector<point*> working = all_points;
    vector<edge*> edges;
    for (int i = 0; i < all_points.size(); i++) graph[i].resize(all_points.size());
    for (int i = 0; i < all_points.size(); i++) for (int j = i; j < all_points.size(); j++)
    {
        if (i != j) graph[i][j] = graph[j][i] = dist(all_points[i], all_points[j]);
        else graph[i][j] = 10000;
    }
    for (int i = 0; i < all_points.size() - K; i++)
    {
        make_edge(&graph, &working, &edges);
        ofstream p("C:/Users/nikit/source/repos/ConsoleApplication1/points/step#" + to_string(i) + ".txt");
        ofstream e("C:/Users/nikit/source/repos/ConsoleApplication1/edges/step#" + to_string(i) + ".txt");
        for (auto& points : working) p << points->x << "\t" << points->y << endl;
        p.close();
        for (auto& edge : edges) e << *edge;
        e.close();
    }
    return 1;
}

void field::TRIANG()
{
    vector<edge*> edges;
    vector<point*> sorted = all_points;
    point* t;
    for (int i = 0; i < sorted.size(); i++) for (int j = i; j < sorted.size(); j++) if (sorted[i]->x > sorted[j]->x)
    {
        t = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = t;
    }
    edges.push_back(new edge(sorted[0], sorted[1]));
    edges.push_back(new edge(sorted[1], sorted[2]));
    edges.push_back(new edge(sorted[0], sorted[2]));
    for (int i = 3; i < sorted.size(); i++) 
    {
        new_step_of_triang(&edges, &sorted, i);
        ofstream p("C:/Users/nikit/source/repos/ConsoleApplication1/points/step#" + to_string(i - 3) + ".txt");
        ofstream e("C:/Users/nikit/source/repos/ConsoleApplication1/edges/step#" + to_string(i - 3) + ".txt");
        for (auto& points : sorted) p << points->x << "\t" << points->y << endl;
        p.close();
        for (auto& edge : edges) e << *edge;
        e.close();
    }
}

void make_edge(vector<vector<double>>* graph, vector<point*>* working, vector<edge*>* edges)
{
    vector<double> minimals;
    double min_i, min_j;
    for (int i = 0; i < (*graph).size(); i++) minimals.push_back(*min_element((*graph)[i].begin(), (*graph)[i].end()));
    double min = *min_element(minimals.begin(), minimals.end());
    for (int i = 0; i < (*graph).size(); i++) if (find((*graph)[i].begin(), (*graph)[i].end(), min) != (*graph)[i].end())
    {
        min_i = i;
        min_j = distance((*graph)[i].begin(), find((*graph)[i].begin(), (*graph)[i].end(), min));
    }

    (*working).push_back(new point((*working)[min_i]->x * 0.5 + (*working)[min_j]->x * 0.5, (*working)[min_i]->y * 0.5 + (*working)[min_j]->y * 0.5));
    for (int i = 0; i < (*graph).size(); i++)
    {
        if (*min_element((*graph)[i].begin(), (*graph)[i].end()) < 1000) (*graph)[i].push_back(dist((*working)[(*working).size() - 1], (*working)[i]));
        else (*graph)[i].push_back(10000000);
        if (i == min_j || i == min_i) for (int j = 0; j < (*graph)[i].size(); j++) (*graph)[i][j] = 10000000;
        else (*graph)[i][min_i] = (*graph)[i][min_j] = 10000000;
    }
    vector<double> very_temp;
    for (int i = 0; i < (*working).size(); i++) very_temp.push_back(dist((*working)[(*working).size() - 1], (*working)[i]));
    very_temp[very_temp.size() - 1] = 10000;
    int t = 0;
    while (*min_element((*graph)[t].begin(), (*graph)[t].end()) > 100000) t++;
    for (int i = 0; i < very_temp.size(); i++) if ((*graph)[t][i] > 100000) very_temp[i] = (*graph)[t][i];
    (*graph).push_back(very_temp);
    (*edges).push_back(new edge((*working)[min_j], (*working)[min_i]));
}

vector<vector<point*>> coresgen(vector<vector<point*>> clust, int K, int p)
{
    vector<vector<point*>> temp;
    for (int i = 0; i < K; i++)
    {
        vector<point*> i_core;
        if(clust[i].size() > 1) i_core = coregen(clust[i], p);
        temp.push_back(i_core);
    }
    return temp;
}

vector<vector<point*>> newclust(vector<vector<point*>> cores, vector<point*> points, int K, int p, int s)
{
    vector<vector<point*>> temp (K);
    ofstream first("C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_1_step#" + to_string(s) + ".txt");
    ofstream second("C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_2_step#" + to_string(s) + ".txt");
    ofstream third("C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_3_step#" + to_string(s) + ".txt");
    ofstream fourth("C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cluster_4_step#" + to_string(s) + ".txt");
    ofstream cor("C:/Users/nikit/source/repos/ConsoleApplication1/K_cores/cores_step#" + to_string(s) + ".txt");
    for (auto& el : points)
    {
        {
            int index = 0;
            while (cores[index].size() == 0) index++;
            double min = dist(el, cores[index][0]);
            for (int i = index; i < K; i++) for (int j = 0; j < p; j++)
            {
                if (dist(el, cores[i][j]) < min)
                {
                    min = dist(el, cores[i][j]);
                    index = i;
                }
            }
            temp[index].push_back(el);

            
            switch (index)
            {
            case 0:
                first << el->x << "\t" << el->y << endl;
                break;
            case 1:
                second << el->x << "\t" << el->y << endl;
                break;
            case 2:
                third << el->x << "\t" << el->y << endl;
                break;
            case 3:
                fourth << el->x << "\t" << el->y << endl;
                break;
            default:
                break;
            }
        }
    }
    for (auto& el : cores) for (auto& c : el) cor << c->x << "\t" << c->y << endl;
    return temp;
}

vector<point*> coregen(vector<point*> clustr, int p)
{
    vector<point*> means_new;
    vector<point*> means_old;
    vector<int> number;
    vector<double> x, y;
    for (auto& el : clustr)
    {
        x.push_back(el->x);
        y.push_back(el->y);
    }
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    double miny = *min_element(y.begin(), y.end());
    double maxy = *max_element(y.begin(), y.end());
    double distnt = sqrt((maxx - minx) * (maxx - minx) + (maxy - miny) * (maxy - miny));
    for (int i = 1; i <= p; i++)
    {
        means_new.push_back(new point((maxx + minx) / 2 + distnt * cos(2 * PI * i / p) / 4, (maxy + miny) / 2 + distnt * sin(2 * PI * i / p) / 4));
        means_old.push_back(new point(0, 0));
        number.push_back(0);
    }
    bool temp = 1;
    while (temp)
    {
        temp = 0;
        for (int i = 0; i < p; i++)
        {
            means_old[i]->x = means_new[i]->x;
            means_old[i]->y = means_new[i]->y;
            means_new[i]->x = 0;
            means_new[i]->y = 0;
            number[i] = 0;
        }
        for (auto& el : clustr)
        {
            double dis = dist(el, means_old[0]);
            int index = 0;
            for (int i = 0; i < p; i++) if (!(dist(el, means_old[i]) > dis))
            {
                dis = dist(el, means_old[i]);
                index = i;
            }
            if (el->ncl != index)
            {
                el->ncl = index;
                temp = 1;
            }
            means_new[index]->x += el->x;
            means_new[index]->y += el->y;
            number[index] ++;
        }
        for (int i = 0; i < p; i++)
        {
            means_new[i]->x /= number[i];
            means_new[i]->y /= number[i];
        }
    }
    return means_new;
}

vector<vector<point*>> init(vector<point*> points, int K)
{
    vector<point*> means_new;
    vector<point*> means_old;
    vector<int> number;
    vector<double> x, y;
    for (auto& el : points)
    {
        x.push_back(el->x);
        y.push_back(el->y);
    }
    double minx = *min_element(x.begin(), x.end());
    double maxx = *max_element(x.begin(), x.end());
    double miny = *min_element(y.begin(), y.end());
    double maxy = *max_element(y.begin(), y.end());
    double distnt = sqrt((maxx - minx) * (maxx - minx) + (maxy - miny) * (maxy - miny));
    for (int i = 1; i <= K; i++)
    {
        means_new.push_back(new point((maxx + minx) / 2  + distnt * cos(2 * PI * i/ K) / 4, (maxy + miny) / 2 + distnt * sin(2 * PI * i / K) / 4));
        means_old.push_back(new point(0, 0));
        number.push_back(0);
    }
    bool temp = 1;
    while (temp)
    {
        temp = 0;
        for (int i = 0; i < K; i++)
        {
            means_old[i]->x = means_new[i]->x;
            means_old[i]->y = means_new[i]->y;
            means_new[i]->x = 0;
            means_new[i]->y = 0;
            number[i] = 0;
        }
        for (auto& el : points)
        {
            double dis = dist(el, means_old[0]);
            int index = 0;
            for (int i = 0; i < K; i++) if (!(dist(el, means_old[i]) > dis))
            {
                dis = dist(el, means_old[i]);
                index = i;
            }
            if (el->ncl != index)
            {
                el->ncl = index;
                temp = 1;
            }
            means_new[index]->x += el->x;
            means_new[index]->y += el->y;
            number[index] ++;
        }
        for (int i = 0; i < K; i++)
        {
            means_new[i]->x /= number[i];
            means_new[i]->y /= number[i];
        }
    }
    vector<vector<point*>> tem(K);
    for (auto& el : points) tem[el->ncl].push_back(el);
    return tem;
}

double dist(point* first, point* second)
{
    return sqrt((first->x - second->x) * (first->x - second->x) + (first->y - second->y) * (first->y - second->y));
}

double ro(double t, double mt, double st)
{
    if (st == 0) return 0;
    return (1/(sqrt(2*PI * st))) * exp ((t - mt) * (t - mt) / (-2 * st));
}

cluster* step_of_forel(vector<point*>* temp, double R)
{
    int t = 0;
    vector<point*> working;
    if (temp->size() > 1) t = rand() % temp->size();
    point* new_middle = new point(*(*temp)[t]);
    point* middle = new point(*new_middle);
    middle->x-=1;
    while (*middle != *new_middle)
    {
        working.clear();
        *middle = *new_middle;
        for (auto& el : *temp) if (dist(middle, el) <= R) working.push_back(el);
        new_middle->y = new_middle->x = 0;
        for (int i = 0; i < working.size(); i++)
        {
            new_middle->y += working[i]->y / working.size();
            new_middle->x += working[i]->x / working.size();
        }
    }
    cluster* temporary = new cluster("forel");
    for (auto& el : working)
    {
        temporary->points.push_back(new point(*el));
        temporary->original_edges.push_back(new edge(el, middle));
        temp->erase(std::remove(temp->begin(), temp->end(), el), temp->end());
    }
    return temporary;
}

void new_step_of_triang(vector<edge*>* edges, vector<point*>* sorted, int i)
{
    vector<point*> sort;
    for (int j = 0; j < i; j++) sort.push_back((*sorted)[j]);
    double min = -100000;
    double max = 100000;
    edge* lower = new edge((*sorted)[i], (*sorted)[i]);
    edge* higher = new edge((*sorted)[i], (*sorted)[i]);
    for (int j = 0; j < i; j++)
    {
        edge* temp = new edge((*sorted)[i], (*sorted)[j]);
        if (edge_intersections(edges, temp))
        {
            if (lowest(&sort, temp))
            {
                delete lower;
                lower = temp;
            }

            else if (highest(&sort, temp))
            {
                delete higher;
                higher = temp;
            }
            else delete temp;
        }
    }
        edges->push_back(lower);
        edges->push_back(higher);

        edge* working = lower;
        while (working->end->id != higher->end->id)
        {
            int check = 0;
            double Rmax = 0;
            double Rmin = 1000000000;
            point* next = working->end;
            vector<point*> stack = find_points(&sort, working);
            for (auto& p : stack)
            {
                if (R(working->begin, p, working->end) > Rmax && cos(working->begin, p, working->end) <= 0)
                {
                    check = 1;
                    next = p;
                    Rmax = R(working->begin, p, working->end);
                }

                else if (R(working->begin, p, working->end) < Rmin && cos(working->begin, p, working->end) >= 0 && check == 0)
                {
                    next = p;
                    Rmin = R(working->begin, p, working->end);
                }
            }

            working = new edge((*sorted)[i], next);
            for (auto& e : *edges) if (edge_intersection(e, working)) e->begin = e->end;
            edges->push_back(working);
        }
}

int edge_intersection(edge* e1, edge* e2)
{
    double k = (e1->begin->y - e1->end->y) / (e1->begin->x - e1->end->x);
    double k1 = (e2->begin->y - e2->end->y) / (e2->begin->x - e2->end->x);
    if (((e2->begin->y - k * (e2->begin->x - e1->begin->x) - e1->begin->y) * (e2->end->y - k * (e2->end->x - e1->begin->x) - e1->begin->y) < -1*E) && ((e1->begin->y - k1 * (e1->begin->x - e2->begin->x) - e2->begin->y) * (e1->end->y - k1 * (e1->end->x - e2->begin->x) - e2->begin->y) < -1*E)) return 1;
    else return 0;
}

int edge_intersections(vector<edge*>* edges, edge* e2)
{
    int check = 1;
    for (auto& e : *edges) if (edge_intersection(e, e2)) check = 0;
    return check;
}

vector<point*> find_points(vector<point*>* temp, edge* e)
{
    vector<point*> working;
    double k = (e->begin->y - e->end->y) / (e->begin->x - e->end->x);
    for (auto& p : *temp) if (p->y - k * (p->x - e->begin->x) - e->begin->y > 0) working.push_back(p);
    return working;
}

double R(point* p1, point* p2, point* p3)
{
    double ma = (p1->y - p2->y) / (p1->x - p2->x);
    double mb = (p3->y - p2->y) / (p3->x - p2->x);
    double x = (ma * mb * (p1->y - p3->y) + mb * (p1->x + p2->x) - ma * (p2->x + p3->x)) / (2 * (mb - ma));
    double y = (-1 / ma) * (x - (p1->x + p2->x) / 2) + (p1->y + p2->y) / 2;
    return (sqrt((x - p1->x) * (x - p1->x) + (y - p1->y) * (y - p1->y)));
}

double cos(point* p1, point* p2, point* p3)
{
    return ((p1->x - p2->x) * (p3->x - p2->x) + (p3->y - p2->y) * (p1->y - p2->y)) / (dist(p1, p2) * dist(p3, p2));
}

int highest(vector<point*>* sorted, edge* e)
{
    int check = 1;
    double k = (e->begin->y - e->end->y) / (e->begin->x - e->end->x);
    for (auto& p : *sorted) 
        if ((p->y - k * (p->x - e->begin->x) - e->begin->y) > 0 && e->end->id != p->id) check = 0;
    return check;
}

int lowest(vector<point*>* sorted, edge* e)
{
    int check = 1;
    double k = (e->begin->y - e->end->y) / (e->begin->x - e->end->x);
    for (auto& p : *sorted) 
        if ((p->y - k * (p->x - e->begin->x) - e->begin->y) < 0 && e->end->id != p->id) check = 0;
    return check;
}
