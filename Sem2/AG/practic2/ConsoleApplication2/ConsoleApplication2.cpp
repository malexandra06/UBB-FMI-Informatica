#include <vector> 
#include <iostream> 
#include <string>
#define _CRTDBG_MAP_ALLOC
using namespace std;

class Participant {
public:
	virtual void tipareste() = 0;
	virtual bool eVoluntar()
	{
		return true;
	}
	virtual ~Participant() = default;
};

class Personal:public Participant
{
private:
	string nume;
public:
	Personal(string nume) :nume{ nume } {}
	virtual void tipareste()override
	{
		cout << nume;
	}
};

class Director :public Personal
{
public:
	Director(string nume) :Personal(nume) {}
	void tipareste()override
	{
		Personal::tipareste();
		cout << " Director " << endl;
	}
};

class Admininstrator:public Personal
{
public:
	Admininstrator(string nume) :Personal(nume) {}
	void tipareste()override
	{
		Personal::tipareste();
		cout << " Admininstrator " << endl;
	}
};

class Angajat : public Participant
{
private:
	Participant* p;
public:
	Angajat(Participant* p0) :p{ p0 } {}
	~Angajat() { delete p; }
	void tipareste()override
	{
		p->tipareste();
		cout << " angajat " << endl;
	}
	bool eVoluntar()override
	{
		return false;
	}
};

class ONG
{
private:
	vector<Participant*> v;
public:
	void add(Participant* p)
	{
		v.push_back(p);
	}
	vector<Participant*> getAll(bool voluntar)
	{
		vector<Participant*> l;
		for (auto& el : v)
			if (el->eVoluntar() == voluntar)
				l.push_back(el);
		return l;
	}
	~ONG()
	{
		for (auto &el : v)
			if(el!=nullptr)
				delete el;
	}
};


ONG f()
{
	ONG obj;
	obj.add(new Admininstrator("Alin"));
	obj.add(new Angajat(new Admininstrator("Marian")));
	obj.add(new Director("Mihai"));
	obj.add(new Angajat(new Director("Ana")));
	return obj;
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		ONG obj = f();
		for (auto el : obj.getAll(true))
		{
			el->tipareste();
		}
		cout << endl;
		for (auto el : obj.getAll(false))
		{
			el->tipareste();
		}
	}
	_CrtDumpMemoryLeaks();
	
	return 0;
}