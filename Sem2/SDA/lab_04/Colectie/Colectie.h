#pragma once;
#include <vector>
using std::vector;
#define CAPACITATE 100
typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:
	struct Nod
	{
		TElem e;
		int urmator;
		int anterior;
	};
	int cp = CAPACITATE;
	Nod* elements;
	//referinta catre primul element
	int prim;
	//referinta catre ultimul element 
	int ultim;
	int dimensiune;
	void redimensionare();
	//referinta catre primul element din lista spatiului liber
	int primLiber;

public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;

		//pastreaza doar o aparitie a tuturor elementelor din colectie
		//returneaza numarul de elemente eliminate
		int transformaInMultime();

		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();


};

