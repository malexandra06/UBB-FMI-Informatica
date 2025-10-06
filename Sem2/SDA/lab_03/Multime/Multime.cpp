#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

Multime::Multime() {
	///Theta(1)
	this->prim = nullptr;
	this->dimensiune = 0;
}


bool Multime::adauga(TElem elem) {
	///BC: elementul se afla pe prima pozitie in multime si nu mai trebuie adaugat: Theta(1)
	///WC: elementul nu se afla in multime si il adaugam: Theta(n)-de la functia de cautare
	/// Overall: O(n)
	if (this->cauta(elem))
		return false;
	PNod q = new Nod(elem, this->prim);
	this->prim = q;
	dimensiune++;
	return true;
}


bool Multime::sterge(TElem elem) {
	///BC:elementul care urmeaza sa fie sters este primul: Theta(1)
	///WC: elementul care urmeaza sa fie sters nu e in multime: Theta(n)
	///Overall: O(n)
	PNod p = prim;
	PNod anterior = nullptr;
	while (p != nullptr && p->e != elem) {
		anterior = p;
		p = p->urm;
	}
	if (p == nullptr)
		return false; // nu am gasit elementul
	if (anterior == nullptr) {
		// stergem primul nod
		prim = prim->urm;
	}
	else {
		anterior->urm = p->urm;
	}
	delete p;
	dimensiune--;
	return true;
}


bool Multime::cauta(TElem elem) const {
	///BC: elementul cautat este primul din multime Theta(1)
	///WC: elementul cautat nu se afla in multime Theta(n)
	///Overall: O(n)
	PNod p = prim;
	while (p != nullptr) {
		if (p->e == elem)
			return true;
		p = p->urm;
	}
	return false;
}


int Multime::dim() const {
	///Theta(1)
	return dimensiune;
}

bool Multime::vida() const {
	///Theta(1)
	if(dimensiune==0)
		return true;
	return false;
}


Multime::~Multime() {
	///Theta(n)
	while (this->prim != nullptr) {
		PNod p = this->prim;
		this->prim = this->prim->urm;
		delete p;
	}
}



IteratorMultime Multime::iterator() const {
	//Theta(1)
	return IteratorMultime(*this);
}

