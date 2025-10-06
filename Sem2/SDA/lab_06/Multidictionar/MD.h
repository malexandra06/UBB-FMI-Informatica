#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;
#define nullKey -1000000
#define nullVal -1000000

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	TElem* tabelaDispersie;
	int* urmator;
	int len, cp, primLiber;

	int TFunctieDispersie(TCheie k)const;

	void rehashing();

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	//returneaza diferenta dintre cheia maxima si cheia minima 
	//daca dictionarul este vid, se returneaza -1
	int diferentaCheieMaxMin()const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();



};

