// Studente: Umberto Salviati


#include "Train.h"

bool Train::move(int time, int v, const std::vector<int> stazioni)
{
	setVelocità(static_cast <double>(v));											//imposta la velocità					
	if (dir== true)
		pos += v * ((time - t) / static_cast<double>(60));				//aggiorno la nuova posizione
	else
		pos -= v * ((time - t) / static_cast<double>(60));
	t = time;
	
	stand = -1;
	return segnalazione(stazioni);									    //ritorno la eventuale segnalazione
}

double Train::getVelocità()
{	
	return vel;														    //ritorna la velocià
}

void Train::setVelocità(double v)
{
	vel = v;															//imposta la nuova velocià
	constrain();														//controllo che le condizioni di velocità siano rispettate
}

double Train::getPosizione()
{
	return pos;															//ritorna la posizione
}

void Train::setPosizione(double p)
{
	pos = p;															//imposta la posizione
	if (pos < 0)														//controllo se la posizione è valida
		throw new IllegalArgument();
}

int Train::whIsStand()
{
	return stand;														//ritorna lo stato del treno(fermo in stazione,fermo in parcheggio,in movimento)
}

int Train::getIdentificator()
{
	return ident;														//ritorna il tipo di treno						
}

bool Train::getDir()
{
	return dir;															//ritorna la direzione di percorrenza
}

bool Train::segnalazione(const std::vector<int> stazioni) {
	if (getDir() == true) {												//se il verso è 'positivo'
		if ((pos - lastSegn) < 10.00)
			return false;
		for (int i = 0; i < stazioni.size(); i++) {						

			if ((pos < stazioni[i])) {									//se la posiozne dell'i-esima stazione è maggiore di pos
				if (pos >= (stazioni[i] - 10))							//e se la posizione del treno è nei primi 10 km
				{
					lastSegn = pos;
					return true;										//allora segnala
				}
				
				else
					return false;										//sennò non seganlare
			}
		}
	}
	else {																// se il verso è negativo
		for (int i = stazioni[stazioni.size()-1]; i > 0; i--) {			
			if ((lastSegn - pos) < 10.00)
				return false;
			if ((pos > stazioni[i])) {									//se la poszione è maggiore dell' i-esima stazione
				if (pos <= stazioni[i] + 10)							// e se il treno è nei primi 10 km dalla satazione
				{
					lastSegn = pos;
					return true;										//allora segnala		
				}									
				else
					return false;										//sennò non seganlare
			}
		}
	}
	return false;

}

int Train::getId()
{
	return id;															//ritorna il codice treno
}

void Train::parcheggia(bool inStation, int p)
{
	setPosizione(static_cast <double>(p) );
	if (inStation)															//se è parcheggiato in stazione
		stand = 0;
	else																	//altrimenti è in un Parcheggio
			stand = -1;				
	
		
}


