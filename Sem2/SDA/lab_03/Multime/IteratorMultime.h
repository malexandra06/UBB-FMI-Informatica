#pragma once
#include "Nod.h"
class Nod;
class Multime;
typedef int TElem;


class IteratorMultime
{
	friend class Multime;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	const Multime& multime;
	/* aici e reprezentarea  specifica a iteratorului */
	PNod curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//modifica elementul curent referit de iterator ca fiind elementul anterior din multime,sau,in cazul 
		//in care elementul curent a fost primul,transforma iteratorul in unul nevalid
		// arunca exceptie in cazul in care iteratorul nu este valid
		void anterior();


		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};
