#include "RepoCos.h"
#include <random> 
#include <algorithm>
#include "exception.h"

void RepoCos::adaugaCos(const Produs& p) {
	if (find(p.getNume()) == -1)
	{
		this->cosCumparaturi.push_back(p);
		this->sumaTotala += p.getPret();
	}
	else
		throw RepoCosException("Produs deja existent in cos!\n");
}

void RepoCos::golesteCos() {
	this->cosCumparaturi.clear();
	this->sumaTotala = 0;
}

void RepoCos::sterge(const string& nume)
{
	this->sumaTotala -= cosCumparaturi[find(nume)].getPret();
	this->cosCumparaturi.erase(cosCumparaturi.begin() + this->find(nume));
}

void RepoCos::adaugaRandom(const int nr, vector<Produs> listaProd) {
	vector<Produs> aux;
	shuffle(listaProd.begin(), listaProd.end(), std::default_random_engine(std::random_device{}()));
	while ((this->cosCumparaturi.size() < nr) && (listaProd.size() > 0)) {
		this->cosCumparaturi.push_back(listaProd.back());
		this->sumaTotala += listaProd[listaProd.size() - 1].getPret();
		aux.push_back(listaProd.back());
		listaProd.pop_back();
		if (listaProd.size() == 0 && this->cosCumparaturi.size() < nr) {
			listaProd = aux;
			aux.clear();
			shuffle(listaProd.begin(), listaProd.end(), std::default_random_engine(std::random_device{}()));
		}
	}
}

int RepoCos::find(const string& name)const{
	auto it = find_if(this->cosCumparaturi.begin(),
		this->cosCumparaturi.end(),
		[name](const Produs& p)
		{ if (p.getNume() == name)
		return true;return false;});
	const int poz = static_cast<int>(std::distance(this->cosCumparaturi.begin(), it));
	if (it != this->cosCumparaturi.end()) //verific daca e la sf
		return poz;
	return -1;
}
vector <Produs>& RepoCos::getAll(){
	return this->cosCumparaturi;
}

int RepoCos::getSuma()const
{
	return this->sumaTotala;
}