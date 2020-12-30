#include "DepositoTreni.h"
using namespace std;

template<typename T>
DepositoTreni<T>::DepositoTreni() {
	deposito.push_back(superveloci);
	deposito.push_back(veloci);
	deposito.push_back(regionali);
}

template<typename T>
void DepositoTreni<T>::stampa_coda(int priorita) const {
	for (int i = 0; i < deposito[priorita].size(); i++)
		cout << deposito[priorita].back() << " ";
}

template<typename T>
bool DepositoTreni<T>::isEmpty() {
	if (deposito[0].size() == 0 && deposito[1].size() == 0 && deposito[2].size() == 0)
		return true;
	else
		return false;
}

template<typename T>
int DepositoTreni<T>::get_priorita(int tipo_treno)  {
	int new_priorita = 0;
	if (tipo_treno == 0)
		new_priorita = 2;
	else if (tipo_treno == 1)
		new_priorita = 1;
	else
		new_priorita = 0;
	return new_priorita;

}
template<typename T>
void DepositoTreni<T>::posiziona_treno(T train) {
	//int priorita = get_priorita(T.getIdentificator());  
	deposito[0].push(train); //mettere priorita tra parantesi
	
}

template<typename T>
void DepositoTreni<T>::elimina_treno() {
	if (isEmpty()) {
		cout << "Il deposito e' momentaneamente vuoto" << endl;
		throw Deposito_vuoto_exception();
	}
	if (deposito[0].size() != 0)
		deposito[0].pop();
	else if (deposito[1].size() != 0)
		deposito[1].pop();
	else
		deposito[2].pop();
	
}

int main() {
	DepositoTreni<double> d;
	d.posiziona_treno(1);
	d.stampa_coda(0);
	d.posiziona_treno(2);
	d.stampa_coda(0);
	d.posiziona_treno(3);
	d.stampa_coda(0);
	
	
}


