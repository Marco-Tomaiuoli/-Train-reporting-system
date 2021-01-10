//Studente: Umberto Salviati 1220994


#ifndef Train_h
#define Train_h
#include <iostream>

#include <vector>
//Studente: Umberto Salviati 1220994


class Train
{
public:
	bool move(int v,int time);		//funzione che muove il treno FA LA segnalazione

	void setTime(int);												//aggiorna il tempo

	bool isArrived(std::vector<int> stazioni);						// vero se è arrivato

	float getSpeed() const;											//ritora la velocià
	void setSpeed(float v);											//set velocià
	
	float getPosition() const;										//get posizione	
	void setPosition(int p);										//set posizione	
	
	int whIsStand() const;											//Where is Standing : In che posizione è
	
	int getIdentificator()  const;									//get Indetificatore
	
	bool getDir()  const;											//get Direzione di percorrenza

	bool segnalazione();											//invia true se a 10 km dalla stazione più vicina
	
	int getId() const;												//ritorna il codice del treno

	void parcheggia(bool inStation, int p);							//funzione per porre il treno in stato di parcheggio

	int posInt() const;												//approssima il valore pos traformandolo in int

	Train(Train&)= delete;											//Elimino i costruttore di copia sono logicamente scorretti
	Train operator=(Train&) const = delete;							//Elimino l'operatore di assegnamento, è logicamente scorretto
	
	void stazioneIncrement(int posNextStat);						//increemnta la next stazione	
	
	std::vector<int> getOrari() const;								//restituisce gli orari

	int getParkTime();												//restituisce l'orario parcheggio
	void setParkTime(int);											//imposta l'orario parcheggio
	void decremetParkTime();										//Riduce di 1 il tempo di parcheggio

	int getNextStation();											//ritorna la posizione della prossima stazione
	int getLastStation();											//ritorna la posizione della stazione precedente

	void setRitardo(int);											//set ritardo
	int getRitardo();												//ritorna il ritardo

	virtual void setSpeedMax()=0;									//fuznione che restituisce la velocità massima(virtual)


protected :
	Train();														//costruttore di default
	Train(int, bool, int, std::vector<int>);						//costruttore 
	//ATTENZIONE IL DISTRUTTORE DI DEFAULT VA BENE PER TUTTE LE CLASSI ANCHE FIGLIE
	float vel;														//velocità
	float pos;														//posizione : disrtanza dalla prima stazione(anche se LinaFerroviaria gestisce tutto con int la poszione deve essere decimale per eviatare assurde approssimazioni)
	bool dir;														//direzione  true da inizio a capolinea, false da capolinea ad inizio	
	int t;															//tempo
	int ident;														//identificatore : 0 Regionale 1 Veloce 2 SuperVeloce
	int stand;														//posizione 0 fermo in stazione, 1 fermo in Parcheggio, -1 in movimento
	int id;															//numero treno
	int nextStation;												//posizione della prossima stazione/stazione attuale 
	int LastStation;												//posizione della stazione precedente	
	int parkTime;													//tempo di parcheggio nella stazione attuale	
	std::vector<int> Orari;											//orari 
	int ritardo;													//dato per il ritardo
	
	private:
		float lastSegn;										//dato utile per inviare una unica segnalazione ad ongi stazione -100 è un numero non valido

};



class IllegalArgument {};											//classe definita per le eccezioni
class InvalidTime {};												//classe definita per le eccezioni
#endif 