// Studente: Umberto Salviati1


#ifndef train_h
#define train_h

#include <iostream>

#include <vector>

class Train
{
public:
	bool move(int time, int v, const std::vector<int> stazioni);	//funzione che muove il treno FA LA segnalazione
	
	double getVelocità();											//ritora la velocià
	void setVelocità(double v);										//set velocià
	
	double getPosizione() ;											//get posizione	
	void setPosizione(double p);									//set posizione	
	
	int whIsStand();												//Where is Standing : In che posizione è
	
	int getIdentificator();											//get Indetificatore
	
	bool getDir();													//get Direzione di percorrenza

	bool segnalazione(const std::vector<int> stazioni);				//invia true se a 10 km dalla stazione più vicina
	
	int getId();													//ritorna il codice del treno

	void parcheggia(bool inStation, int p);							//funzione per porre il treno in stato di parcheggio

	int posInt();													//approssima il valore pos traformandolo in int

	Train(const Train&) = delete;									// escludo i costruttori di copia e assegnamento(non hanno senso per un treno)
	Train operator=(const Train&) = delete;
protected:
	Train() {};														//costruttori vuoti(sono virtuali) 
	Train(int v, int p, int time, int id, bool direzione) {};
	//ATTENZIONE IL DISTRUTTORE DI DEFAULT VA BENE PER TUTTE LE CLASSI ANCHE FIGLIE
	double vel;														//velocità
	double pos;														//posizione : disrtanza dalla prima stazione
	bool dir;														//direzione  true da inizio a capolinea, false da capolinea ad inizio	
	int t;															//tempo
	int ident;														//identificatore : 0 Regionale 1 Veloce 2 SuperVeloce
	int stand;														//posizione 0 fermo in stazione, 1 fermo in Parcheggio, -1 in movimento
	int id;															//numero treno

	private:
		double lastSegn = -100;										//dato utile per inviare una unica segnalazione ad ongi stazione -100 è un numero non valido
	  
	virtual bool constrain()=0;									//funzione che definisce le condizioni della velocità
};



class IllegalArgument {};											//classe definita per le eccezioni
#endif 