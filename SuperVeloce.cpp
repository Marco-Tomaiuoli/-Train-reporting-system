//Studente: Umberto Salviati 1220994


#include "SuperVeloce.h"
SuperVeloce::SuperVeloce(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 2;//pongo l'identi�
}

void SuperVeloce::setSpeedMax()
{
	vel = 300;//velocit� massima
}



SuperVeloce::SuperVeloce() : Train() {
	ident = 2;//pongo l'identi�
}
