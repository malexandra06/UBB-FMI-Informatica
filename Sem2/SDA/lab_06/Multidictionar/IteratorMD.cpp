#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	curent = 0;
}

TElem IteratorMD::element() const{
	if (this->valid()) {
		return md.tabelaDispersie[curent];
	}
	else {
		throw std::exception();
	}
}

bool IteratorMD::valid() const {
	return curent < md.dim();
}

void IteratorMD::urmator() {
	if (this->valid())
		curent += 1;
	else {
		throw std::exception();
	}
}

void IteratorMD::prim() {
	curent = 0;
}

