//Studente: Umberto Salviati 1220994



#include "Train.h"

void Train::stazioneIncrement(int posNextStat)
{
	LastStation = nextStation;
	nextStation = pos;

}

int Train::getOrarioPartenza() const
{
	return OrarioPart;
}

int Train::getParkTime()
{
	return parkTime;
}

void Train::setParkTime(int TempoParcheggio)
{
	parkTime= TempoParcheggio;
}

void Train::decremetParkTime()
{
	parkTime--;
	if (parkTime < -1)
		throw InvalidTime{};
}

Train::Train() {
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	dir = true;
	id = 0;
	OrarioPart = 0;
	nextStation = 0;
	LastStation = 0;
	parkTime = -1;
}
Train::Train(int v, int p, int time, int id, bool direzione,int orarioPart,int posStazioneIniziale) {
	setSpeed(static_cast <double>(v));
	setPosition(static_cast <double>(p));
	dir = direzione;
	t = time;
	stand = 0;
	this->id = id;
	OrarioPart = orarioPart;
	nextStation = posStazioneIniziale;
	LastStation = posStazioneIniziale;
	parkTime = -1;

}

bool Train::move(int time, int v, const std::vector<int> stazioni)
{
	setSpeed(static_cast <double>(v));
	if (dir == true)
		pos += v * ((time - t) / static_cast<double>(60));
	else
		pos -= v * ((time - t) / static_cast<double>(60));
	t = time;

	stand = -1;
	return segnalazione(stazioni);
}

double Train::getSpeed() const
{
	return vel;
}

void Train::setSpeed(double v)
{
	vel = v;
	constrain();
}

double Train::getPosition() const
{
	return pos;
}

void Train::setPosition(double p)
{
	pos = p;
	if (pos < 0)
		throw  IllegalArgument();
}

int Train::whIsStand() const
{
	return stand;
}

int Train::getIdentificator() const
{
	return ident;
}

bool Train::getDir() const
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

int Train::getId() const
{
	return id;
}

void Train::parcheggia(bool inStation, int p)
{
	setPosition(static_cast <double>(p));
	if (inStation)
		stand = 0;
	else
		stand = -1;


}

int Train::posInt() const
{
	int posIntero = static_cast<int> (pos);
	if (pos > (posIntero + 0.5))
		return posIntero + 1;
	return posIntero;
}