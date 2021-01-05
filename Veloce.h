//Studente: Umberto Salviati 1220994

#ifndef Veloce_h
#define Veloce_h


#include "Train.h"
class Veloce : public Train																			//classe figlia di train
{
public:
	Veloce();																						//costruttore di dafault
	Veloce(int, bool, int, std::vector<int>);														//costruttore
	void setSpeedMax() override;

};


#endif 

