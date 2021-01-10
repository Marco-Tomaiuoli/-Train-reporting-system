#include "Stazione.h"
using namespace std;

Stazione::Stazione(string nome, int distanza)
{
    name = nome;
    distance_from_first = distanza;
    isLocale = false;
}

std::string Stazione::get_name() { return  name; }
int Stazione::get_distance() { return distance_from_first; }
bool Stazione::is_local(){return isLocale;}