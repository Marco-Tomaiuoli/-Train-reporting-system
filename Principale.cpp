#include "Principale.h"
using namespace std;
Principale::Principale(std::string name, int distance)
    :Stazione(name, distance)
{
    num_binari = 3;
    for (int i = 0; i < num_binari; i++)
    {
        gone.push_back(0);
        come_back.push_back(0);
    }
}

int Principale::is_it_free(int indice)
{
    //restituisce 1 se c'è un binario vuoto, 0 se nessuno
    int ret = 0;
    if (indice == 0)
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (gone[i] == 0)
            {
                ret = 1;
                continue;
            }
        }
    }
    else if (indice == 1)
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (gone[i] == 1)
            {
                ret = 1;
                continue;
            }
        }
    }
    else {
        throw exception("");
    }
    return ret;
}

int Principale::change_status(int andata_o_ritorno)
{
    if (andata_o_ritorno == 0)
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (gone[i] == 0)
            {
                gone[i] = 1;
                return 0;
            }
        }
    }
    else if (andata_o_ritorno == 1)
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (come_back[i] == 0)
            {
                come_back[i] = 1;
                return 0;
            }
        }
    }
    else {
        throw invalid_argument("");
    }
    return -1;
}