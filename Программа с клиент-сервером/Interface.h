
//Programma Semenova Nikity iz 211 gruppy
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;
#define CLOUD 20
#define E 0.01
#define pi 3.1415926535
#include "Kontroller.h"

class Interface
{
private:
    int ID;
    int protokol;
    //char* file;
    Kontroller Kontroller;
public:
    Interface();
    void Help();
    int Command();
};
