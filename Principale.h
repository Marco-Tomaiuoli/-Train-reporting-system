//Studente: Trevisiol Riccardo 1216353
#ifndef PRINCIPALE_H
#define PRINCIPALE_H
#include "Stazione.h"
#include <string>

class Principale : public Stazione {
public:
    Principale(std::string);
    Principale(std::string, int);
    virtual int is_arriving(bool, int) override;
    bool is_it_free(bool) override; //prende in input 0 se treno in andata, 1 se treno in ritorno; dice se c'� almeno un binario libero
    void change_status(bool, int);
    virtual bool present_train(bool) override;

protected:
    //prende in input 0 se treno in andata, 1 se treno in ritorno; cambia lo stato del binario
    class busy_platform {};

    std::vector<int> gone;
    std::vector<int> come_back;
    void change_gone(int);
    void change_back(int);
    constexpr static int num_binari = 2;
};
#endif