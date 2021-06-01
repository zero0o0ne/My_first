//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <thread>
#include <numeric>
#define PI 3.141592653
#define E 0.0000001

using namespace std;

static int id = 0;
static int cid = 0;
static int lid = 0;
static int clustid = 0;
static int Bid = 0;
static int pid = 0;



class point
{
public:
    double x, y;
    int id, mark, ncl;
    friend bool operator != (point& e1, point& e2);
    point(double xx, double yy);
    point(const point& p);
    point();
    ~point();
};

class edge
{
public:
    point* begin;
    point* end;
    double length;
    edge(point* b, point* e);
    friend ostream& operator << (ostream& out, edge& e);
    friend bool operator < (edge& e1, edge& e2);
    friend bool operator > (edge& e1, edge& e2);
};

class buffer
{
public:
    vector<point*> temp;
    ~buffer();
};

class cloud
{
public:
    int N, Id;
    vector<point*> points;
    cloud(double mX, double mY, double sX, double sY, int Np);
    cloud();
    ~cloud();
};

class cluster
{
public:
    int Id;
    string method;
    vector<edge*> edges;
    vector<edge*> original_edges;
    vector<point*> points;
    cluster(vector<point*> a, vector<vector<int>>* it, int i, string type);
    cluster(string type);
    ~cluster();
};

class B_matrix
{
public:
    int id;
    vector<vector<int>> B;
    B_matrix(double r, vector<vector<double>>* D);
    ~B_matrix();
    B_matrix();
};

class D_matrix
{
public:
    vector<vector<double>> D;
    D_matrix(vector<point*>* point);
    D_matrix();
};

class find_clusters
{
public:
    int distant;
    find_clusters(double r, vector<vector<double>>* D);
    vector<cluster*> clusters;
    B_matrix B;
};

class field
{
public:
    int Np, Nc, state = 1;
    vector<cloud*> clouds;
    vector<cluster*> clusters;
    vector<point*> all_points;
    vector<edge*> all_edges;
    vector<find_clusters> Find_clusters;
    D_matrix D;
    void MATRIX();
    int BINARY(double r);
    void WAVE();
    int WAVE(int k);
    int DBSCAN(int k);
    void DBWAVE();
    void INFO_clusters();
    void INFO_marks();
    void STREE(string type);
    int TREE_histogram(int K);
    int K_means(int K);
    int EM_algorythm(int K);
    int K_cores(int K, int p);
    int FOREL(double R);
    int IERARH(int K);
    void TRIANG();
    field();
    ~field();
};

class controller
{
public:
    field* Field;
    buffer* Buffer;
    void INIT();
    void INFO();
    void GEN_CLOUD(double mX, double mY, double sX, double sY, int N);
    void HELP();
    int HISTOGRAM(int K);
    int HISTOGRAM(int K, int number);
    void BUFFER();
    int BUFFER(int number);
    void ROTATION(double xo, double yo, double fi);
    void HOMOTETIA(double xo, double yo, double fi);
    void SHIFT(double xo, double yo);
    void SET();
    ~controller();
};

class interface
{
public:
    int ID;
    controller Controller;
    vector<string> comands;
    vector<string> instructions;
    interface();
    ~interface();
    void Log_wrong_command(string command);
    void Log_wrong_means(string command);
    void Log_access_denied(string command);
    string GetCommand();
    void ReadCommand();
    int Check(string cmd);
    void Fill();
    int CONTROLLER(string Command);
};

double dist(point* first, point* second);

double ro(double t, double mt, double st);

vector<vector<point*>> coresgen(vector<vector<point*>> clust, int K, int p);

vector<vector<point*>> newclust(vector<vector<point*>> cores, vector<point*> points, int K, int p, int s);

vector<point*> coregen(vector<point*> clustr, int p);

vector<vector<point*>> init(vector<point*> points, int K);

cluster* step_of_forel(vector<point*>* temp, double R);

void make_edge(vector<vector<double>>* graph, vector<point*>* working, vector<edge*>* edges);

void new_step_of_triang(vector<edge*>* edges, vector<point*>* sorted, int i);

int edge_intersection(edge* e1, edge* e2);

int edge_intersections(vector<edge*>* edges, edge* e2);

vector<point*> find_points(vector<point*>* temp, edge* e);

double R(point* p1, point* p2, point* p3);

double cos(point* p1, point* p2, point* p3);

int highest(vector<point*>* sorted, edge* e);

int lowest(vector<point*>* sorted, edge* e);
