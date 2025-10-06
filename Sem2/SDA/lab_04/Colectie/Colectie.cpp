#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	//Theta(1)
	return e1 <= e2;
}

Colectie::Colectie() {
	//Theta(cp)
	cp = CAPACITATE;
	elements = new Nod[cp];
	dimensiune = 0;
	prim = ultim = -1;

	for (int i = 0; i < cp - 1; i++)
		elements[i].urmator = i + 1;
	for (int i = 1;i < cp;i++)
		elements[i].anterior = i - 1;
	elements[cp - 1].urmator = elements[0].anterior= - 1;
	primLiber = 0;
}

void Colectie::redimensionare() {
	//Theta(newCp)
	int newCap = cp + 10;
	Nod* newElems = new Nod[newCap];

	for (int i = 0; i < cp; i++) {
		newElems[i] = elements[i];
	}
	for (int i = cp; i < newCap - 1; i++) 
		newElems[i].urmator = i + 1;
	for (int i = cp; i < newCap; i++)
		newElems[i].anterior = i - 1;
	newElems[newCap - 1].urmator = - 1;

	primLiber = cp;
	cp = newCap;
	delete[] elements;
	elements = newElems;
}

void Colectie::adauga(TElem e) {
	//BC: colectia este goala, iar elementul se insereaza pe prima pozitie
	//WC: trebuie redimensionare, iar elementul pe care dorim sa il inseram va fi inserat la final Theta(newCp)+Theta(n)
	//Overall: O(newCp+n) daca luam si WC cu redimensionare, dar daca tinem cont de complexitatea amortizata: O(n)
	if (primLiber == -1)
		redimensionare();
	int poz = primLiber;
	primLiber = elements[poz].urmator;
	elements[poz].e = e;
	elements[poz].urmator = -1;
	elements[poz].anterior = -1;
	if (prim == -1) {
		prim = ultim = poz;
	}
	else {
		int curent = prim;
		int prec = -1;

		while (curent != -1 && rel(elements[curent].e, e)) {
			prec = curent;
			curent = elements[curent].urmator;
		}

		if (curent == prim) {
			elements[poz].urmator = prim;
			elements[prim].anterior = poz;
			prim = poz;
		}
		else if (curent == -1) {
			elements[poz].anterior = ultim;
			elements[ultim].urmator = poz;
			ultim = poz;
		}
		else {
			elements[poz].urmator = curent;
			elements[poz].anterior = prec;
			elements[prec].urmator = poz;
			elements[curent].anterior = poz;
		}
	}
	dimensiune++;
}

bool Colectie::sterge(TElem e) {
	//BC: nu avem elemente in colectie Theta(1)
	//WC: elementul cautat nu se afla in colectie Theta(n)
	//Overall O(n)
	int curent = prim;

	while (curent != -1 && elements[curent].e!=e) {
		curent = elements[curent].urmator;
	}

	if (curent == -1)
		return false;

	if (curent == prim) {
		prim = elements[curent].urmator;
		if (prim != -1)
			elements[prim].anterior = -1;
		else
			ultim = -1;
	}
	else if (curent == ultim) {
		ultim = elements[curent].anterior;
		if (ultim != -1)
			elements[ultim].urmator = -1;
	}
	else {
		int prec = elements[curent].anterior;
		int urm = elements[curent].urmator;
		elements[prec].urmator = urm;
		elements[urm].anterior = prec;
	}

	elements[curent].urmator = primLiber;
	primLiber = curent;
	dimensiune--;
	return true;
}

bool Colectie::cauta(TElem elem) const {
	//BC: elementul cautat este primul in colectie Theta(1)
	//WC: elementul cautat nu se afla in colectie Theta(n)
	//Overall: O(n)
	int curent = prim;
	while (curent != -1) {
		if (elements[curent].e == elem)
			return true;
		curent = elements[curent].urmator;
	}
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	//BC=WC=AC deci Overall Theta(n), n= numarul de elemente din colectie
	int curent = prim;
	int aparitii = 0;
	while (curent != -1) {
		if (elements[curent].e == elem)
			aparitii++;
		curent = elements[curent].urmator;
	}
	return aparitii;
}

int Colectie::transformaInMultime()
{
	//BC: elementele nu trebuie sa mai fie sterse ,colectia e deja multime: Theta(n^2) deoarece si nrAparitii() are theta(n)
	//WC: toate elementele sunt identice Theta(n)*theta(n)(de la nrAparitii)=Theta(n^2)
	//Overall: Theta(n^2)(?)
	int curent = prim;
	int sterse = 0;

	while (curent != -1)
	{
		TElem e = elements[curent].e;
		int nrAp = nrAparitii(e);
		sterse += nrAp - 1;
		for (int i = 1;i <= nrAp;i++)
			curent = elements[curent].urmator;
		for (int i = 1; i < nrAp; i++)
		{
			sterge(e);
		} 
	}

	return sterse;
}

int Colectie::dim() const {
	//Theta(1)
	return dimensiune;
}

bool Colectie::vida() const {
	//Theta(1)
	return prim == -1;
}

IteratorColectie Colectie::iterator() const {
	//Theta(1)
	return IteratorColectie(*this);
}

Colectie::~Colectie() {
	//Theta(1)
	delete[] elements;
}

/*subalgoritm transformaInMultime(Colectie c)
*	curent<-c.prim
*	sterse<-0
*	cat timp curent != -1 executa
*		e<-c.elements[curent].e
*		nrAp<-c.nrAparitii(e)
*		sterse<-sterse+nrAp-1
*		pentru i<-1,nrAp executa
*			curent<-c.elements[curent].urmator
*		pentru i<-1,nrAp-1 executa
*			c.sterge(e)
*	transformaInMultime<-sterse
*/