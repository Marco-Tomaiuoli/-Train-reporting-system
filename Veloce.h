//Studente: Umberto Salviati 1220994

#ifndef Veloce_h
#define Veloce_h


#include "Train.h"
class Veloce : public Train																			//classe figlia di train
{
public:
	Veloce();																						//costruttore di dafault
	Veloce(int, bool, int, std::vector<int>);														//costruttore
protected:


	bool constrain() override																		//sovrascrivo la classe constrain
	{
		if (vel > 240 || vel < 0)
			throw IllegalArgument();

		return true;
	}

};
Veloce::Veloce(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 1;
}

Veloce::Veloce() : Train() {
	ident = 1;
}

#endif 

