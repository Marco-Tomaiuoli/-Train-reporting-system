//Studente: Marco Tomaiuoli 1224262




#include "DepositoTreni.h"
using namespace std;

DepositoTreni::DepositoTreni() {
	queue<Train*> superveloci;
	queue<Train*> veloci;
	queue<Train*> regionali;
	deposito.push_back(superveloci);
	deposito.push_back(veloci);
	deposito.push_back(regionali);
}

void DepositoTreni::posiziona_treno(Train* train) {
	int priorita = get_priorita(train->getIdentificator());
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

Train* DepositoTreni::elimina_treno() {
	Train* p = nullptr;
	if (isEmpty()) 
		throw Deposito_vuoto_exception();
	if (deposito[0].size() != 0) {
		p = deposito[0].front();
		deposito[0].pop();
	}
	else if (deposito[1].size() != 0) {
		p = deposito[1].front();
		deposito[1].pop();

	}
	else {
		p = deposito[2].front();
		deposito[2].pop();
	}
	return p;
}

void DepositoTreni::print(int priority) {
	queue <Train*> q = deposito[0];
	for (int i = 0; i < deposito[priority].size(); i++) {
		cout << "velocita': " << q.front()->getSpeed() << " posizione: " << q.front()->getPosition() << " id del treno: " << q.front()->getId();
		cout << endl;
		q.pop();
	}
}

void DepositoTreni::set_speed(int priority, double new_speed) {
	deposito[priority].front()->setSpeed(new_speed); 

}

bool DepositoTreni::check_binario(Stazione* station, int direzione) {
	return(station->is_arriving(true, direzione));
}

Train* DepositoTreni::prossimo_uscire() {
	Train* p = nullptr;
	if (isEmpty())
		throw Deposito_vuoto_exception();
	if (deposito[0].size() != 0)
		p = deposito[0].front();
	else if (deposito[1].size() != 0) 
		p = deposito[1].front();
	else 
		p = deposito[2].front();
	return p;
}



