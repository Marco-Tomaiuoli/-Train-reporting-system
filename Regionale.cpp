#include "Regionale.h"	



Regionale::Regionale(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 0;//pongo l'identi�
}

Regionale::Regionale() : Train() {
	ident = 0;//pongo l'identi�
}
void Regionale::setSpeedMax()   {
	vel = 160;// velocit� massima
}