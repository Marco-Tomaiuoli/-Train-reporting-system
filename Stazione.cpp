#include "Stazione.h"
using namespace std;

Stazione::Stazione(string nome, int distanza)
{
    name = nome;
    distance_from_first = distanza;
}

std::string Stazione::get_name() { return  name; }
int Stazione::get_distance() { return distance_from_first; }

/*
int main()
{
      Stazione s = Stazione("Vi", 3);
      cout<<s.get_distance()<< " " <<s.get_name();
    return 0;
}
*/