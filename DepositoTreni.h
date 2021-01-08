//Studente: Marco Tomaiuoli 1224262



#ifndef DepositoTreni_h
#define DepositoTreni_h

#include <iostream>
#include <queue>
#include <vector>
#include "Train.h"
#include "Stazione.h"


class DepositoTreni {

private:
	std::vector<std::queue<Train*>> deposito;			//vector che rappresenta il deposito per intero

public:
	DepositoTreni();									//costruttore
	class Deposito_vuoto_exception{};				
	void posiziona_treno(Train*);						//aggiunge un treno nel deposito
	int get_priorita(int);								//sistema le priorità dei treni 0 superveloce, 1 veloce, 2 regionale
	bool isEmpty();										//controlla se ci sono treni nel deposito
	Train* elimina_treno();								//fa partire un treno dal deposito
	void print(int);									//stampa i treni dello stesso tipo del deposito
	void set_speed(int, double);						//modifica la velocità del treno in partenza
	bool check_binario(Stazione*, int);					//controlla se il binario della stazione è libero
	Train* prossimo_uscire();
};
#endif 


