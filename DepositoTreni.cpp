//Studente:Marco Tomaiuoli 1224262



#pragma once
#include "DepositoTreni.h"
using namespace std;


DepositoTreni::DepositoTreni() {
	queue<Train> superveloci;
	queue<Train> veloci;
	queue<Train> regionali;
	deposito.push_back(superveloci);
	deposito.push_back(veloci);
	deposito.push_back(regionali);
}

void DepositoTreni::posiziona_treno(Train& train)
{
	int priorita = get_priorita(train.getIdentificator());
	deposito[priorita].push(train);
}

bool DepositoTreni::isEmpty() {
	if (deposito[0].size() == 0 && deposito[1].size() == 0 && deposito[2].size() == 0)
		return true;
	else
		return false;
}

int DepositoTreni::get_priorita(int tipo_treno)  {
	int new_priorita = 0;
	if (tipo_treno == 0)
		new_priorita = 2;
	else if (tipo_treno == 1)
		new_priorita = 1;
	else
		new_priorita = 0;
	return new_priorita;

}

void DepositoTreni::elimina_treno() {
	if (isEmpty()) 
		throw Deposito_vuoto_exception();
	if (deposito[0].size() != 0)
		deposito[0].pop();
	else if (deposito[1].size() != 0)
		deposito[1].pop();
	else
		deposito[2].pop();
	
}

void DepositoTreni::print(int priority) {
	queue <Train> q = deposito[0];
	cout << deposito[priority].size() << endl;
	for (int i = 0; i < deposito[priority].size(); i++) {
		cout << "velocita': " << q.front().getVelocità() << " posizione: " << q.front().getPosizione() << " id del treno: " << q.front().getId();
		cout << endl;
		q.pop();
	}
}

void DepositoTreni::set_speed(int priority, int new_speed) {
	deposito[priority].front().setVelocità(new_speed);

}





