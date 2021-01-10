#include "Principale.h"
using namespace std;

Principale::Principale(std::string name)    //costruttore per la Prima stazione
    :Stazione(name, 0)
{
    isLocale = false;
    for (int i = 0; i < num_binari; i++)
    {
        gone[i] = 0;
        come_back[i] = 0;
    }
}

Principale::Principale(std::string name, int distance)
    :Stazione(name, distance)
{
    isLocale = false;
    for (int i = 0; i < num_binari; i++)
    {
        gone[i] = 0;
        come_back[i] = 0;
    }
}

//ritorna se c'è un binario libero
bool Principale::is_it_free(bool andata_o_ritorno)
{
    bool ret = false;
    if (andata_o_ritorno)//andata
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (gone[i] == 0)
            {
                ret = true;
                break;
            }
        }
    }
    else if (!andata_o_ritorno)//ritorno
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (come_back[i] == 0)
            {
                ret = true;
                break;
            }
        }
    }
    return ret;
}

//libera il binario indicato 
void Principale::change_status(bool andata_o_ritorno, int num_binario)
{
    if (num_binario == -1)
    {
        return;
    }
    if (andata_o_ritorno)  //andata
    {
        change_gone(num_binario);
    }
    else if(!andata_o_ritorno) //ritorno
    {
        change_back(num_binario);
    }
}

void Principale::change_gone(int num_binario)
{
    if (gone[num_binario] == 0)
    {
        gone[num_binario] = 1;
    }
    else if (gone[num_binario] == 1)
        gone[num_binario] = 0;
}

void Principale::change_back(int num_binario)
{
    if (come_back[num_binario] == 0)
    {
        come_back[num_binario] = 1;
    }
    else if (come_back[num_binario] == 1)
        come_back[num_binario] = 0;
}

int Principale::is_arriving(bool andata_o_ritorno, int nullo)
{
    int pos = -1;
    if (is_it_free(andata_o_ritorno))
    {
        if (andata_o_ritorno)//andata
        {
            for (int i = 0; i < num_binari; i++)
            {
                if (gone[i] == 0)
                {
                    pos = i;
                    break;
                }
            }
        }
        else if (!andata_o_ritorno)//ritorno
        {
            for (int i = 0; i < num_binari; i++)
            {
                if (come_back[i] == 0)
                {
                    pos = i;
                    break;
                }
            }
        }
    }
    change_status(andata_o_ritorno, pos);
    return pos;
}

bool Principale::present_train(bool andata_o_ritorno)
{
    bool ret = false;
    if (andata_o_ritorno)//andata
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (gone[i] == 1)
            {
                ret = true;
                break;
            }
        }
    }
    else if (!andata_o_ritorno)//ritorno
    {
        for (int i = 0; i < num_binari; i++)
        {
            if (come_back[i] == 1)
            {
                ret = true;
                break;
            }
        }
    }
    return ret;
}