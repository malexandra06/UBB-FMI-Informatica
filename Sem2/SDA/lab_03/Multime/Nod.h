#pragma once
class Nod;
typedef int TElem;


//se defineste tipul PNod ca fiind adresa unui Nod

typedef Nod* PNod;



class Nod

{

public:

	friend class Multime;

	//constructor

	Nod(TElem e, PNod urm);

	TElem element();

	PNod urmator();

private:

	TElem e;

	PNod urm;

};