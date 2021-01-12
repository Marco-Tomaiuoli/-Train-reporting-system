//Studente: Umberto Salviati 1220994


#include "LineaFerroviaria.h"

using namespace std;

LineaFerroviaria::LineaFerroviaria()
{

	openStation("line_description.txt");
	openTrain("timetables.txt");

}

void LineaFerroviaria::start()
{

	time = orario_inizio();
	//lettura file
	spawnTreno();
	while (!allTreniArrived()) {
		if (time == 614) {
			cout << "";
		}
 		time++;
		DaStazioneAInTransito();
		AvanzaTreniInTransito();
		DaDepositoAStazione();
		gestione_depostio();
		gestioneTreniInStazione();
		updateliste();
		spawnTreno();

	}
	
	stampa_ritardi();
	cout << "Stampa timetabele..." << endl << endl;
	stampa_timetable();
	time_table();

}

void LineaFerroviaria::spawnTreno()
{
		
	for (auto it = treni.begin(); it != treni.end(); it++)													//scorri la lista
	{	
		if (time < 1440)																					//controlla che non sia superata la mezzanotte
		{
			if (time == (*it)->getOrari()[0])																//se l'orario di partenza è uguale al tempo
			{
				if ((*it)->getDir())																		//se direzione è positiva
				{
					if (stazioni[0]->is_it_free(true))															//se la stazione è libera
					{
						occupaSegnala(stazioni[0], (*it), true);														//occupa un binario e ricevi la segnalazione della stazione
						avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
						inStazione.push_back((*it));																	//metti il treno nella stazione
					}
					else
					{
						(*it)->setPosition(-5);																			//posiziona il teno a 5km dalla stazione
						inDeposito.push_back(*it);																		//mettilo in deposito
					}
				}

				else																									//se direzione è negativa
				{
					if (stazioni[stazioni.size() - 1]->is_it_free(false))													//se la stazione è libera
					{
						occupaSegnala(stazioni[stazioni.size() - 1], (*it), false);								//occupa un binario e ricevi la segnalazione della stazione
						avvisoArrivo((*it));																	//stampa in standard Arrivo di un treno in stazione
						inStazione.push_back((*it));															//metti il treno nella stazione
					}
					else
					{
						(*it)->setPosition(posizioneStazioni[posizioneStazioni.size() - 1] + 5);				//posiziona il teno a 5km dalla stazione	
						inDeposito.push_back(*it);															//mettilo in deposito
					}
				}
			}
		}
	}
}

void LineaFerroviaria::muoviStampa(Train* t, int v)																//funzione che gestisce il move
{
	bool stampa = t->move(time, v);																				//muovi il treno con velocità v (return seganle)
	if (stampa) {																									//se il treno segnala
		int i = getIndexStazione(t->getNextStation());															//calcola l'index stazione
		cout << "il Treno numero " << t->getId() << " sta arrivando alla stazione " << stazioni[i]->get_name() << " alle  " << print_time(time);	//stampa in standard output
		if (stazioni[i]->is_local() && t->getIdentificator() > 0) {												//controllo se Locale e se treno non è regionale
			cout << ", non fermera' alla stazione " << endl;														//stampa in standard output
			cout << "La stazione non segnala nulla il treno prosegue senza impedimenti nella corsia veloce  " << print_time(time) << endl;
		}//stampa in standard output
		else
			cout << ", si fermera' alla stazione " << endl ;														//stampa in standard output
	}
}

void LineaFerroviaria::DaDepositoAStazione()																	//gestione treni da -5 km dalla posizione della stazione a stazione
{
	if (!daDepositoInStazione.empty())
	{
		auto it = daDepositoInStazione.begin();
		bool deleted = false;
		while (!daDepositoInStazione.empty() && it != daDepositoInStazione.end())						//scorro la lista
		{
			deleted = false;
			(*it)->move(time, 80);																					// muovi teno a velocità 80 km/h
			if ((*it)->getDir()) {																					//se si muove con direzione positiva
				if ((*it)->getPosition() > (*it)->getNextStation()) {												//se il treno è arrivato in stazione
					avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
					UPDATEinStazione.push_back((*it));																// aggiungi treno alla lista dei nuovi treni in stazione
					daDepositoInStazione.erase(it);																	//cancella il treno dalla lista
					it = daDepositoInStazione.begin();																//QUESTO ELEMENTO é UTILE SOLO PER PAR SOCRRERE LA LISTA E NEL MENTRE CANCELLARE ALCUNI DATI
					deleted = true;
				}
			}
			else {
				if ((*it)->getPosition() < (*it)->getNextStation()) {												//se il treno è arrivato in stazione
					avvisoArrivo((*it));																			//stampa in standard Arrivo di un treno in stazione
					UPDATEinStazione.push_back((*it));																// aggiungi treno alla lista dei nuovi treni in stazione
					daDepositoInStazione.erase(it);																	//cancella il treno dalla lista
					it = daDepositoInStazione.begin();
					deleted = true;

				}
			}
			if (!deleted)
				it++;
		}
	}
}
void LineaFerroviaria::avvisoArrivo(Train* t)																	//funzione stampa arrivo di un treno in stazione
{
	int index = getIndexStazione(t->getNextStation());															//calcola l'indice della stazione
	cout << "Il Treno numero " << t->getId() << " e' arrivato nalla stazione " << stazioni[index]->get_name();	//stampa in standard output
	cout << " all'orario " << print_time(time);;																//stampa in standard output

	gestioneRitardo(t, index);																					//stampa in standard output ritatdo e lo gestisce
	cout << endl;
	if (allTreniArrived())															//se è l'ultimo treno chiama comunque last delay
		lastDelay(t);															//gestione del ritardo fianle dell'ultimo treno
}

void LineaFerroviaria::updateliste() {																			//funzione che aggiunge alle liste i nuovi treni
	sumVector(inTransito, UPDATEinTransito);																	//aggiunge al vettore Update e cancella Update
	sumList(inDeposito, UPDATEinDeposito);																		//aggiunge la lista Update e cancella Update
	sumList(daDepositoInStazione, UPDATEdaDepositoInStazione);													//aggiunge la lista Update e cancella Update
	sumList(inStazione, UPDATEinStazione);																		//aggiunge la lista Update e cancella Update
}
void LineaFerroviaria::sumList(list<Train*>& a, list<Train*>& b)										//aggiunge la lista b ad a e cancella b
{
	for (auto it = b.begin(); it != b.end(); it++) {														//scorre la lista b
		a.push_back(*it);																				//carica la lista b in a 
	}
	b.clear();																							// rende b vuoto
}
void LineaFerroviaria::sumVector(vector<Train*>& a, vector<Train*>& b)									//aggiunge il vector b ad a e cancella b
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
				int speed = treniAndata[i + 1]->getSpeed()/2;
				if (SpeedIsGood(treniAndata[i], speed))						//se la velocita del treno successiva va bene
					muoviStampa(treniAndata[i], speed);						//pongo la velocita uguale a quella del successivo
				else
					muoviStampa(treniAndata[i], -1);													//muovo il treno a massima velocità
			}
			else
				muoviStampa(treniAndata[i], -1);														//muovo il treno a massima velocità
		}
	
	}

	if (treniRitorno.size() > 0) {																		// se c'è almeno un elemento
		muoviStampa(treniRitorno[0], -1);																//muovi il primo elemento
		for (int i = 1; i < treniRitorno.size()-1; i++) {														//scorro il vettore
			if (treniRitorno[i]->getPosition() < treniRitorno[i - 1]->getPosition() + 10) {					//se la distanza dal treno successivo è minore di 10 km
				int speed = treniRitorno[i - 1]->getSpeed() / 2;
				if (SpeedIsGood(treniRitorno[i], speed))						//se la velocita del treno successiva va bene
					muoviStampa(treniRitorno[i], speed);							//pongo la velocita uguale a quella del successivo
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
			if (treniAndata[i]->getIdentificator() > 0 && stazioni[index]->is_local() && index != stazioni.size() - 1)					//se il treno non è regionale e la stazione è locale
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
		if (treniRitorno[i]->getPosition() < (treniRitorno[i]->getNextStation() + 5)) {					//la distanza dalla prossima stazione è minore di 5		
			int index = getIndexStazione(treniRitorno[i]->getNextStation());							//calcola l'indice della stazione successiva
			if (treniRitorno[i]->getIdentificator() > 0 && stazioni[index]->is_local() && index != stazioni.size() - 1)					//se il treno non è regionale e la stazione è locale
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
{
	if (!daStazioneInTransito.empty())
	{
		auto it = daStazioneInTransito.begin();
		bool deleted = false;
		while (!daStazioneInTransito.empty() && it != daStazioneInTransito.end())				//scorri lista
		{
			deleted = false;
			muoviStampa((*it), 80);																			//muovi con velocità 80km/h
			if ((*it)->getDir()) {																			//se la direzione è positiva
				if ((*it)->getPosition() > (*it)->getLastStation() + 5) {										//se la posizione è maggiore della stazione precedente +5 km
					UPDATEinTransito.push_back((*it));														//inserici il treno nella lista del prossimo stato
					daStazioneInTransito.erase(it);	//elimina il treno da questo stato
					it = daStazioneInTransito.begin();
					deleted = true;
				}
			}
			else {
				if ((*it)->getPosition() < (*it)->getLastStation() - 5) {									//se la posizione è maggiore della stazione precedente +5 km
					UPDATEinTransito.push_back((*it));														//inserici il treno nella lista del prossimo stato
					daStazioneInTransito.erase(it);															//elimina il treno da questo stato
					it = daStazioneInTransito.begin();
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
		if (!((*it)->isArrived(posizioneStazioni)|| (*it)->getOrari()[0]>=1440))						//se il treno NON è arrivato
			return false;

	}
	return true;
}

void LineaFerroviaria::occupaSegnala(Stazione* s, Train* t, bool d)										//funzione che occupa un binario della stazione e lo stampa
{
	int a = s->is_arriving(d, t->getIdentificator());										//riceve il numero della stazione 1 o 2

	cout << "La stazione " << s->get_name() << " segnala al treno " << t->getId() << " di parcheggiarsi al binario ";//stampa in standard output
	if (d)																								// se la direzione è positiva
		cout << a << endl;																				//stampa il numero dinario
	else
		cout << a + 2 << endl;//stampa il numero dinario

}

bool LineaFerroviaria::SpeedIsGood(Train* t, int newSpeed)
{
	switch (t->getIdentificator())																		//se il tipo del treno
	{
	case 0:																							//regionale
		if (newSpeed > 160)
			return false;
		break;
	case 1:																							//veloce
		if (newSpeed > 240)
			return false;
		break;
	case 2:																							//superveloce
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

		Train* temp = nullptr;
		temp = v[i];
		v[i] = v[min];
		v[min] = temp;
		//non elimino temp perchè l'oggetto è ancora usato
	}
}

void LineaFerroviaria::exitFromStation(Train* t)//funzione che si usa quando un treno esce dalla stazione STAMPA: Partenza di un treno dalla stazione
{
	int binario = stazioni[getIndexStazione(t->getNextStation())]->binario_occupato(t->getDir());
	stazioni[getIndexStazione(t->getNextStation())]->change_status(t->getDir(), binario);				//libera il binario dalla stazione
	daStazioneInTransito.push_front(t);																	//inserisce il treno nella lista dello stadio successivo
	incrementaLaStazione(t);																			//incremento la nextStazione del treno uscito dalla stazione
	t->setTime(time);																					//aggiorna il tempo del treno				
	t->setParkTime(-1);																					//aggiorna il tempo del treno
	int i = getIndexStazione(t->getLastStation());														//calcola l'indice stazione
	cout << "Il treno "<<t->getId()<<" esce dalla sazione " << stazioni[i]->get_name() << " alle ore "<< print_time(time); ;		//stampa in standard output

	//gestioneRitardo(t,i);
	cout << endl;
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
	else {
		for (int i = posizioneStazioni.size() - 1; i > 0 && change == false; i--) {					//scorri il vettore poszioneStazioni oppure fermati quando hai trovato l'index
			if (t->getNextStation() == posizioneStazioni[i]) {											//se la i-esima stazione è ha la poszione uguale a nextStation
				t->stazioneIncrement(posizioneStazioni[i - 1]);											//incremeta la stazione con i-1-esima stazione
				change = true;
			}
		}
		if (change == false) {																			//se non è stata incrementa la stazione
			t->stazioneIncrement(posizioneStazioni[0]);													//incremeta con l'ultima stazione
			change = true;
		}
	}

}

void LineaFerroviaria::gestioneRitardo(Train* t, int i) {											//fuznione per gestire i ritardi
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
		cout << ", Il ritardo e' aumentato";
	}
	else																							//se il ritardo è rimasto invariato
		cout << ", Il ritardo e'  invariato";
	cout << endl;
	t->setRitardo(nRitardo);																		//aggiorna il ritardo
}

void LineaFerroviaria::stampa_ritardi() //fuanzione che stampa i ritardi finali dei treni  INCOLONNATI i commenti sono inutili, ragionamento banale
{
	cout << endl;
	cout << " Stampa dei ritardi...";
	cout << endl;
	cout << endl;
	int l = 1;
	int l2 = 1;
	for (auto it2 = treni.begin(); it2 != treni.end(); it2++)
	{
		int a = (*it2)->getId();
		int i = 0;
		while (a>0) {
			a=a/10;
			i++;
		}
		if (i > l)
			l = i;
	}
	for (auto it2 = treni.begin(); it2 != treni.end(); it2++)
	{
		int a = (*it2)->getRitardo();
		int i = 0;
		while (a > 0) {
			a = a / 10;
			i++;
		}
		if (i > l2)
			l2 = i;
	}
	for (auto it = treni.begin(); it != treni.end(); it++)
	{
		if (!((*it)->getOrari()[0] >= 1440))
		{
			cout << "Il treno di id: ";
			int a = (*it)->getId();
			cout << a;
			int i = 0;
			while (a > 0) {
				a = a / 10;
				i++;
			}
			for (int j = 0; j < l - i; j++)
			{
				cout << " ";

			}
			cout << " il ritardo e' di: ";
			int b = (*it)->getRitardo();
			cout << b;
			if (b == 0)
				b = 1;
			i = 0;
			while (b > 0) {
				b = b / 10;
				i++;
			}
			for (int j = 0; j < l2 - i; j++)
			{
				cout << " ";

			}
			if ((*it)->getRitardo() == 1)
				cout << " minuito ";
			else
				cout << " minuiti ";

			cout << endl;
			
		}

		else{
			cout << "Il treno " << (*it)->getId() << " non e' partito, il suo orario di partenza e' oltre la mezzanotte";
		cout << endl;}
	
	}
	cout << endl; cout << endl;
}