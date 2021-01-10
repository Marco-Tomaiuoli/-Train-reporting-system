#pragma once

#include <iostream>
#include "Regionale.h"
#include "SuperVeloce.h"
#include "Veloce.h"
#include <vector>
#include <list>
#include "Locale.h"

class LineaFerroviaria
{
public:
	LineaFerroviaria();
	
	void start();

private:

	void DaStazioneAInTransito();
	void AvanzaTreniInTransito();
	void DaDepositoAStazione();	
	void updateliste();
	
	int time=0;
	
	std::vector<Train*>	inTransito;
	std::vector< Train*> UPDATEinTransito;
	std::vector<int> Orari;
	std::vector<int> posizioneStazioni;
	std::vector<Stazione*> stazioni;
	

	std::list<Train*>	UPDATEinDeposito;
	std::list<Train*>	UPDATEinStazione;
	
	std::list<Train*> treni;


	std::list<Train*>	inDeposito;
	std::list<Train*>	UPDATEdaDepositoInStazione;
	std::list<Train*>	daDepositoInStazione;
	std::list<Train*>	inStazione;
	std::list<Train*>	daStazioneInTransito;

	void print_time(int time);
	void avvisoArrivo(Train*);
	bool allTreniArrived();
	void occupaSegnala(Stazione*, Train*, bool);
	void exitFromStation(Train*);
	int getIndexStazione(int);
	void muoviStampa(Train*,int );

	static bool SpeedIsGood(Train*,int);
	static void sortTrain(std::vector < Train*>&);
	void incrementaLaStazione(Train*);
	static void printTrain(Train* t);
	static void sumList(std::list<Train*>&, std::list<Train*>&);
	static void sumVector(std::vector<Train*>&, std::vector<Train*>&);
	void gestioneRitardo(Train*, int);
};

