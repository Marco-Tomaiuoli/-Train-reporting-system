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
	
	double getSpeed() const;										//ritora la velocià
	void setSpeed(double v);										//set velocià
	
	double getPosition() const;									//get posizione	
	void setPosition(double p);									//set posizione	
	
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
	
	std::vector<int> getOrari() const;									//restituisce l'orario di partenza

	int getParkTime();												//restituisce l'orario di partenza
	void setParkTime(int);											//imposta l'orario di partenza
	void decremetParkTime();											//Riduce di 1 il tempo di parcheggio

protected:
	Train();														//costruttori vuoti(sono virtuali) 
	Train(int, bool, int, std::vector<int>);
	//ATTENZIONE IL DISTRUTTORE DI DEFAULT VA BENE PER TUTTE LE CLASSI ANCHE FIGLIE
	double vel;														//velocità
	double pos;														//posizione : disrtanza dalla prima stazione
	bool dir;														//direzione  true da inizio a capolinea, false da capolinea ad inizio	
	int t;															//tempo
	int ident;														//identificatore : 0 Regionale 1 Veloce 2 SuperVeloce
	int stand;														//posizione 0 fermo in stazione, 1 fermo in Parcheggio, -1 in movimento
	int id;															//numero treno
	int nextStation;												//posizione della prossima stazione
	int LastStation;												//posizione della stazione precedente	
	int parkTime;													//tempo di parcheggio nella stazione attuale	
	std::vector<int> Orari;												//orari 
	virtual bool constrain() = 0;									//funzione che definisce le condizioni della velocità

	private:
		double lastSegn = -100;										//dato utile per inviare una unica segnalazione ad ongi stazione -100 è un numero non valido

};



class IllegalArgument {};											//classe definita per le eccezioni
class InvalidTime {};												//classe definita per le eccezioni
#endif 