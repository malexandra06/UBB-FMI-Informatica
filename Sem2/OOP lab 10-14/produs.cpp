#include "produs.h"
//#include <exception>
//#include <stdexcept>
#include <iostream>

// Constructor pentru clasa Produs
// Inițializează un produs cu nume, tip, producător și preț
Produs::Produs(const string &nume, const string &tip, const string &producator, const int pret)
{
	this->nume = nume;
	this->tip = tip;
	this->producator = producator;
	this->pret = pret;
}

Produs::~Produs() = default;

Produs::Produs(const Produs& prod){
	this->nume = prod.nume;
	this->tip = prod.tip;
	this->producator = prod.producator;
	this->pret = prod.pret;
}


// Returnează numele produsului
string Produs::getNume() const
{
	return this->nume;
}

// Returnează tipul produsului
string Produs::getTip() const
{
	return this->tip;
}

// Returnează producătorul produsului
string Produs::getProducator() const
{
	return this->producator;
}

// Returnează prețul produsului
int Produs::getPret() const noexcept
{
	return this->pret;
}


// Setează un nou nume pentru produs
void Produs::setNume(const string &newname)
{
	this->nume = newname;
}

// Setează un nou tip pentru produs
void Produs::setTip(const string &newtype)
{
	this->tip = newtype;
}

// Setează un nou producător pentru produs
void Produs::setProducator(const string &newproducer)
{
	this->producator = newproducer;
}

// Setează un nou preț pentru produs
void Produs::setPret(const int newprice) noexcept
{
	this->pret = newprice;
}

// Compară două obiecte de tip Produs și verifică dacă sunt egale
// Returnează true dacă produsele sunt identice, false altfel
bool Produs::equal(const Produs& p) const
{
	return this->getNume() == p.getNume() &&
		this->getTip() == p.getTip() &&
		this->getProducator() == p.getProducator() &&
		this->getPret() == p.getPret();
}
