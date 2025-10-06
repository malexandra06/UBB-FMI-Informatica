#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"
#include <exception>
void testAnterior()
{
	Multime m;
	m.adauga(3);
	m.adauga(7);
	m.adauga(2);
	m.adauga(1);
	IteratorMultime im = m.iterator();
	assert(im.valid() == true);
	im.urmator();
	im.urmator();
	im.urmator();
	TElem elem = im.element();
	assert(elem == 3);
	im.anterior();
	elem = im.element();
	assert(elem == 7);
	im.anterior();
	elem = im.element();
	assert(elem == 2);
	im.anterior();
	elem = im.element();
	assert(elem == 1);
	im.anterior();
	assert(im.valid()==false);
	try {
		im.anterior();
		assert(false);
	}
	catch (std::exception) {
		assert(true);
	}

}

void testAll() { //apelam fiecare functie sa vedem daca exista
	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5)==true);
	assert(m.adauga(1)==true);
	assert(m.adauga(10)==true);
	assert(m.adauga(7)==true);
	assert(m.adauga(1)==false);
	assert(m.adauga(10)==false);
	assert(m.adauga(-3)==true);
	assert(m.dim() == 5);
	assert(m.cauta(10) == true);
	assert(m.cauta(16) == false);
	assert(m.sterge(1) == true);
	assert(m.sterge(6) == false);
	assert(m.dim() == 4);


	IteratorMultime im = m.iterator();
	im.prim();
	int s = 0;
	while (im.valid()) {
		TElem e = im.element();
		s += e;
		im.urmator();
	}
	assert(s == 19);

}
