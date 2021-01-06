// Studente: Umberto Salviati1


#ifndef Train_h
#define Train_h
#include <iostream>

#include <vector>
//Studente: Umberto Salviati 1220994


class Train
{
public:
	bool move(int v,int time, const std::vector<int> stazioni);		//funzione che muove il treno FA LA segnalazione

	bool isArrived(std::vector<int> stazioni);						// vero se è arrivato

	float getSpeed() const;										//ritora la velocià
	void setSpeed(float v);										//set velocià
	
	float getPosition() const;									//get posizione	
	void setPosition(float p);									//set posizione	
	
	int whIsStand() const;											//Where is Standing : In che posizione è
	
	int getIdentificator()  const;									//get Indetificatore
	
	bool getDir()  const;											//get Direzione di percorrenza

	bool segnalazione(const std::vector<int> stazioni);		//invia true se a 10 km dalla stazione più vicina
	
	int getId() const;												//ritorna il codice del treno

	void parcheggia(bool inStation, int p);							//funzione per porre il treno in stato di parcheggio

	int posInt() const;												//approssima il valore pos traformandolo in int

	Train(Train&)= delete;											//Elimino i costruttore di copia sono logicamente scorretti
	Train operator=(Train&) const = delete;							//Elimino l'operatore di assegnamento, è logicamente scorretto
	
	void stazioneIncrement(int posNextStat);						//increemnta la next stazione	
	
	std::vector<int> getOrari() const;								//restituisce l'orario di partenza

	int getParkTime();												//restituisce l'orario parcheggio
	void setParkTime(int);											//imposta l'orario parcheggio
	void decremetParkTime();										//Riduce di 1 il tempo di parcheggio

	int getNextStation();
	int getLastStation();

	virtual void setSpeedMax()=0;

protected :
	Train();														//costruttori vuoti
	Train(int, bool, int, std::vector<int>);
	//ATTENZIONE IL DISTRUTTORE DI DEFAULT VA BENE PER TUTTE LE CLASSI ANCHE FIGLIE
	float vel;														//velocità
	float pos;														//posizione : disrtanza dalla prima stazione
	bool dir;														//direzione  true da inizio a capolinea, false da capolinea ad inizio	
	int t;															//tempo
	int ident;														//identificatore : 0 Regionale 1 Veloce 2 SuperVeloce
	int stand;														//posizione 0 fermo in stazione, 1 fermo in Parcheggio, -1 in movimento
	int id;															//numero treno
	int nextStation;												//posizione della prossima stazione
	int LastStation;												//posizione della stazione precedente	
	int parkTime;													//tempo di parcheggio nella stazione attuale	
	std::vector<int> Orari;											//orari 
	
	
	private:
		float lastSegn;										//dato utile per inviare una unica segnalazione ad ongi stazione -100 è un numero non valido

};



class IllegalArgument {};											//classe definita per le eccezioni
class InvalidTime {};												//classe definita per le eccezioni
#endif 