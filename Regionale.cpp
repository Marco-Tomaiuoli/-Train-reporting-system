#include "Regionale.h"	



Regionale::Regionale(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 0;
}

Regionale::Regionale() : Train() {
	ident = 0;
}
void Regionale::setSpeedMax()   {
	vel = 160;
}