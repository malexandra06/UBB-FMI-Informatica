#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;

int MD::TFunctieDispersie(TCheie k)const
//Theta(1)
{
	if (k % cp > 0)
		return k % cp;
	else
		return -(k % cp);
}

void MD::rehashing()
//  BC=WC=AC: Theta(cp_veche)+theta(cp_veche)(for-ul de jos de la adauga) *O(cp_noua),de la functia de adaugare (worst case fara rehashing)
// O(cp_noua*cp_veche)
{
	TElem* tabelaVeche = new TElem[cp];
	int cp_veche = cp;
	cp = 2 * cp;
	for (int i = 0;i < cp_veche;i++)
	{
		tabelaVeche[i] = tabelaDispersie[i];
	}
	delete[] tabelaDispersie;
	delete[] urmator;
	tabelaDispersie = new TElem[cp];
	urmator = new int[cp];
	for (int i = 0;i < cp;i++)
	{
		this->urmator[i] = -1;
		this->tabelaDispersie[i].first = nullKey;
		this->tabelaDispersie[i].second = nullVal;
	}
	primLiber = 0;
	len = 0;
	for (int i = 0;i < cp_veche;i++)
		this->adauga(tabelaVeche[i].first, tabelaVeche[i].second);
	delete[] tabelaVeche;
}

MD::MD() {
	//Theta(cp)
	len = 0;
	cp = 10;
	urmator = new int[cp];
	tabelaDispersie = new TElem[cp];
	for (int i = 0;i < cp ;i++)
	{
		this->urmator[i] = -1;
		this->tabelaDispersie[i].first = nullKey;
		this->tabelaDispersie[i].second = nullVal;
	}
	primLiber = 0;
}


void MD::adauga(TCheie c, TValoare v) {
	//BC: elementul va fi inserat pe pozitia data de functia de dispersie iar pozitia libera nu era fix pozitia pe care l am inserat: Theta(1)
	//WC: facem rehashing: si vom avea theta(cp_noua*cp_veche)
	//WC fara rehashing: inseram elementul pe prima pozitie libera, iar prima pozitie libera trebuie actualizata: theta(n)
	//AC: O(n) daca luam in considerare rehashing, sau theta(cp_noua*cp_veche)
	if (len == cp)
		rehashing();
	int disp = TFunctieDispersie(c);
	if (tabelaDispersie[disp].first == nullKey and tabelaDispersie[disp].second == nullVal)//daca pozitia care trebuie e libera
	{
		tabelaDispersie[disp] = make_pair(c, v);
		urmator[disp] = -1;
		len++;
		if(disp==primLiber)
			for (int i = primLiber + 1;i < cp;i++)
				if (tabelaDispersie[i].first == nullKey)
				{
					primLiber = i;
					break;
				}
	}
	else//altfel inseram elementul pe prima pozitie libera
	{
		tabelaDispersie[primLiber].first = c;
		tabelaDispersie[primLiber].second = v;
		urmator[primLiber] = -1;
		int k = disp;
		while (urmator[k] != -1)
			k = urmator[k];
		urmator[k] = primLiber;
		len++;
		
		for(int i=primLiber+1;i<cp;i++)
			if (tabelaDispersie[i].first == nullKey)
			{
				primLiber = i;
				break;
			}
	}
}


bool MD::sterge(TCheie c, TValoare v) {
	//BC:stergem prima pozitie in lant si dupa ea nu mai e nimic: theta(1)
	//WC: elementul nu se afla in dictionar theta(n)
	//AC:O(n)
	int pos = TFunctieDispersie(c);
	int prec = -1;

	// Caut pozitia elementului
	while (pos != -1 && (tabelaDispersie[pos].first != c || tabelaDispersie[pos].second != v)) {
		prec = pos;
		pos = urmator[pos];
	}

	if (pos == -1)
		return false;  // elementul cautat nu se afla in multidictionar

	int p, pp;
	bool gata = false;

	while (!gata) {
		p = urmator[pos];
		pp = pos;

		// Caut un element care poate fi inserat la pozitia curenta
		while (p != -1 && TFunctieDispersie(tabelaDispersie[p].first) != pos) {
			pp = p;
			p = urmator[p];
		}

		if (p == -1) {
			// nu avem ce pune in loc
			if (prec != -1)//daca nu e primul in lant facem legatura
				urmator[prec] = urmator[pos];
			else {
				// Daca era primul ,cautam cine il refera  
				int k = 0;
				while (k < cp && urmator[k] != pos)
					k++;
				if (k < cp)
					urmator[k] = urmator[pos];
			}

			tabelaDispersie[pos].first = nullKey;
			tabelaDispersie[pos].second = nullVal;
			urmator[pos] = -1;
			if (pos < primLiber)
				primLiber = pos;
			len--;
			gata = true;
		}
		else {
			//se muta elementul de la pozitia p la pos
			tabelaDispersie[pos] = tabelaDispersie[p];
			prec = pp;
			pos = p;
		}
	}

	return true;
}



vector<TValoare> MD::cauta(TCheie c) const {
	//BC=WC=AC Theta(n)
	vector<TValoare>v;
	int i = TFunctieDispersie(c);
	while (i != -1)
	{
		if (tabelaDispersie[i].first == c)
			v.push_back(tabelaDispersie[i].second);
		i = urmator[i];
	}
	return v;
}


int MD::dim() const {
	//theta(1)
	return len;
}


bool MD::vid() const {
	//theta(1)
	return len == 0;
}


IteratorMD MD::iterator() const {
	//theta(1)
	return IteratorMD(*this);
}


MD::~MD() {
	//theta(1)
	delete[] tabelaDispersie;
	delete[] urmator;
}

int MD::diferentaCheieMaxMin()const
{
	//Theta(n)
	TCheie minn = INT_MAX;
	TCheie maxx = -INT_MAX;
	if (this->vid())
		return -1;
	else
	{
		for (int i = 0;i < len;i++)
		{
			if (tabelaDispersie[i].first > maxx)
				maxx = tabelaDispersie[i].first;
			if (tabelaDispersie[i].first < minn)
				minn = tabelaDispersie[i].first;
		}
		return maxx - minn;
	}
}

/*subalgoritm diferentaCheieMaxMin(Multidictionar m)
	minn<-INT_MAX
	maxx<- -INT_MAX
	daca m.vid()=true atunci
		diferentaCheieMaxMin<- -1
	altfel
		pentru i<-0,len-1 executa

			daca m.tabelaDispersie[i].cheie>maxx atunci
				max<-m.tabelaDispersie[i].cheie
			sf_daca

			daca m.tabelaDispersie[i].cheie<minn atunci
				minn<-m.tabelaDispersie[i].cheie
			sf_daca

		sf_pentru
		diferentaCheieMaxMin<- maxx-minn
	sf_daca
  sf_subalgoritm
*/
