#include "SuperVeloce.h"
SuperVeloce::SuperVeloce(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train(id, direzione, p, OrariTreno) {
	ident = 2;
}

void SuperVeloce::setSpeedMax()
{
	vel = 300;
}



SuperVeloce::SuperVeloce() : Train() {
	ident = 2;
}
