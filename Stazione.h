//Studente: Trevisiol Riccardo 1216353
//1
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
    virtual bool is_arriving(bool, int) = 0;
    virtual bool is_it_free(bool) = 0; //prende in input 0 se treno in andata, 1 se treno in ritorno; dice se c'è almeno un binario libero


protected:
    bool isLocal();
    Stazione(std::string, int);
    int distance_from_first;                  //distance from first; DISTANZA DALLA PRIMA STAZIONE
    std::string name;                       //nome della stazione
    bool isLocale;
};
#endif