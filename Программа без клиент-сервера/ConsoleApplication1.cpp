#include "Lib.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "English");
    interface MAIN;
    string command;
    MAIN.Fill();
    /*while (!MAIN.Check(command))
    {
        MAIN.Log_wrong_command(command);
        command = MAIN.GetCommand();
    }
    while (command != "EXIT")
    {
        if (!MAIN.CONTROLLER(command)) MAIN.Log_wrong_means(command);
        command = MAIN.GetCommand();
        while (!MAIN.Check(command))
        {
            MAIN.Log_wrong_command(command);
            command = MAIN.GetCommand();
        }
    }*/
    int start = clock();
    MAIN.ReadCommand();
    for (auto& el : MAIN.instructions)
    {
        if (!MAIN.Check(el))
        {
            MAIN.Log_wrong_command(el);
            continue;
        }
        else if (el == "EXIT")
        {
            int end = clock();
            cout << end - start;
            return 0;
        }
        int code = MAIN.CONTROLLER(el);
        if (code == 0) MAIN.Log_wrong_means(el);
        if (code == 2) MAIN.Log_access_denied(el);
    }
    int end = clock();
    cout << end - start;
    return 0;
}



