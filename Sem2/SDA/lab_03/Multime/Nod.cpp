#include "Nod.h"

Nod::Nod(TElem e, PNod urm) {
	//Theta(1)
	this->e = e;
	this->urm = urm;
}

TElem Nod::element() {
	//Theta(1)
	return e;
}

PNod Nod::urmator() {
	//Theta(1)
	return urm;
}
