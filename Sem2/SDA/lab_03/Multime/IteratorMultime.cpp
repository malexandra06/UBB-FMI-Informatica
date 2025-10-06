#include "IteratorMultime.h"
#include "Multime.h"
#include "Nod.h"
#include <exception>

IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	//Theta(1)
	curent = m.prim;
}


void IteratorMultime::prim() {
	//Theta(1)
	curent = multime.prim;
}


void IteratorMultime::urmator() {
	//Theta(1)
	curent = curent->urmator();
}

void IteratorMultime::anterior()
{
	//BC: iteratorul nu este valid sau pointeaza spre primul element theta(1)
	//WC: iteratorul pointeaza catre ultimul element theta(n)
	//Overall: O(n)
	if (!valid())
		throw std::exception("Iterator invalid!");
	else if (curent == multime.prim)
		curent = nullptr;
	else
	{
		PNod it = multime.prim;
		PNod ant = nullptr;
		while (it != curent)
		{
			ant = it;
			it = it->urmator();
		}
		curent = ant;
	}
}

TElem IteratorMultime::element() const {
	//Theta(1)
	return curent->element();
}

bool IteratorMultime::valid() const {
	//Theta(1)
	if(curent==nullptr)
		return false;
	return true;
}


/*subalgoritm anterior(IteratorMultime curent,Multime m)
* 
* daca !valid(curent) atunci 
*	@se arunca exceptie 
* altfel daca curent=m.prim atunci
*	curent<-null
* altfel
*	it<-m.prim
*	ant<-null
*	cat timp it!=curent executa
*		ant<-it
*		it<-it.urmator()
*	curent<-ant
*/