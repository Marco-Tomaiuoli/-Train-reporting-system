// Studente: Umberto Salviati


#pragma once



#include "Train.h"
class Veloce : public Train													//classe figlia di train
{
public:
	Veloce();																	//costruttore di dafault
	Veloce(int v, int p, int time, int id, bool direzione);						//costruttore
protected:


	bool constrain() override													//sovrascrivo la classe constrain
	{
		if (vel > 240 || vel < 0)
			throw new IllegalArgument();

		return true;
	}

};
Veloce::Veloce(int v, int p, int time, int id, bool direzione) {				//costruttore
	
	setVelocità(static_cast <double>(v));
	setPosizione(static_cast <double>(p));
	dir = direzione;
	t = time;
	stand = 0;
	ident = 1;
	this->id = id;
}
Veloce::Veloce()																//costruttore di default
{
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	ident = 1;
	dir = true;
	id = 0;
}


