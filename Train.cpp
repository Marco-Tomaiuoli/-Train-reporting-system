//Studente: Umberto Salviati 1220994



#include "Train.h"

void Train::stazioneIncrement(int posNextStat)
{
	LastStation = nextStation;
	nextStation = posNextStat;

}

std::vector<int> Train::getOrari() const
{
	return Orari;
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

int Train::getNextStation()
{
	return nextStation;
}

int Train::getLastStation()
{
	return LastStation;
}

Train::Train() {
	vel = 0;
	pos = 0;
	t = 0;
	stand = 0;
	dir = true;
	id = 0;
	nextStation = 0;
	LastStation = 0;
	parkTime = -1;
}
Train::Train(int id, bool direzione, int p, std::vector<int> OrariTreno) {
	if (OrariTreno.size() <= 0)
		throw IllegalArgument();
	setSpeed(80.00);
	setPosition(static_cast <float>(p));
	dir = direzione;
	t = OrariTreno[0];
	stand = 0;
	this->id = id;
	Orari = OrariTreno;
	nextStation = pos;
	LastStation = pos;
	parkTime = -1;
	if (direzione)
		lastSegn = p - 30;
	else
		lastSegn = p + 30;

}

bool Train::move(int time, int v, const std::vector<int> stazioni)
{
	if (v == -1)
		setSpeedMax();
	else
	setSpeed(static_cast <float>(v));
	if (dir == true)
		pos += v * ((time - t) / static_cast<float>(60));
	else
		pos -= v * ((time - t) / static_cast<float>(60));
	t = time;

	stand = -1;
	return segnalazione(stazioni);
}

bool Train::isArrived(std::vector<int> stazioni)
{
	if (dir && pos >= stazioni[stazioni.size() - 1])
		return true;
	else if (pos <= 0)
		return true;
	else false;
}

float Train::getSpeed() const
{
	return vel;
}

void Train::setSpeed(float v)
{
	vel = v;
}

float Train::getPosition() const
{
	return pos;
}

void Train::setPosition(float p)
{
	pos = p;
	if (pos < -5)
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
		if ((pos - lastSegn) < 20.00)
			return false;
		for (int i = 0; i < stazioni.size(); i++) {

			if ((pos < stazioni[i])) {
				if (pos >= (stazioni[i] - 20))
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
		for (int i = stazioni.size() - 1; i > 0; i--) {
			if ((lastSegn - pos) < 20.00)
				return false;
			if ((pos > stazioni[i])) {
				if (pos <= stazioni[i] + 20)
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
	setPosition(static_cast <float>(p));
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