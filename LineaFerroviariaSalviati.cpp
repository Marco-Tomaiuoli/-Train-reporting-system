//Studente: Umberto Salviati 1220994


#include "LineaFerroviaria.h"

using namespace std;

LineaFerroviaria::LineaFerroviaria(std::string s, std::string t)
{

	openStation(s);
	openTrain(t);

}

void LineaFerroviaria::start()
{	
	
	time = orario_inizio();
	//lettura file
	spawnTreno();
	while (!allTreniArrived()) {

		time++;

		if (time == 922) {
			cout << "tempo : " << time << endl << endl;
		}
		DaStazioneAInTransito();
		AvanzaTreniInTransito();
		DaDepositoAStazione();
		gestione_depostio();
		gestioneTreniInStazione();
		updateliste();
		spawnTreno();

	}
	cout << "tempo : " << time << endl << endl;
	stampa_timetable();

}

void LineaFerroviaria::spawnTreno()
{
	
	for (auto it = treni.begin(); it != treni.end(); it++)
	{	
		if(time<1440)
		{
			if(time == (*it)->getOrari()[0])
			{
				if((*it)->getDir())
				{
					if (stazioni[0]->is_it_free(true))
					{
						// TODO correggi cout
						occupaSegnala(stazioni[0], (*it), true);								//occupa un binario e ricevi la segnalazione della stazione
						avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
						inStazione.push_back((*it));
					}
					else
					{
						(*it)->setPosition(-5);
						inDeposito.push_back(*it);
					}
				}	
				
				else
				{
					if (stazioni[stazioni.size()-1]->is_it_free(false))
					{
							// TODO correggi cout
							occupaSegnala(stazioni[stazioni.size() - 1], (*it), false);								//occupa un binario e ricevi la segnalazione della stazione
							avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
							inStazione.push_back((*it));
					}
					else 
					{
							(*it)->setPosition(posizioneStazioni[posizioneStazioni.size()-1]+5);
							inDeposito.push_back(*it);
					}
				}	
			}
		}
	}
}




void LineaFerroviaria::muoviStampa(Train* t, int v)																//funzione che gestisce il move
{
	bool stampa = t->move(time,v);																				//muovi il treno con velocità v (return seganle)
	if(stampa){																									//se il treno segnala
		int i = getIndexStazione(t->getNextStation());															//calcola l'index stazione
		cout << "il Treno numero " << t->getId() << " sta arrivando alla stazione "<< stazioni[i]->get_name()<< " alle  " << print_time(time);	//stampa in standard output
		if (stazioni[i]->is_local() && t->getIdentificator() > 0){												//controllo se Locale e se treno non è regionale
			cout << ", non fermera' alla stazione " << endl;														//stampa in standard output
			cout << "La stazione non segnala nulla il treno prosegue senza impedimenti nella corsia veloce  "<< print_time(time)<< endl;}//stampa in standard output
		else
			cout << ", si fermerà alla stazione "<< endl;														//stampa in standard output
	}
}



void LineaFerroviaria::DaDepositoAStazione()																	//gestione treni da -5 km dalla posizione della stazione a stazione
{	
	if(!daDepositoInStazione.empty())
	{
		auto it = daDepositoInStazione.begin();
		bool deleted= false;
		while (!daDepositoInStazione.empty() && it != daDepositoInStazione.end())						//scorro la lista
		{
			deleted = false;
			(*it)->move( time,80);																					// muovi teno a velocità 80 km/h
			if ((*it)->getDir()) {																					//se si muove con direzione positiva
				if ((*it)->getPosition() > (*it)->getNextStation() ) {												//se il treno è arrivato in stazione
					avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
					UPDATEinStazione.push_back((*it));																// aggiungi treno alla lista dei nuovi treni in stazione
					daDepositoInStazione.erase(it);																	//cancella il treno dalla lista
					deleted = true;
				}
			}
			else {
				if ((*it)->getPosition() < (*it)->getNextStation() ) {												//se il treno è arrivato in stazione
					avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
					UPDATEinStazione.push_back((*it));																// aggiungi treno alla lista dei nuovi treni in stazione
					daDepositoInStazione.erase(it);																	//cancella il treno dalla lista
					deleted = true;

				}
			}
			if(!deleted)
				it++;
		}
	}
}
void LineaFerroviaria::avvisoArrivo(Train* t)																	//funzione stampa arrivo di un treno in stazione
{	
	int index = getIndexStazione(t->getNextStation());															//calcola l'indice della stazione
	cout << "Il Treno numero " << t->getId() << " è arrivato nalla stazione " << stazioni[index]->get_name();	//stampa in standard output
	cout << " all'orario "<< print_time(time);;																						//stampa in standard output
																							
	gestioneRitardo(t, index);																					//stampa in standard output ritatdo e lo gestisce
	cout << endl;
}

void LineaFerroviaria::updateliste(){																			//funzione che aggiunge alle liste i nuovi treni
	sumVector(inTransito , UPDATEinTransito);																	//aggiunge al vettore Update e cancella Update
	sumList(inDeposito, UPDATEinDeposito);																		//aggiunge la lista Update e cancella Update
	sumList(daDepositoInStazione, UPDATEdaDepositoInStazione);													//aggiunge la lista Update e cancella Update
	sumList(inStazione, UPDATEinStazione);																		//aggiunge la lista Update e cancella Update
}
void LineaFerroviaria::sumList(list<Train*>& a, list<Train*>& b)										//aggiunge la lista b ad a e cancella b
 {
	for (auto it = b.begin(); it != b.end(); it++){														//scorre la lista b
		a.push_back(*it);																				//carica la lista b in a 
	}
	b.clear();																							// rende b vuoto
}
void LineaFerroviaria::sumVector(vector<Train*>&  a, vector<Train*>& b)									//aggiunge il vector b ad a e cancella b
{
	for (int i = 0; i < b.size(); i++)																	//scrre il vector b
	{
		a.push_back(b[i]);																				//carica il vettore b in a
	}
	b.clear();																							//rende b vuoto
}

void LineaFerroviaria::AvanzaTreniInTransito()
{
	sortTrain(inTransito);																				//oradina il vettore secondo le poszioni dei treni
	

	vector <Train*> treniAndata;																		//crea un vettore destinato ai vettori con direzione positiva
	vector <Train*> treniRitorno;																		//crea un vettore destinato ai vettori con direzione positiva
	for (int i = 0; i < inTransito.size(); i++)															//scorre il vettore
	{
		if (inTransito[i]->getDir())																	//se la direzione è positiva
			treniAndata.push_back(inTransito[i]);														//aggiune al vettore andata
	}
	for (int i = 0; i < inTransito.size(); i++)//scorre il vettore
	{
		if (!inTransito[i]->getDir())//se la direzione è negativa
			treniRitorno.push_back(inTransito[i]);//aggiunge al vettore ritorno

	}
	sortTrain(treniAndata);																				//oradina il vettore secondo le poszioni dei treni
	sortTrain(treniRitorno);																			//oradina il vettore secondo le poszioni dei treni
	//muovi con attenzione alla distanza di sicurezza 10km
	if (treniAndata.size() > 0) {																		// se c'è almeno un elemento
		muoviStampa(treniAndata[treniAndata.size() - 1], -1);											//muovi il primo elemento
		for (int i = treniAndata.size() - 2; i >= 0; i--) {												//scorro il vettore a ritroso partendo
			if (treniAndata[i]->getPosition() > treniAndata[i + 1]->getPosition() - 10) {				//se la distanza dal treno successivo è minore di 10 km
				if (SpeedIsGood(treniAndata[i], treniAndata[i + 1]->getSpeed()))						//se la velocita del treno successiva va bene
					muoviStampa(treniAndata[i], treniAndata[i + 1]->getSpeed());						//pongo la velocita uguale a quella del successivo
				else
					muoviStampa(treniAndata[i], -1);													//muovo il treno a massima velocità
			}
			else
				muoviStampa(treniAndata[i], -1);														//muovo il treno a massima velocità
		}
	}

	if (treniRitorno.size() > 0){																		// se c'è almeno un elemento
		muoviStampa(treniRitorno[0], -1);																//muovi il primo elemento
	for (int i = 1; i < treniRitorno.size(); i++) {														//scorro il vettore
		if (treniRitorno[i]->getPosition() < treniRitorno[i - 1]->getPosition() + 10) {					//se la distanza dal treno successivo è minore di 10 km
			if (SpeedIsGood(treniRitorno[i], treniRitorno[i - 1]->getSpeed()))							//se la velocita del treno successiva va bene
				muoviStampa(treniRitorno[i], treniRitorno[i - 1]->getSpeed());							//pongo la velocita uguale a quella del successivo
			else
				muoviStampa(treniRitorno[i], -1);														//muovo il treno a massima velocità
		}
		else
			muoviStampa(treniRitorno[i], -1);															//muovo il treno a massima velocità
	}
	}

	//constrolla che qualche treno non sia arrivato a 5km di distanza dalla stazione successiva
	for (int i = 0; i < treniAndata.size(); i++)														//scorro il treni in andata
	{
		if (treniAndata[i]->getPosition() > (treniAndata[i]->getNextStation() - 5)) {					//la distanza dalla prossima stazione è minore di 5
			int index = getIndexStazione(treniAndata[i]->getNextStation());								//calcola l'indice della stazione successiva
			if (treniAndata[i]->getIdentificator() > 0 && stazioni[index]->is_local())					//se il treno non è regionale e la stazione è locale
				incrementaLaStazione(treniAndata[i]);													//incrementa la prossima stazione ma non fermare il treno
			else
			{
				treniAndata[i]->setPosition(treniAndata[i]->getNextStation() - 5);						//imposta la posizione esattemente a 5 km dalla stazione
				if (stazioni[index]->is_it_free(true)) {												//se la prossima stazione è libera	
					occupaSegnala(stazioni[index], treniAndata[i], true);								//occupa un binario e ricevi la segnalazione della stazione
					UPDATEdaDepositoInStazione.push_back(treniAndata[i]);								//aggiungi il treno alla lista Update del prossimo stadio
					treniAndata.erase(treniAndata.begin() + i);											//elimina il treno dal vettore
				}
				else {																					// se la stazione è piena
					UPDATEinDeposito.push_back(treniAndata[i]);											//aggiungi il treno alla lista Update del prossimo stadio
					treniAndata.erase(treniAndata.begin() + i);											//elimina il treno dal vettore
				}
			}
		}
	}
	for (int i = 0; i < treniRitorno.size(); i++)
	{
		if (treniRitorno[i]->getPosition() < (treniRitorno[i]->getNextStation() +5)) {					//la distanza dalla prossima stazione è minore di 5		
			int index = getIndexStazione(treniRitorno[i]->getNextStation());							//calcola l'indice della stazione successiva
			if (treniRitorno[i]->getIdentificator() > 0 && stazioni[index]->is_local())					//se il treno non è regionale e la stazione è locale
				incrementaLaStazione(treniRitorno[i]);													//incrementa la prossima stazione ma non fermare il treno
			else
			{
				treniRitorno[i]->setPosition(treniRitorno[i]->getNextStation() + 5);					//imposta la posizione esattamente a 5 km dalla stazione
				if (stazioni[index]->is_it_free(false)) {												//se la prossima stazione è libera
					occupaSegnala(stazioni[index], treniRitorno[i], false);								//occupa un binario e ricevi la segnalazione della stazione
					UPDATEdaDepositoInStazione.push_back(treniRitorno[i]);								//aggiungi il treno alla lista Update del prossimo stadio
					treniRitorno.erase(treniRitorno.begin() + i);										//elimina il treno dal vettore
				}
				else {
					UPDATEinDeposito.push_back(treniRitorno[i]);										//aggiungi il treno alla lista Update del prossimo stadio
					treniRitorno.erase(treniRitorno.begin() + i);										//elimina il treno dal vettore
				}
			}
		}
	}
	
	//copia tutto nel vettore In transito
	inTransito.clear();//svuota il vettore
	for (int i = 0; i < treniAndata.size(); i++)														//scorri vector
	{
		inTransito.push_back(treniAndata[i]);															//inserisci nel nuovo vettore
	}
	for (int i = 0; i < treniRitorno.size(); i++)														//scorri vector
	{
		inTransito.push_back(treniRitorno[i]);															//inserisci nel nuovo vettore
	}
	sortTrain(inTransito);																				//ordina il vettore

}

void LineaFerroviaria::DaStazioneAInTransito()															//gestione treni nei 5 km dopo la stazione
{	if(!daStazioneInTransito.empty())
	{
		auto it = daStazioneInTransito.begin();
		bool deleted = false;
		while ( !daStazioneInTransito.empty() && it != daStazioneInTransito.end() )				//scorri lista
		{
			deleted = false;
			muoviStampa((*it), 80);																			//muovi con velocità 80km/h
			if((*it)->getDir()){																			//se la direzione è positiva
				if((*it)->getPosition() > (*it)->getLastStation()+5){										//se la posizione è maggiore della stazione precedente +5 km
					UPDATEinTransito.push_back((*it));														//inserici il treno nella lista del prossimo stato
					daStazioneInTransito.erase(it);	//elimina il treno da questo stato
					deleted = true;
				}
			}
			else{
				if ((*it)->getPosition() < (*it)->getLastStation() -5) {									//se la posizione è maggiore della stazione precedente +5 km
					UPDATEinTransito.push_back((*it));														//inserici il treno nella lista del prossimo stato
					daStazioneInTransito.erase(it);															//elimina il treno da questo stato
					deleted = true;
				}
			}
			if (!deleted)
				it++;
		}
	}
}
	
bool LineaFerroviaria::allTreniArrived()																//funzione ceh controlla che tutti i treni siano arriavti
{	
	for (auto it = treni.begin(); it != treni.end(); it++) {											//scorri la lista di treni
		if(!((*it)->isArrived(posizioneStazioni)))														//se il treno NON è arrivato
			return false;
	}
	return true;
}

void LineaFerroviaria::occupaSegnala(Stazione* s, Train* t, bool d)										//funzione che occupa un binario della stazione e lo stampa
{
	int a= s->is_arriving(d, t->getIdentificator());//riceve il numero della stazione 1 o 2

	cout << "La stazione "<<s->get_name()<<" segnala al treno " << t->getId() << " di parcheggiarsi al binario ";//stampa in standard output
	if (d)																								// se la direzione è positiva
		cout << a << endl;																				//stampa il numero dinario
	else
		cout << a+2 << endl;																			//stampa il numero dinario
}

bool LineaFerroviaria::SpeedIsGood(Train* t, int newSpeed)
{
	switch (t->getIdentificator())																		//se il tipo del treno
	{
	case 0 :																							//regionale
		if(newSpeed>160)
			return false;
		break;
	case 1 :																							//veloce
		if (newSpeed > 240)
			return false;
		break;
	case 2 :																							//superveloce
		if (newSpeed > 300)
			return false;
		break;
	default:																							//impossibile errore
		throw IllegalArgument();
		break;
	}

	return true;
}

void  LineaFerroviaria::sortTrain(vector<Train*>& v)													//oridna un vector di treni e 
{	
	if (v.size() == 1 || v.size() == 0)																	//controlla che il vettore abbia più di un elemento
		return;
	int min = 0;
	for (int i = 0; i < v.size() - 1; ++i)																//selection sort
	{
		min = i;
		 
		for (int j = i + 1; j < v.size(); ++j) {
		if (v[j]->getPosition() < v[min]->getPosition())
			min = j;
		}
		
		Train* temp =nullptr;
		temp =	v[i];
		v[i] = v[min];
		v[min] = temp;
		//non elimino temp perchè l'oggetto è ancora usato
	}
}

void LineaFerroviaria::exitFromStation(Train* t)//funzione che si usa quando un treno esce dalla stazione STAMPA: Partenza di un treno dalla stazione
{ 
	daStazioneInTransito.push_front(t);																	//inserisce il treno nella lista dello stadio successivo
	incrementaLaStazione(t);																			//incremento la nextStazione del treno uscito dalla stazione
	t->setTime(time);
	t->setParkTime(-1);																		//aggiorna il tempo del treno
	int i = getIndexStazione(t->getLastStation());														//calcola l'indice stazione
	// ADD cout << "Il treno "<<t->getId()<<" esce dalla sazione " << stazioni[i]->get_name() << " alle ore "<< print_time(time); ;		//stampa in standard output
																			
	//gestioneRitardo(t,i);
	//cout << endl;
}


int LineaFerroviaria::getIndexStazione(int distanza)												//calocla l'indice della stazione sapendo la posizione
{
	for (int i = 0; i < posizioneStazioni.size(); i++)												//scorri vettreo poszioneStazioni
	{
		if (posizioneStazioni[i] == distanza)
			return i;
	}
	throw IllegalArgument();
	return 0;
}

void LineaFerroviaria::incrementaLaStazione(Train* t)//incrementa nextSation del treno
{
	bool change = false;//uso questo booleano per evitare di usare return e rendere la rappresentazione con il diagramma di flusso complessa(sapaghetti code)

		if (t->getDir()) {//se la posizione
				for (int i = 0; i < posizioneStazioni.size() - 1 && change == false; i++) {//scorri il vettore poszioneStazioni oppure fermati quando hai trovato l'index
					if (t->getNextStation() == posizioneStazioni[i]) {//se la i-esima stazione è ha la poszione uguale a nextStation
						t->stazioneIncrement(posizioneStazioni[i + 1]);//incremeta la stazione con i+1-esima stazione  
						change = true;
					}
				}
				if (change == false) {//se non è stata incrementa la stazione
						t->stazioneIncrement(posizioneStazioni[(posizioneStazioni.size() - 1)]);//incremeta con l'ultima stazione
						change = true;
					}
				}
		else{
				for (int i = posizioneStazioni.size() - 1 ; i > 0 && change == false; i--) {					//scorri il vettore poszioneStazioni oppure fermati quando hai trovato l'index
					if (t->getNextStation() == posizioneStazioni[i]){											//se la i-esima stazione è ha la poszione uguale a nextStation
						t->stazioneIncrement(posizioneStazioni[i -1]);											//incremeta la stazione con i-1-esima stazione
						change = true;
					}
				}
				if (change == false) {																			//se non è stata incrementa la stazione
					t->stazioneIncrement(posizioneStazioni[0]);													//incremeta con l'ultima stazione
					change = true;
				}
		}

}

void LineaFerroviaria::printTrain(Train* t) {//stampa treno utile per i test

	cout << "ID : " << t->getId() << endl;
	cout << "POSIZIONE : " << t->getPosition() << endl;
	cout << "VELOCITà : " << t->getSpeed() << endl;
	cout << "DIREZIONE : " << t->getDir() << endl;
	//agavazzz::cout << "TEMPO :"<<  t. <<agavazzz::endl;
	cout << "DOVE è FERMO : " << t->whIsStand() << endl;
	cout << "TIPO : " << t->getIdentificator() << endl << endl << endl;

}

void LineaFerroviaria::gestioneRitardo(Train* t, int i){											//fuznione per gestire i ritardi
	int nRitardo = time - t->getOrari()[i];															//nuovo ritardo
	if (nRitardo < 0)																				//se è minore di 0 
		nRitardo = 0;
	if (nRitardo > 0) {//se il ritardo è maggiore di 0
		cout << " con ritardo di " << time - t->getOrari()[i];
		if (time - t->getOrari()[i] == 1)
			cout << " minuto";
		else
			cout << " minuti";
	}
	if (t->getRitardo() > nRitardo)																	//se il ritardo è diminuito
		cout << ", Il ritardo è diminuito";
	else if (t->getRitardo() < nRitardo) {															//se il ritardo è aumentato
		cout << ", Il ritardo è aumentato";
		}
	else																							//se il ritardo è rimasto invariato
		cout << ", Il ritardo è  invariato";
	t->setRitardo(nRitardo);																		//aggiorna il ritardo
	}
	