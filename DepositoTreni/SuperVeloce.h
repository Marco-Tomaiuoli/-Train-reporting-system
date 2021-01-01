#pragma once
#include "Train.h"
class SuperVeloce : public Train														
{
public:
	SuperVeloce();																		
	SuperVeloce(int v, int p, int time, int id, bool direzione);						
protected:

	bool constrain() override {															
		{
			if (vel > 300 || vel < 0)
				throw new IllegalArgument();										

			return true;
		}
	}

};
SuperVeloce::SuperVeloce(int v, int p, int time, int id, bool direzione) {				

	setVelocit�(static_cast <double>(v));
	setPosizione(static_cast <double>(p));
	dir = direzione;
	t = time;
	stand = 0;
	ident = 2;
	this->id = id;
}
SuperVeloce::SuperVeloce()																
{
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	ident = 2;
	dir = true;
	id = 0;

}
