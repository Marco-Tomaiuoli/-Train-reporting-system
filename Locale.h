#ifndef LOCALE_H
#define LOCALE_H
#include "Stazione.h"
class Locale : public Stazione {
public:
    Locale(std::string, int);
    int change_status(int andata_o_ritorno);
    //prende in input 0 se treno in andata, 1 se treno in ritorno; ritorna 0 se è andato a buon fine, -1 se i binari sono tutti pieni
    int is_it_free(int indice); //prende in input 0 se treno in andata, 1 se treno in ritorno; ritorna 1 se c'è almeno un binario libero, 0 altrimenti

private:
    int num_binari;
    std::vector<int> gone;
    std::vector<int> come_back;
};
#endif 