//Studente: Umberto Salviati 1220994

#ifndef Regionale_h
#define Regionale_h


#include "Train.h"	
class Regionale : public Train																			//classe figlia di train
{	public:
	Regionale();																						//costruttore di dafault
	Regionale(int, bool, int, std::vector<int>);														//costruttore
	void setSpeedMax() override {
		vel = 160;
	}

};
Regionale::Regionale(int id, bool direzione, int p,std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 0;
}

Regionale::Regionale() : Train() {
	ident = 0;
}

#endif 