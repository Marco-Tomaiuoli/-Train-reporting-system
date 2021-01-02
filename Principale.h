#ifndef PRINCIPALE_H
#define PRINCIPALE_H
#include "Stazione.h"
#include <string>

class Principale : public Stazione {
public:
    Principale(std::string, int);
    bool is_arriving(bool);

protected:
    bool is_it_free(bool); //prende in input 0 se treno in andata, 1 se treno in ritorno; dice se c'è almeno un binario libero
    void change_status(bool, int);
    //prende in input 0 se treno in andata, 1 se treno in ritorno; cambia lo stato del binario
    class busy_platform {};

    std::vector<int> gone;
    std::vector<int> come_back;
    void change_gone(int);
    void change_back(int);
    constexpr static int num_binari = 2;
};
#endif