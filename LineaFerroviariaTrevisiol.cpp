//Studente: Riccardo Trevisiol 1216353


#include "LineaFerroviaria.h"


void LineaFerroviaria::gestioneTreniInStazione()
{
	if (!inStazione.empty())
	{
		auto it = inStazione.begin();

		while (!inStazione.empty() && it != inStazione.end())										//scorre la lista
		{


			if ((*it)->getParkTime() == -1)
			{															//se il treno è in arrivo in stazione(parktime =-1) imporsto il tempoo minimo d'attesa
				int set = (*it)->getNextStation();
				(*it)->parcheggia(1, set);
				bool change = false;

				if (!daStazioneInTransito.empty())													//controllo che la lista non sia vuota
				{
					auto prev = daStazioneInTransito.begin();

					while (prev != daStazioneInTransito.end() && !daStazioneInTransito.empty())		//imposta il nuovo tempo d'attesa nel caso in cui un treno abbia appena lasciato la stazione
					{
						if ((*prev)->getLastStation() == set)
							if ((*it)->getDir())
								if ((*prev)->getPosition() < (*prev)->getLastStation() + 10)
								{
									int prev_train_speed = (*prev)->getIdentificator();
									prev_train_speed = check_speed(prev_train_speed + 1);
									int time = 4 + ceil((5 / prev_train_speed) * 60);
									(*it)->setParkTime(time);
									change = true;
								}
								else
								{
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

					if (change == false)
					{
						if ((*it)->isArrived(posizioneStazioni))
							(*it)->setParkTime(0);
						else
							(*it)->setParkTime(4);
					}
				}

				else
					(*it)->setParkTime(4);
			}

			else
			{
				(*it)->decremetParkTime();
			}

			it++;
		}

		for (int i = 0; i < stazioni.size(); i++) 			//fa partire il treno 
		{
			std::list<Train*> leaving;
			for (auto ite = inStazione.begin(); ite != inStazione.end(); ite++)
			{
				int indDiSta = getIndexStazione((*ite)->getNextStation());
				if ((*ite)->getParkTime() == 0 && (*ite)->getDir() && indDiSta == i)
				{
					leaving.push_back(*ite);
				}
			}
			if (!leaving.empty())
				let_the_train_start(leaving);
		}
		for (int i = 0; i < stazioni.size(); i++)
		{
			std::list<Train*> leaving;
			for (auto ite = inStazione.begin(); ite != inStazione.end(); ite++)
			{
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
		while (!inStazione.empty() && it != inStazione.end())
		{
			if ((*it)->getParkTime() == -1)
			{
				inStazione.erase(it);
				it = inStazione.begin();
			}
			else
				it++;
		}
	}
}


void LineaFerroviaria::let_the_train_start(std::list<Train*>& leaving_train)		//funzione che chiama la funzione exitFromStation, che carica il treno che deve partire nella lista dei treni in transito  
{
	auto iteratore = leaving_train.begin();
	int priority = (*iteratore)->getIdentificator();
	int direction = (*iteratore)->getDir();
	int position = (*iteratore)->getNextStation();
	int index = getIndexStazione(position);
	if (leaving_train.size() > 1)
	{
		auto to_delete = iteratore;
		Train* second_train = *(std::next(leaving_train.begin()));
		if (priority < (*second_train).getIdentificator())
		{
			int temp = (*iteratore)->getParkTime();
			int prev_train_speed = check_speed((second_train)->getIdentificator() + 1);
			int time = 4 + ceil((5 / prev_train_speed) * 60);
			(*iteratore)->setParkTime(temp + time);
			if ((second_train)->isArrived(posizioneStazioni))
			{
				int binario = stazioni[getIndexStazione((second_train)->getNextStation())]->binario_occupato((second_train)->getDir());
				stazioni[getIndexStazione((second_train)->getNextStation())]->change_status((second_train)->getDir(), binario);
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
			int prev_train_speed = check_speed((*to_delete)->getIdentificator() + 1);
			int time = 4 + ceil((5 / prev_train_speed) * 60);
			(second_train)->setParkTime(temp + time);

			if ((*to_delete)->isArrived(posizioneStazioni))
			{
				lastDelay(*to_delete);
				int binario = stazioni[getIndexStazione((*to_delete)->getNextStation())]->binario_occupato((*to_delete)->getDir());
				stazioni[getIndexStazione((*to_delete)->getNextStation())]->change_status((*to_delete)->getDir(), binario);
			}
			else
			{
				exitFromStation(*to_delete);

			}
		}
	}
	else {
		if ((*iteratore)->isArrived(posizioneStazioni))
		{
			int binario = stazioni[getIndexStazione((*iteratore)->getNextStation())]->binario_occupato((*iteratore)->getDir());
			stazioni[getIndexStazione((*iteratore)->getNextStation())]->change_status((*iteratore)->getDir(), binario);
			lastDelay(*iteratore);
		}
		else
			exitFromStation(*iteratore);
	}
}

void LineaFerroviaria::lastDelay(Train* t)				//stampa ad output il ritardo finale di ogni treno una volta che questo è arrivato al capolinea 
{
	std::cout << "Il treno " << t->getId();
	int delay = 0;
	std::vector<int> copia = t->getOrari();
	int schedule = copia[copia.size() - 1];
	delay = time - schedule;
	if (delay <= 0)
	{
		t->setRitardo(0);
		std::cout << " e' in orario\n" << std::endl;
	}
	else {
		t->setRitardo(delay);
		std::cout << " e' in ritardo di " << delay << " minuti.\n" << std::endl;
	}

}