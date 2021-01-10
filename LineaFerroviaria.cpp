#include "LineaFerroviaria.h"

void LineaFerroviaria::inStazione()
{
	auto it = InStazione.begin();

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
	trenoInPartenza(InStazione);
}

void LineaFerroviaria::trenoInPartenza(std::list<Train*>& leaving_train)
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
}

void LineaFerroviaria::let_the_train_start(std::list<Train*>& leaving_train)
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

void LineaFerroviaria::lastDelay(Train* t)
{
	std::cout << "Il treno " << t->getId();
	int delay = 0;
	std::vector<int> copia = t->getOrari();
	int schedule = copia[t->getNextStation()];
	delay = time - schedule;
	if (delay <= 0)
	{
		std::cout << " e' in orario\n" << std::endl;
	}
	else {
		std::cout << " e' in ritardo di " << delay << " minuti.\n" << std::endl;
	}

}
