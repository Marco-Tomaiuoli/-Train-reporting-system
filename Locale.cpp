#include "Locale.h"
using namespace std; 

Locale::Locale(string name, int distance)
    :Principale(name, distance)
{
    fast_platform_gone = 0;
    fast_platform_back = 0;
}

bool Locale::is_arriving(bool gone_or_return, int priority)
{
    bool done = false;
    if (priority == 1 || priority == 2)
    {
        if(gone_or_return == 0)
        {
            if(fast_platform_gone == 0)
               fast_platform_gone = 1;
        }else if(gone_or_return == 1)
        {
            if(fast_platform_back == 0)
                fast_platform_back = 1;
        }
        done = true;    //il treno veloce o superveloce non si ferma alle stazioni e il binario veloce è sempre libero, di conseguenza lo lascio passare
    }
    else if (priority == 0)
    {
        int pos = -1;
        if (is_it_free(gone_or_return))
        {
            if (!gone_or_return)//andata
            {
                for (int i = 0; i < num_binari; i++)
                {
                    if (gone[i] == 0)
                    {
                        pos = i;
                        done = true;
                        break;
                    }
                }
            }
            else if (gone_or_return)//ritorno
            {
                for (int i = 0; i < num_binari; i++)
                {
                    if (come_back[i] == 0)
                    {
                        pos = i;
                        done = true;
                        break;
                    }
                }
            }
        }
        change_status(gone_or_return, pos);
    }
    return done;
}
