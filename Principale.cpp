#include "Principale.h"
using namespace std;
Principale::Principale(std::string name, int distance)
    :Stazione(name, distance)
{
    for (int i = 0; i < num_binari; i++)
    {
        gone.push_back(0);
        come_back.push_back(0);
    }
}

//ritorna se c'è un binario libero
bool Principale::is_it_free(bool andata_o_ritorno)
{
    bool ret = false;
    if (!andata_o_ritorno)//andata
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
    else if (andata_o_ritorno)//ritorno
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
        throw busy_platform();
    }
    if (num_binario > 1)
        throw exception("");
    if (andata_o_ritorno == 0)  //andata
    {
        change_gone(num_binario);
    }
    else if(andata_o_ritorno == 1) //ritorno
    {
        change_back(num_binario);
    }
}

void Principale::change_gone(int num_binario)
{
    if (gone[num_binario] == 1)
    {
        gone[num_binario] = 0;
    }
    else if (gone[num_binario] == 1)
        gone[num_binario] = 0;
}

void Principale::change_back(int num_binario)
{
    if (come_back[num_binario] == 1)
    {
        come_back[num_binario] = 0;
    }
    else if (come_back[num_binario] == 1)
        come_back[num_binario] = 0;
}

bool Principale::is_arriving(bool andata_o_ritorno)
{
    bool fatto = false;
    int pos = -1;
    if (is_it_free(andata_o_ritorno))
    {
        if (!andata_o_ritorno)//andata
        {
            for (int i = 0; i < num_binari; i++)
            {
                if (gone[i] == 0)
                {
                    pos = i;
                    fatto = true;
                    break;
                }
            }
        }
        else if (andata_o_ritorno)//ritorno
        {
            for (int i = 0; i < num_binari; i++)
            {
                if (come_back[i] == 0)
                {
                    pos = i;
                    fatto = true;
                    break;
                }
            }
        }
    }
    change_status(andata_o_ritorno, pos);
    return fatto;
}