#include "Veloce.h"


Veloce::Veloce(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 1;//pongo l'identi�
}

Veloce::Veloce() : Train() {
	ident = 1;//pongo l'identi�
}
void Veloce::setSpeedMax()  {
	vel = 240;//pongo la velocit� massima
}
