//Studente: Umberto Salviati 1220994

#ifndef SuperVeloce_h
#define SuperVeloce_h


#include "Train.h"
class SuperVeloce : public Train																			//classe figlia di train
{
public:
	SuperVeloce();																							//costruttore di dafault
	SuperVeloce(int, int, int, int, bool, int, int);														//costruttore
protected:

	bool constrain() override {															//sovrascrivo la classe constrain
		{
			if (vel > 300 || vel < 0)
				throw IllegalArgument();										//lancia encezione

			return true;
		}
	}

};
SuperVeloce::SuperVeloce(int v, int p, int time, int id, bool direzione, int orarioPart, int posStazioneIniziale) : Train(v, p, time, id, direzione,orarioPart,posStazioneIniziale) {
	ident = 2;
}

SuperVeloce::SuperVeloce() : Train() {
	ident = 2;
}
#endif 