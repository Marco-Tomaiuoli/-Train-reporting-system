// Studente: Umberto Salviati


#pragma once


#include "Train.h"
class Regionale : public Train																//classe figlia di train
{	public:
	Regionale();																			//costruttore di dafault
	Regionale(int v, int p, int time, int id, bool direzione);								//costruttore
protected:
	
	bool constrain() override{ 																//sovrascrivo la classe constrain
		if (vel > 160 || vel < 0)
			throw new IllegalArgument();											//lancia encezione

		return true;
	}
};
Regionale::Regionale(int v, int p, int time, int id, bool direzione) {						//costruttore

	setVelocità(static_cast <double>(v));
	setPosizione(static_cast <double>(p));
	dir = direzione;
	t = time;
	stand = 0;
	ident = 0;
	this->id = id;

}
Regionale::Regionale()																		//costruttore di default
{
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	ident = 0;
	dir = true;
	id = 0;
}

