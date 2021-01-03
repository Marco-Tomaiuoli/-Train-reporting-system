//Studente: Umberto Salviati 1220994

#ifndef Veloce_h
#define Veloce_h


#include "Train.h"
class Veloce : public Train																			//classe figlia di train
{
public:
	Veloce();																						//costruttore di dafault
	Veloce(int, int, int, int, bool, int, int);														//costruttore
protected:


	bool constrain() override																		//sovrascrivo la classe constrain
	{
		if (vel > 240 || vel < 0)
			throw IllegalArgument();

		return true;
	}

};
Veloce::Veloce(int v, int p, int time, int id, bool direzione,int orarioPart, int posStazioneIniziale) : Train(v, p, time, id, direzione, orarioPart, posStazioneIniziale) {
	ident = 1;
}

Veloce::Veloce() : Train() {
	ident = 1;
}

#endif 

