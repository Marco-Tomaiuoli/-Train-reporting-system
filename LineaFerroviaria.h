//Studente: Marco Tomaiuoli 1224262



#ifndef LineaFerroviaria_h
#define LineaFerroviaria_h
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Locale.h"
#include "DepositoTreni.h"
#include "SuperVeloce.h"
#include "Veloce.h"
#include "Regionale.h"
#include <stdlib.h>
#include <crtdbg.h>

class LineaFerroviaria {
private:
	int time = 0;															//tempo
	constexpr static int waste = 10;										//scarto massimo anticipo treno
	constexpr static int time_stop_station = 5;								//tempo di stop minimo dei treni nelle stazioni
	constexpr static int min_distance = 20;									//distanza minima tra due stazioni
	int n_station = 0;														//numero delle staioni
	int n_pstation = 0;														//numero delle stazioni principali
	int n_treni = 0;														//numero dei treni totale
	std::vector<int> orari_partenze;										//contenitore degli orari di partenza dei treni
	std::vector<int> posizioneStazioni;										//contenitore delle distanze tra le stazioni e la stazione iniziale
	std::list<Train*> treni;												//contenitori dei treni
	std::vector<Stazione*> stazioni;										//contenitore delle stazioni
	std::vector<DepositoTreni*> depositi;									//contenitore dei depositi
	std::vector<Train*> treniIntransito;									//contenitore dei treni in transito
	std::vector<Train*> UPDATEinTransito;									//contenitore aggiornato dei treni in transito
	std::list<Train*> UPDATEinDeposito;										//contenitore aggiornato dei treni in deposito
	std::list<Train*> UPDATEdaDepositoInStazione;							//contenitore aggiornato dei treni partiti dal deposito diretti in stazione
	std::list<Train*> UPDATEinStazione;										//contenitore aggiornato dei treni in stazione
	std::vector<Train*> inTransito;											//contenitore dei treni in transito
	std::list<Train*> inDeposito;											//contenitore dei treni arrivati in deposito
	std::list<Train*> inStazione;											//contenitore dei treni in stazione
	std::list<Train*> daDepositoInStazione;									//contenitore dei treni che stanno andando dalla stazione al deposito
	std::list<Train*> daStazioneInTransito;									//contenitore dei treni che stanno partendo dalla stazione
	void openStation(std::string);											//legge il file delle stazioni e crea i vector di stazini e distanze
	void openTrain(std::string);											//legge il file dei treni e crea la lista contenente i treni che devono partire
	int count_train(std::string);											//conta il numero dei treni 
	int add_time(int, int, int, int);										//modifica il valore del tempo nel caso sia sbagliato
	int check_speed(int);													//mette la velocità max del treno in base a che tipo è il treno
	void treni_in_deposito();												//aggiorna il deposito facendo uscire i treni 
	void posiziona_treni();													//aggiunge nel deposito i treni che devono entrare nel deposito
	int orario_inizio();													//ritorna l'orario di partenza del primo treno
	bool check_time(int, int, int);											//controlla se il tempo è stato cambiato correttamente
	static bool check_distance(Stazione*, Stazione*);						//controlla se la distanza minima è rispettata
	std::string print_time(int);											//modifica il tempo passato in minuti nel tempo in formato "ora:minuti"
	void gestione_depostio();												//funzione che gestisce i depositi
	void ordinaStazioni();													//funzione che ordina le stazioni
	void distanze_stazioni();												//funzione che seleziona solo le distanze valide tra le stazioni
	void stampa_timetable();												//funzione che stampa la timetable
	std::string cambia_tipo(int);											//funzione che converte il tipo int in tipo string
	std::string stampa_orari(std::vector<int>);								//funzione che unifica tutti gli otari in un'unica stringa
	std::vector<int> somma_orari(std::vector<int>);							//somma l'orario di partenza con quello di arrivo alle varie stazioni

	void AvanzaTreniInTransito();
	void DaStazioneAInTransito();
	void DaDepositoAStazione();
	void updateliste();
	void occupaSegnala(Stazione*, Train*, bool);
	void avvisoArrivo(Train*);
	void allTreniArrived();
	void spawnTreno();
	void exitFromStation(Train*);
	int getIndexStazione(int);
	void muoviStampa(Train*, int);
	static bool SpeedIsGood(Train*, int);
	static void sortTrain(std::vector<Train*>&);
	void incrementaLaStazione(Train*);
	static void printTrain(Train*);
	static void sumList(std::list<Train*>&, std::list<Train*>&);
	static void sumVector(std::vector<Train*>&, std::vector<Train*>&);
	void gestioneRitardo(Train*, int);

	void in_Stazione();
	void trenoInpartenza(std::list<Train*>&);
	Train* get_train(std::list<Train*>&, int, std::list<Train*>::iterator&);
	void let_the_train_start(std::list<Train*>&);
	void lastDelay(Train*);
public:
	~LineaFerroviaria();													//distruttore
	void start();
};
#endif 

