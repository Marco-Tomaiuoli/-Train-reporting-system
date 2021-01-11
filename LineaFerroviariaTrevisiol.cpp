#include "LineaFerroviaria.h"


void LineaFerroviaria::gestioneTreniInStazione(){
	if(!inStazione.empty())
	{
		auto it = inStazione.begin();
		
		while ( !inStazione.empty() && it != inStazione.end() )				//scorri lista
		{
			
														
			if((*it)->getParkTime()==-1){	
				int set = (*it)->getNextStation();
				(*it)->parcheggia(1, set);
				bool change = false;

				if(!daStazioneInTransito.empty())
				{
					auto prev = daStazioneInTransito.begin();

					while(prev != daStazioneInTransito.end()&& !daStazioneInTransito.empty()){
						if((*prev)->getLastStation()==set)
							if((*it)->getDir())
								if ((*prev)->getPosition() < (*prev)->getLastStation()+10)
								{
									int prev_train_speed = (*prev)->getIdentificator();
									prev_train_speed =check_speed(prev_train_speed+1);
									int time = 4 + ceil((5 / prev_train_speed) * 60);
									(*it)->setParkTime(time);
									change = true;
								}
								else {
									if ((*prev)->getPosition() < (*prev)->getLastStation() - 10)
									{
										int prev_train_speed = (*prev)->getIdentificator();
										prev_train_speed = check_speed(prev_train_speed + 1);
										int time = 4 + ceil((5 / prev_train_speed) * 60);
										(*it)->setParkTime(time);
										change = true;
									}
								
								}
						prev++;

					}

					if(change ==false)
					{
						if((*it)->isArrived(posizioneStazioni))
							(*it)->setParkTime(0);
						else
							(*it)->setParkTime(5);	
					}
				}

				else
					(*it)->setParkTime(5);
			}
			
			else{
				(*it)->decremetParkTime();
			}
			
			it++;
		}
	



		for (int i = 0; i < stazioni.size(); i++) {
			std::list<Train*> leaving;
			for (auto ite = inStazione.begin(); ite != inStazione.end(); ite++) {
				int indDiSta = getIndexStazione((*ite)->getNextStation());
				if ((*ite)->getParkTime() == 0 && (*ite)->getDir()&& indDiSta == i)
				{
						leaving.push_back(*ite);
				}
			}
			if(!leaving.empty())
				let_the_train_start(leaving);
		}
		for (int i = 0; i < stazioni.size(); i++) {
			std::list<Train*> leaving;
			for (auto ite = inStazione.begin(); ite != inStazione.end(); ite++) {
				int indDiSta = getIndexStazione((*ite)->getNextStation());
				if ((*ite)->getParkTime() == 0 && !(*ite)->getDir() && indDiSta == i)
				{
						leaving.push_back(*ite);

				}
			}
			if (!leaving.empty())
				let_the_train_start(leaving);
		}

		it = inStazione.begin();
		while (!inStazione.empty() && it != inStazione.end()) {
			if ((*it)->getParkTime() == -1) {
				inStazione.erase(it);
				it = inStazione.begin();
			}
			else
				it++;
		}



	}
	
	
	

}






/*

void LineaFerroviaria::in_Stazione()
{
	if(!inStazione.empty())
	{
	auto it = inStazione.begin();

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
		else
			(*it)->setParkTime(5);
	}
	else {
		(*it)->decremetParkTime();
	}
	trenoInPartenza(inStazione);
	}
}

void LineaFerroviaria::trenoInPartenza(std::list<Train*>& leaving_train)
{
	auto it = leaving_train.begin();
	bool to_continue = true;
	while (to_continue && it != leaving_train.end())
	{
		if ((*it)->getParkTime() == 0)
		{
			let_the_train_start(leaving_train);
			to_continue = false;// TODO forse sbagliato
		}
	}
}*/

void LineaFerroviaria::let_the_train_start(std::list<Train*>& leaving_train)
{
	auto iteratore = leaving_train.begin();
	Train* it = (*iteratore);
	int priority = (it)->getIdentificator();
	int direction = (it)->getDir();
	int position = (it)->getNextStation();
	int index = getIndexStazione(position);
	if (leaving_train.size()>1)
	{
		auto to_delete = iteratore;
		Train* second_train = *(iteratore++);
		if (priority < (*second_train).getIdentificator())
		{
			int temp = (it)->getParkTime();
			int prev_train_speed = (second_train)->getSpeed();
			int time = 4 + ceil((5 / prev_train_speed) * 60);
			(it)->setParkTime(temp + time);
			if ((second_train)->isArrived(posizioneStazioni))
			{	
				// TODO correggi cout
					lastDelay(second_train);
			}
			else
			{
				exitFromStation(second_train);
			}
		}
		else
		{	
			int temp = (second_train)->getParkTime();
			int prev_train_speed = (*to_delete)->getSpeed();
			int time = 4 + ceil((5 / prev_train_speed) * 60);
			(second_train)->setParkTime(temp + time);

			if ((*to_delete)->isArrived(posizioneStazioni))
				lastDelay(*to_delete);
			else
			{
				exitFromStation(*to_delete);
			}
		}
	}
	else {
		if ((*iteratore)->isArrived(posizioneStazioni))
			lastDelay(*iteratore);
		else
			exitFromStation(*iteratore);
	}



}

Train* LineaFerroviaria::get_train(std::list<Train*>& leaving_train, int stazione, std::list<Train*>::iterator& da_cancellare)
{
	Train* ritorno = nullptr;
	ritorno = *leaving_train.begin();
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
	int schedule = copia[copia.size()-1];
	delay = time - schedule;
	if (delay <= 0)
	{
		std::cout << " e' in orario\n" << std::endl;
	}
	else {
		std::cout << " e' in ritardo di " << delay << " minuti.\n" << std::endl;
	}

}
