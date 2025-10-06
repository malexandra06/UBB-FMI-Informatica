#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	curent = c.prim;
}

TElem IteratorColectie::element() const{
	return col.elements[curent].e;
}

bool IteratorColectie::valid() const {
	return curent!=-1;
}

void IteratorColectie::urmator() {
	curent = col.elements[curent].urmator;
}

void IteratorColectie::prim() {
	curent = col.prim;
}
