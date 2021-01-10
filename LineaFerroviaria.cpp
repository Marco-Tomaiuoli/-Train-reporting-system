//Studente: Marco Tomaiuoli 1224262



#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include "LineaFerroviaria.h"

using namespace std;

LineaFerroviaria::~LineaFerroviaria() {
	for (auto s : stazioni)
		delete s;
	for (auto t : treni)
		delete t;
	for (auto d : depositi)
		delete d;
	treni.clear();
	stazioni.clear();
	depositi.clear();
	orari_partenze.clear();
	posizioneStazioni.clear();
	treniIntransito.clear();
	UPDATEinTransito.clear();
	UPDATEinDeposito.clear();
	UPDATEdaDepositoInStazione.clear();
	UPDATEinStazione.clear();
	inTransito.clear();
	inDeposito.clear();
	inStazione.clear();
	daDepositoInStazione.clear();
	daStazioneInTransito.clear();
}

void LineaFerroviaria::openStation(string nome_file) {
	posizioneStazioni.push_back(0);
	ifstream openFile(nome_file);
	if (openFile.is_open()) {
		string line;
		int cont = 0;
		int count = 0;
		while (getline(openFile, line) && line != "") {
			if (cont == 0) {
				Principale* iniziale = new Principale(line);
				stazioni.push_back(iniziale);
				count++;
			}
			else {
				int i = 0;
				while (((line[i] >= 65 && line[i] <= 90) || (line[i] >= 97 && line[i] <= 122)) || line[i] == 130 || line[i] == 133 || line[i] == 138 || line[i] == 141 || line[i] == 162 || line[i] == 32)
					i++;
				string nome_stazione = line.substr(0, i);
				int tipo = stoi(line.substr(i, i + 1));
				int distanza = stoi(line.substr(i + 2, line.length() - 1));
				posizioneStazioni.push_back(distanza);
				if (tipo == 0) {
					Principale* principale = new Principale(nome_stazione, distanza);
					stazioni.push_back(principale);
					count++;
				}
				else {
					Locale* locale = new Locale(nome_stazione, distanza);
					stazioni.push_back(locale);
				}
			}
			cont++;
			n_station = cont;
			n_pstation = count;
		}
		openFile.close();
	}
	else
		cout << "Apertura file non avvenuta correttamente " << endl;
	ordinaStazioni();
	distanze_stazioni();
	for (int i = 0; i < n_station * 2; i++) 
		depositi.push_back(new DepositoTreni());
}

void LineaFerroviaria::openTrain(string nome_file) {
	ifstream openFile(nome_file);
	if (openFile.is_open()) {
		n_treni = count_train(nome_file);
		string line;
		int count = 0;
		while (getline(openFile, line) && line != "") {
			vector<int> orari;
			int i = 0;
			while (line[i] != ' ')
				i++;
			int id_treno = stoi(line.substr(0, i));
			int direzione_partenza = stoi(line.substr(i + 1));
			int tipo_treno = stoi(line.substr(i + 3));
			int cont = i + 5;
			string s;
			while (line[cont] != ' ' && line[cont] != '\0')
				cont++;
			int orarioPartenza = stoi(line.substr(i + 5, cont));
			orari_partenze.push_back(orarioPartenza);
			if (cont == line.size())
				orari.resize(n_station - 1);
			else {
				string orari_stazioni = line.substr(cont + 1, line.length() - 1);
				stringstream stream(orari_stazioni);
				while (getline(stream, orari_stazioni, ' '))
					orari.push_back(stoi(orari_stazioni));
				while (orari.size() < n_station)
					orari.push_back(0);
				if (orari.size() > n_station - 1)
					orari.resize(n_station - 1);
			}
			for (int j = 0; j < orari.size(); j++) {
				if (orari[j] == 0)
					orari[j] = add_time(tipo_treno, posizioneStazioni[j + 1], orarioPartenza, j) + waste;
				else if((orari[j] > add_time(tipo_treno, posizioneStazioni[j + 1], orarioPartenza, j)) || (orari[j] < add_time(tipo_treno, posizioneStazioni[j + 1], orarioPartenza, j)))
					orari[j] = add_time(tipo_treno, posizioneStazioni[j + 1], orarioPartenza, j);
			}
			int posizione_treno = 0;
			if (direzione_partenza == 0)
				posizione_treno = 0;
			else
				posizione_treno = posizioneStazioni[posizioneStazioni.size() - 1];
			vector<int> orario_tot;
			orario_tot.push_back(orarioPartenza);
			for (int i = 0; i < orari.size(); i++) {
				orario_tot.push_back(orari[i]);
			}
			if (tipo_treno == 1) {
				Regionale* regionale = new Regionale(id_treno, direzione_partenza, posizione_treno, orario_tot);
				treni.push_back(regionale);
			}
			else if (tipo_treno == 2) {
				Veloce* veloce = new Veloce(id_treno, direzione_partenza, posizione_treno, orario_tot);
				treni.push_back(veloce);
			}
			else {
				SuperVeloce* superveloce = new SuperVeloce(id_treno, direzione_partenza, posizione_treno, orario_tot);
				treni.push_back(superveloce);
			}
		}
		openFile.close();
	}
	else
		cout << "Apertura file non avvenuta correttamente " << endl;
	
 }

bool LineaFerroviaria::check_time(int time, int type, int distance) {
	if(time == add_time(type, distance, 0, 0))
		return true;
	else
		return false;
}

string LineaFerroviaria::print_time(int time) {
	if (time > 1440)
		time = time - 1440;
	string orario = "";
	int ore = time / 60;
	int minuti = time - (60 * ore);
	if (time % 60 == 0)
		orario = orario + to_string(ore) + ":" + "00";
	else if (ore < 10 && minuti < 10)
		orario = orario + "0" + to_string(ore) + ":" + "0" + to_string(minuti);
	else if (minuti < 10)
		orario = orario + to_string(ore) + ":" + "0" + to_string(minuti);
	else if (ore < 10)
		orario = orario + "0" + to_string(ore) + ":" + to_string(minuti);
	else
		orario = orario + to_string(ore) + ":" + to_string(minuti);
	return orario;
}

int LineaFerroviaria::count_train(std::string) {
	int cont = 0;
	ifstream openFile("treni.txt");
	if (openFile.is_open()) {
		string line;
		while (getline(openFile, line) && line != "")
			cont++;
		openFile.close();
	}
	else
		cout << "Apertura file non avvenuta correttamente " << endl;
	return cont;
}

int	LineaFerroviaria::add_time(int type, int distanza, int orarioPartenza, int esima_stazione) {
	int max_speed = check_speed(type);
	double time = ((static_cast<double>(distanza) - 10.0) / max_speed) * 60.0;
	double time5km = (10.0 / 80) * 60;
	if (type == 1)
		time = time + time5km + time_stop_station;
	else if (!stazioni[esima_stazione]->is_local())
		time = time + time5km + time_stop_station;
	else
		time = time + time5km;
	return round(time) + orarioPartenza;
}

int LineaFerroviaria::check_speed(int type) {
	int speed = 0;
	if (type == 1)
		speed = 160;
	else if (type == 2)
		speed = 240;
	else
		speed = 300;
	return speed;
}

void LineaFerroviaria::treni_in_deposito() {
	Train* treno = nullptr;
	int index = 0;
	for (int i = 0; i < depositi.size(); i++) {
		treno = depositi[i]->prossimo_uscire();
		if (index >= stazioni.size()) 
			index = 0;
		if (stazioni[index]->is_it_free(treno->getDir())) {
			occupaSegnala(stazioni[index], treno, treno->getDir());
			UPDATEdaDepositoInStazione.push_back(depositi[i]->elimina_treno());
		}
		index++;
	}
}

void LineaFerroviaria::posiziona_treni() {
	int index = 0;
	for (int i = 0; i < depositi.size(); i++) {
		if (index >= stazioni.size())
			index = 0;
		if (inDeposito.front()->getDir())
			inDeposito.front()->parcheggia(false, posizioneStazioni[index - 5]);
		else
			inDeposito.front()->parcheggia(false, posizioneStazioni[index + 5]);
		depositi[i]->posiziona_treno(inDeposito.front());
		inDeposito.pop_front();
	}
}

void LineaFerroviaria::gestione_depostio() {
	posiziona_treni();
	treni_in_deposito();
}

void LineaFerroviaria::ordinaStazioni() {
	sort(posizioneStazioni.begin(), posizioneStazioni.end());
	sort(stazioni.begin(), stazioni.end(), check_distance);
}

void LineaFerroviaria::distanze_stazioni() {
	for (int i = 1; i < stazioni.size(); i++) {
		if (posizioneStazioni[i] - posizioneStazioni[i - 1] < 20) {
			posizioneStazioni.erase(posizioneStazioni.begin() + i); 
			auto it = stazioni.begin() + i;
			delete *it;
			stazioni.erase(it);
			i--;
		}
	}
	n_pstation = 0;
	n_station = stazioni.size();
	for (auto s : stazioni)
		if (!s->is_local())
			n_pstation++;
}

void LineaFerroviaria::stampa_timetable() {
	int i = 0;
	for (auto treno : treni) {
		cout << "Identificatore del treno: " << treno->getId() << " Direzione: " << treno->getDir() << " Tipo: " << cambia_tipo(treno->getIdentificator()) << " Orario partenza: " << print_time(orari_partenze[i]) << " Orari di arrivo nelle stazioni: " << stampa_orari(somma_orari(treno->getOrari())) << endl;
		i++;
	}
}

string LineaFerroviaria::cambia_tipo(int tipo) {
	if (tipo == 0)
		return "Regionale";
	else if (tipo == 1)
		return "Alta velocita'";
	else
		return "Alta veocita' super";
}

string LineaFerroviaria::stampa_orari(std::vector<int> v) {
	string s = "";
	for (int i = 1; i < v.size(); i++)
		s = s + print_time(v[i]) + " ";
	return s;
}

vector<int> LineaFerroviaria::somma_orari(vector<int> v) {
	int partenza = v[0];
	for (int i = 1; i < v.size(); i++)
		v[i] = v[i] + partenza;
	return v;
}

bool LineaFerroviaria::check_distance(Stazione* stazione1, Stazione* stazione2) {
	return (stazione1->get_distance() < stazione2->get_distance());
}

int LineaFerroviaria::orario_inizio() {
	int cont = orari_partenze[0];
	for (int i = 1; i < orari_partenze.size(); i++)
		if (orari_partenze[i] < cont)
			cont = orari_partenze[i];
	return cont - 1;
}

