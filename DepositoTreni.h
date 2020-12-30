#include <iostream>
#include <queue>
#include <string>
#include <vector>

template <typename T>
class DepositoTreni {
private:
	std::queue<T> superveloci;                      //coda contenente i treni super veloci (priorità 0) max 
	std::queue<T> veloci;				            //coda contenente i treni veloci	   (priorità 1)
	std::queue<T> regionali;			            //coda contenente i treni regionali    (priorità 2) min
	std::vector<std::queue<T>> deposito;			//vector che rappresenta il deposito per intero
	
public:
	class Deposito_vuoto_exception{};
	DepositoTreni();
	int get_priorita(int);							//usare treno.segnalazione_Arrivo()
	void stampa_coda(int) const;
	void posiziona_treno(T);
	void elimina_treno();
	bool isEmpty();
};



