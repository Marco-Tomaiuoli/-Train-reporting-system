#include "LineaFerroviaria.h"
void LineaFerroviaria::creaLineaFerroviaria()
{
	Locale* st_1 = new Locale("Altavilla", 3);
	stazioni.push_back(st_1);
	Principale* st_2 = new Principale("Vicenza", 20);
	stazioni.push_back(st_2);
	DepositoTreni* dt_1 = new DepositoTreni();
	st_1->is_arriving(0, 0);
}

int LineaFerroviaria::getIndexStazione(int distanza)
{ 
	std::vector <int> posizioneStazioni{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	for (int i = 0; i < posizioneStazioni.size(); i++) 
	{ 
		if (posizioneStazioni[i] == distanza)             
			return i; 
	}
	throw IllegalArgument();     
	return 0; 
}

void LineaFerroviaria::inStazione(std::list<Train*> treni_in_stazione)
{
	auto it = treni_in_stazione.begin();

	if ((*it)->getParkTime() == -1)
	{
		int set = (*it)->getNextStation();
		(*it)->parcheggia(1, set);

		std::list<Train*>::iterator prev = daStazioneInTransito.begin();
		if (prev != daStazioneInTransito.end())
		{
			int prev_train_speed = (*prev)->getSpeed(); 
			int time = 4 + ceil((5 / prev_train_speed) * 60);
			(*it)->setParkTime(time);
		}
	}
	else {
		(*it)->decremetParkTime();
	}
}

void LineaFerroviaria::trenoInPartenza(std::list<Train*> leaving_train)
{
	auto it = leaving_train.begin();
	
	bool to_continue = true;
	while (to_continue && it != leaving_train.end())
	{
		if ((*it)->getParkTime() == -1)
		{
			let_the_train_start(leaving_train);
			to_continue = false;
		}
	}
	lastDelay((*it));
}

void LineaFerroviaria::let_the_train_start(std::list<Train*> leaving_train)
{
	Locale* st1 = new Locale("Vi", 10);
	stazioni.push_back(st1);
	auto iteratore = leaving_train.begin();
	Train* it = (*iteratore);
	int priority = (it)->getIdentificator();
	int direction = (it)->getDir();
	int position = (it)->getNextStation();
	bool what_to_do = (*stazioni[position]).present_train(direction);//errore
	if (what_to_do)
	{
		auto to_delete = leaving_train.end();
		Train* second_train = get_train(leaving_train, position, to_delete);
		if (priority < (*second_train).getIdentificator())
		{
			int temp = (it)->getParkTime();
			int prev_train_speed = (second_train)->getSpeed();
			int time = 4 + ceil((5 / prev_train_speed) * 60);
			(it)->setParkTime(temp + temp);
			if ((it)->getNextStation() == 0 || (it)->getNextStation() == (stazioni.size() - 1))
			{
				lastDelay(*to_delete);
				leaving_train.erase(to_delete);
			}
			else
			{
				exitFromStation(*to_delete);
				leaving_train.erase(to_delete);
			}
		}
		else
		{
			if ((it)->getNextStation() == 0 || (it)->getNextStation() == (stazioni.size() - 1))
				leaving_train.pop_front();
			else
			{
				exitFromStation(it);
				leaving_train.pop_front();
			}
		}
	}
}

Train* LineaFerroviaria::get_train(std::list<Train*>& leaving_train, int stazione, std::list<Train*>::iterator& da_cancellare)
{
	Train* ritorno = nullptr;
	std::list<Train*> copia = leaving_train;
	copia.pop_front();
	for (auto it = (copia.begin()); it != copia.end(); it++)
	{
		if ((*it)->getNextStation() == stazione)
		{
			da_cancellare = it;
			ritorno = (*it);
		}
	}
	return ritorno;
}

void LineaFerroviaria::exitFromStation(Train* t)
{ 
	daStazioneInTransito.push_front(t);
	incrementaLaStazione(t);
	int i = getIndexStazione(t->getLastStation());
	std::cout << "Il treno " << t->getId() << " esce dalla sazione " << stazioni[i]->get_name() << " alle ";
	//print_time(time);
	//gestioneRitardo(t, i);
	std::cout << std::endl;
}

void LineaFerroviaria::incrementaLaStazione(Train* t)
{
	bool change = false;

	if (t->getDir()) {
		for (int i = 0; i < posizioneStazioni.size() - 1 && change == false; i++) {
			if (t->getNextStation() == posizioneStazioni[i]) {
				t->stazioneIncrement(posizioneStazioni[i + 1]);
				change = true;
			}
		}
		if (change == false) {
			t->stazioneIncrement(posizioneStazioni[(posizioneStazioni.size() - 1)]);
			change = true;
		}
	}
	else {
		for (int i = posizioneStazioni.size() - 1; i > 0 && change == false; i--) {

			if (t->getNextStation() == posizioneStazioni[i]) {
				t->stazioneIncrement(posizioneStazioni[i - 1]);
				change = true;
			}
		}
		if (change == false) {
			t->stazioneIncrement(posizioneStazioni[0]);
			change = true;
		}
	}
}

void LineaFerroviaria::lastDelay(Train* t)
{
	std::cout << "Il treno " << t->getId();
	int delay = 0;
	std::vector<int> copia = t->getOrari();
	int schedule = copia[t->getNextStation()];
	delay = time - schedule;
	if (delay <= 0)
	{
		std::cout << " e' in orario\n"<<std::endl;
	}
	else {
		std::cout << " e' in ritardo di " << delay << " minuti.\n" << std::endl;
	}
	 
}

int main()
{
	std::vector<int> orari_1{ 0, 3600 };
	Veloce* treno_1 = new Veloce(342, 1, 0, orari_1);
	
	std::list<Train*> lista_treni;
	lista_treni.push_back(treno_1);
	std::cout << "Legen" << std::endl;
	std::cout << "Wait for it..."<<std::endl;
	
	LineaFerroviaria lf;
	lf.inStazione(lista_treni);
	lf.trenoInPartenza(lista_treni);
	std::cout << "dary" << std::endl;
	delete treno_1;
	return 0;
}
//...
	//treniDaStazioneAtranisto.push_front(treno che esce)
	//quando faccio l'erase mi salvo il tempo_ultimo_treno e lo sommo ai tempi dei treni della lista  