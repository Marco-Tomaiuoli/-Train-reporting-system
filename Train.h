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
	
	double getSpeed() const;										//ritora la veloci�
	void setSpeed(double v);										//set veloci�
	
	double getPosition() const;									//get posizione	
	void setPosition(double p);									//set posizione	
	
	int whIsStand() const;											//Where is Standing : In che posizione �
	
	int getIdentificator()  const;									//get Indetificatore
	
	bool getDir()  const;											//get Direzione di percorrenza

	bool segnalazione(const std::vector<int> stazioni);		//invia true se a 10 km dalla stazione pi� vicina
	
	int getId() const;												//ritorna il codice del treno

	void parcheggia(bool inStation, int p);							//funzione per porre il treno in stato di parcheggio

	int posInt() const;												//approssima il valore pos traformandolo in int

	Train(Train&)= delete;											//Elimino i costruttore di copia sono logicamente scorretti
	Train operator=(Train&) const = delete;							//Elimino l'operatore di assegnamento, � logicamente scorretto
	
	void stazioneIncrement(int posNextStat);						//increemnta la next stazione	
	
	int getOrarioPartenza() const;									//restituisce l'orario di partenza


protected:
	Train();														//costruttori vuoti(sono virtuali) 
	Train(int, int, int, int, bool, int, int);
	//ATTENZIONE IL DISTRUTTORE DI DEFAULT VA BENE PER TUTTE LE CLASSI ANCHE FIGLIE
	double vel;														//velocit�
	double pos;														//posizione : disrtanza dalla prima stazione
	bool dir;														//direzione  true da inizio a capolinea, false da capolinea ad inizio	
	int t;															//tempo
	int ident;														//identificatore : 0 Regionale 1 Veloce 2 SuperVeloce
	int stand;														//posizione 0 fermo in stazione, 1 fermo in Parcheggio, -1 in movimento
	int id;															//numero treno
	int nextStation;												//posizione della prossima stazione
	int LastStation;												//posizione della stazione precedente	
	int tempoParcheggio;											//tempo di parcheggio nella stazione attuale	
	int OrarioPart;													//orario di partenza	
	
	virtual bool constrain() = 0;									//funzione che definisce le condizioni della velocit�

	private:
		double lastSegn = -100;										//dato utile per inviare una unica segnalazione ad ongi stazione -100 � un numero non valido

};



class IllegalArgument {};											//classe definita per le eccezioni
#endif 