//Studente: Umberto Salviati 1220994



#include "Train.h"

void Train::stazioneIncrement(int posNextStat)									//funzione che incrementa la poszione della prossima stazione
{
	LastStation = nextStation;
	nextStation = posNextStat;

}

std::vector<int> Train::getOrari() const										//get il vettore orari
{
	return Orari;
}

int Train::getParkTime()														//get il tempo di parcheggio in stazione
{
	return parkTime;
}

void Train::setParkTime(int TempoParcheggio)									//set il tempo di parcheggio
{
	parkTime= TempoParcheggio;
}

void Train::decremetParkTime()													//decerementa il parcheggio fino ad un minimo di -1(valore di default)
{
	parkTime--;
	if (parkTime < -1)
		throw InvalidTime{};
}

int Train::getNextStation()														// get la posizione della prossima stazione/stazione attuale 
{
	return nextStation;
}

int Train::getLastStation()														//get la posizione stazione precedente
{
	return LastStation;
}

void Train::setRitardo(int r)													//set il ritardo accumulato
{
	ritardo = r;
}

int Train::getRitardo()															// get il ritardo accumulato
{
	return ritardo;
}

Train::Train() {																//costruttore di default (è stato utile solo nella fase di tasting) pone tutti gli attributi a 0
	ident = -5;																	//valore logicamente nullo
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	dir = true;
	id = 0;
	nextStation = 0;
	LastStation = 0;
	parkTime = -1;
	lastSegn = pos - 30;
	ritardo = 0;
}
Train::Train(int id, bool direzione, int p, std::vector<int> OrariTreno) {		//costruttore
	if (OrariTreno.size() <= 0)													//se il vettore di orari è vuoto
		throw IllegalArgument();												//lancia ecceszione
	setSpeed(80.00f);															//imposta la velocità a 80 km/h
	setPosition(static_cast <float>(p));										//imposta la poszione
	dir = direzione;															//imposta la direzione
	t = OrariTreno[0];															//poni il tempo = al tempo di partenza
	stand = 0;																	//poni il treno in "stato" parcheggia in stazione
	this->id = id;																//imposta id
	Orari = OrariTreno;															//imposta il vettore di orari previsti
	nextStation = pos;															//la prossima stazione/stazione attuale è in posizione pos
	LastStation = pos;															//l'ultima stazione visitata è la prima in posizione pos
	parkTime = -1;																//il treno inizialmente imposta il tempo di parcheggio con un valore nullo
	if (direzione)																// se la direzione è postiva
		lastSegn = p - 25;														//poni l'ulima segnalazione fatta a -30 km
	else
		lastSegn = p + 25;														//poni l'ulima segnalazione fatta a -30 km
	ritardo = 0;

}

bool Train::move(int time, int v)															//funzione muovi
{
	if (v == -1)																			//se v =-1 
		setSpeedMax();																		//poni la velocità a max
	else
	setSpeed(static_cast <float>(v));														//poni la velocità uguale a v
	if (dir == true)
		pos += vel * ((time - t) / static_cast<float>(60));									//muovi 
	else
		pos = pos -( vel * ((time - t) / static_cast<float>(60)));							//muovi 
	t = time;																				//aggiorna tempo

	stand = -1;																				//poini lo stato in moto
	parkTime = -1;																			//poni il tempo di parcheggio in stazione nullo
	return segnalazione();																	// segnala
}

void Train::setTime(int time)															//aggiorna tempoo
{
	t = time;
}

bool Train::isArrived(std::vector<int> stazioni)															//funzione che controlla se il treno è arrivato
{
	if (dir && pos >= stazioni[stazioni.size() - 1] && LastStation!=nextStation)														//se la direzione è positiva e il treno è alla stazione finale
		return true;
	else if (!dir && pos <= 0 && LastStation != nextStation)																				// senno se il treno è alla stazione iniziale(ricontrolla la direzione perchè il treno con direzione positiva pèotrebbe essere nel deposito dietro la prima stazione)
		return true;
	else false;
}

float Train::getSpeed() const															//get velocità
{
	return vel;
}

void Train::setSpeed(float v)															//set velocità
{
	vel = v;
}

float Train::getPosition() const															//ritorna la poszione ATTENZIONE: questa funzione NON approssima il numero della posizione
{
	return pos;
}

void Train::setPosition(int p)															//set poszione
{
	pos = static_cast<float>(p);
	if (pos < -5)																		//la posizone al minimo potà essere -5 (nel deposito)
		throw  IllegalArgument();
}

int Train::whIsStand() const															//where is standing
{
	return stand;																		//stato di posizione
}

int Train::getIdentificator() const															//identificatore
{
	return ident;
}

bool Train::getDir() const															// get direzione
{
	return dir;
}

bool Train::segnalazione() {																							//funzione per la segnalazione

	if (getDir() == true) {	
		if (static_cast<float>(pos - lastSegn) < 20.00f)																	//se è stato segnalato già meno di km fa
			return false;
		if (pos >= (static_cast<float>(nextStation) - static_cast < float>(20)))										//il treno è a meno di km dalla prossima stazione
		{
			lastSegn = pos;																								//pongo last segnalazione = alla poszione in questo momento
			return true;																								//segnalo
		}
				else
					return false;
	}
	else {
		if (static_cast<float>( lastSegn - pos ) < 20.00f)																	//se è stato segnalato già meno di km fa
		return false;
		if (pos <= static_cast<float>(nextStation + 20))															//il treno è a meno di km dalla prossima stazione
		{
			lastSegn = pos;																							//pongo last segnalazione = alla poszione in questo momento
			return true;																							//segnalo
		}
		else
			return false;			
	}

}

int Train::getId() const															// get id
{
	return id;
}

void Train::parcheggia(bool inStation, int p)															//funzione per parcheggiare il treno
{
	setPosition(static_cast <float>(p));																//parcheggia il treno nella poszione precisa
	if (inStation)
		stand = 0;																						//poni lo stato in parcheggio stazione
	else
		stand = 1;


}

int Train::posInt() const																			//funzione che ritorna la poszione approssimata
{
	int posIntero = static_cast<int> (pos);															//staic cast
	if (pos > (posIntero + 0.5))
		return posIntero + 1;
	return posIntero;
}