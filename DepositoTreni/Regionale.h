#pragma once
#include "Train.h"
class Regionale : public Train																
{
public:
	Regionale();																			
	Regionale(int v, int p, int time, int id, bool direzione);								
protected:

	bool constrain() override { 																
		if (vel > 160 || vel < 0)
			throw new IllegalArgument();											

		return true;
	}
};
Regionale::Regionale(int v, int p, int time, int id, bool direzione) {						

	setVelocità(static_cast <double>(v));
	setPosizione(static_cast <double>(p));
	dir = direzione;
	t = time;
	stand = 0;
	ident = 0;
	this->id = id;

}
Regionale::Regionale() {																		
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	ident = 0;
	dir = true;
	id = 0;
}
