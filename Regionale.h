//Studente: Umberto Salviati 1220994

#ifndef Regionale_h
#define Regionale_h


#include "Train.h"	
class Regionale : public Train																			//classe figlia di train
{	public:
	Regionale();																						//costruttore di dafault
	Regionale(int, int, int, int, bool, int, int);														//costruttore
protected:
			
	bool constrain() override{ 																			//sovrascrivo la classe constrain
		if (vel > 160 || vel < 0)
			throw new IllegalArgument();																//lancia encezione

		return true;
	}
};
Regionale::Regionale(int v, int p, int time, int id, bool direzione,int orarioPart, int posStazioneIniziale) : Train(v, p, time, id, direzione, orarioPart, posStazioneIniziale) {
	ident = 0;
}

Regionale::Regionale() : Train() {
	ident = 0;
}

#endif 