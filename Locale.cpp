#include "Locale.h"
using namespace std; 

Locale::Locale(string name, int distance)
    :Principale(name, distance)
{
    isLocale = true;
    fast_platform_gone = 0;
    fast_platform_back = 0;
}

int Locale::is_arriving(bool gone_or_return, int priority)
{
    int rit = -1;
    if (priority == 1 || priority == 2)
    {
        if(gone_or_return)//andata 
        {
            if (fast_platform_gone == 0)
            {
                fast_platform_gone = 1;
                rit = 2;
            }
        }else if(!gone_or_return)//ritorno
        {
            if (fast_platform_back == 0)
            {
                fast_platform_back = 1;
                rit = 2;
            }
        }
    }
    else if (priority == 0)
    {
        if (is_it_free(gone_or_return))
        {
            if (gone_or_return)//andata
            {
                for (int i = 0; i < num_binari; i++)
                {
                    if (gone[i] == 0)
                    {
                        rit = i;
                        break;
                    }
                }
            }
            else if (!gone_or_return)//ritorno
            {
                for (int i = 0; i < num_binari; i++)
                {
                    if (come_back[i] == 0)
                    {
                        rit = i;
                        break;
                    }
                }
            }
        }
        change_status(gone_or_return, rit);
    }
    return rit;
}