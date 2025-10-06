#include <string>
#include <iostream>
#pragma once
using std::string;
using std::ostream;

class Produs
{
private:
	string nume;
	string tip;
	string producator;
	int pret;

public:
	Produs() = default;
	Produs(const string &nume, const string &tip, const string &producator, const int pret);
	Produs(const Produs& prod);
	~Produs();
	string getNume()const;
	string getTip()const;
	string getProducator()const;
	int getPret()const noexcept;

	void setNume(const string &newname);
	void setTip(const string &newtype);
	void setProducator(const string &newproducer);
	void setPret(const int newprice)noexcept;

	bool equal(const Produs& p)const;
};
