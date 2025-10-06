#include "TestScurt.h"
#include "Colectie.h"
#include "IteratorColectie.h"
#include <assert.h>
#include <iostream>
void testAll() {
	Colectie c;
	c.adauga(5);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);

	assert(c.dim() == 6);
	assert(c.nrAparitii(5) == 2);

	assert(c.sterge(5) == true);
	assert(c.dim() == 5);

	assert(c.cauta(6) == true);
	assert(c.vida() == false);

	IteratorColectie ic = c.iterator();
	assert(ic.valid() == true);
	while (ic.valid()) {
		ic.element();
		ic.urmator();
	}
	assert(ic.valid() == false);
	ic.prim();
	assert(ic.valid() == true);

}

void testMultime() {
	Colectie c;
	c.adauga(5);
	c.adauga(8);
	c.adauga(8);
	c.adauga(6);
	c.adauga(0);
	c.adauga(5);
	c.adauga(10);
	c.adauga(8);
	c.adauga(0);
	c.adauga(5);
	int nr = c.transformaInMultime();
	assert(nr == 5);
	assert(c.dim() == 5);
	assert(c.nrAparitii(5) == 1);
	assert(c.nrAparitii(8) == 1);
	assert(c.nrAparitii(6) == 1);
	assert(c.nrAparitii(0) == 1);
	assert(c.nrAparitii(10) == 1);
	IteratorColectie ic = c.iterator();
	assert(ic.element() == 0);
	ic.urmator();
	assert(ic.element() == 5);
	ic.urmator();
	assert(ic.element() == 6);
	ic.urmator();
	assert(ic.element() == 8);
	ic.urmator();
	assert(ic.element() == 10);
}