#ifndef STAZIONE_H
#define STAZIONE_H
#include <string>
#include <iostream>
#include <vector>
class Stazione
{
public:
    std::string get_name();
    int get_distance();
    Stazione(std::string, int);

protected:
    int distance_from_first;                  //distance from first; DISTANZA DALLA PRIMA STAZIONE
    std::string name;        //nome della stazione
};
#endif