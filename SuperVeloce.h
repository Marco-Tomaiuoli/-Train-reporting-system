//Studente: Umberto Salviati 1220994

#ifndef SuperVeloce_h
#define SuperVeloce_h


#include "Train.h"
class SuperVeloce : public Train																			//classe figlia di train
{
public:
	SuperVeloce();																							//costruttore di dafault
	SuperVeloce(int, bool, int, std::vector<int>);											//costruttore
	void setSpeedMax() override {
		vel = 300;
	}



};
SuperVeloce::SuperVeloce(int id, bool direzione, int p, std::vector<int> OrariTreno) : Train( id, direzione,p, OrariTreno) {
	ident = 2;
}

SuperVeloce::SuperVeloce() : Train() {
	ident = 2;
}
#endif 