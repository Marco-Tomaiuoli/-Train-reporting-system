//Studente: Trevisiol Riccardo 1216353

#ifndef STAZIONE_H
#define STAZIONE_H
#include <string>
#include <iostream>
#include <vector>
#include <string>

class Stazione
{
public:
    std::string get_name();
    int get_distance();
    virtual bool is_arriving(bool) = 0;

protected:
    Stazione(std::string, int);
    int distance_from_first;                  //distance from first; DISTANZA DALLA PRIMA STAZIONE
    std::string name;                       //nome della stazione
};
#endif