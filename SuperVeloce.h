// Studente: Umberto Salviati


#pragma once


#include "Train.h"
class SuperVeloce : public Train														//classe figlia di train
{
public:
	SuperVeloce();																		//costruttore di dafault
	SuperVeloce(int v, int p, int time, int id, bool direzione);						//costruttore
protected:

	bool constrain() override {															//sovrascrivo la classe constrain
		{
			if (vel > 300 || vel < 0)
				throw new IllegalArgument();										//lancia encezione

			return true;
		}
	}

};
SuperVeloce::SuperVeloce(int v, int p, int time, int id, bool direzione) {				//costruttore
	
	setVelocità(static_cast <double>(v));
	setPosizione(static_cast <double>(p));
	dir = direzione;
	t = time;
	stand = 0;
	ident = 2;
	this->id = id;
}
SuperVeloce::SuperVeloce()																//costruttore di default
{
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	ident = 2;
	dir = true;
	id = 0;
	
}

