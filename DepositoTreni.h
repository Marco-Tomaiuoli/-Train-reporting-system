//Studente: Marco Tomaiuoli 1224262



#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include "Train.h"


class DepositoTreni {
private:
	std::vector<std::queue<Train>> deposito;			//vector che rappresenta il deposito per intero
	
public:
	DepositoTreni();
	class Deposito_vuoto_exception{};	
	void posiziona_treno(Train&);	
	int get_priorita(int);
	bool isEmpty();
	void elimina_treno();
	void print(int);
	void set_speed(int, int);
};



