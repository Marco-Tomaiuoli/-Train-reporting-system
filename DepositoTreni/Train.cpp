#pragma once
#include "Train.h"

bool Train::move(int time, int v, const std::vector<int> stazioni)
{
	setVelocità(static_cast <double>(v));																
	if (dir == true)
		pos += v * ((time - t) / static_cast<double>(60));				
	else
		pos -= v * ((time - t) / static_cast<double>(60));
	t = time;

	stand = -1;
	return segnalazione(stazioni);									    
}

double Train::getVelocità()
{
	return vel;														    
}

void Train::setVelocità(double v)
{
	vel = v;															
	constrain();														
}

double Train::getPosizione()
{
	return pos;															
}

void Train::setPosizione(double p)
{
	pos = p;															
	if (pos < 0)														
		throw new IllegalArgument();
}

int Train::whIsStand()
{
	return stand;														
}

int Train::getIdentificator()
{
	return ident;																			
}

bool Train::getDir()
{
	return dir;															
}

bool Train::segnalazione(const std::vector<int> stazioni) {
	if (getDir() == true) {												
		if ((pos - lastSegn) < 10.00)
			return false;
		for (int i = 0; i < stazioni.size(); i++) {

			if ((pos < stazioni[i])) {									
				if (pos >= (stazioni[i] - 10))							
				{
					lastSegn = pos;
					return true;										
				}

				else
					return false;										
			}
		}
	}
	else {																
		for (int i = stazioni[stazioni.size() - 1]; i > 0; i--) {
			if ((lastSegn - pos) < 10.00)
				return false;
			if ((pos > stazioni[i])) {									
				if (pos <= stazioni[i] + 10)							
				{
					lastSegn = pos;
					return true;												
				}
				else
					return false;										
			}
		}
	}
	return false;

}

int Train::getId()
{
	return id;															
}

void Train::parcheggia(bool inStation, int p)
{
	setPosizione(static_cast <double>(p));
	if (inStation)															
		stand = 0;
	else																	
		stand = -1;


}

int Train::posInt()
{
	int posIntero = static_cast<int> (pos);
	if (pos > (posIntero + 0.5))											
		return posIntero + 1;
	return posIntero;
}