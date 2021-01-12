//Studente: Umberto Salviati 1220994


#ifndef SuperVeloce_h
#define SuperVeloce_h


#include "Train.h"
class SuperVeloce : public Train																			//classe figlia di train
{
public:
	SuperVeloce();																							//costruttore di dafault
	SuperVeloce(int, bool, int, std::vector<int>);															//costruttore
	void setSpeedMax() override;																			//sovrastrivi la classe


};

#endif 