#pragma once
#include "service.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga:public ActiuneUndo
{
	Produs produsAdaugat;
	RepoFileProduse& repo;
public:
	UndoAdauga(RepoFileProduse& repo, const Produs& p) :repo{ repo }, produsAdaugat{ p } {}
	void doUndo() override
	{
		repo.sterge(produsAdaugat.getNume());
	}
};

class UndoSterge :public ActiuneUndo
{
	Produs produsSters;
	RepoFileProduse& repo;
public:
	UndoSterge(RepoFileProduse& repo,const Produs&p):repo{repo},produsSters{p}{ }
	void doUndo()override
	{
		repo.adauga(produsSters.getNume(), produsSters.getTip(), produsSters.getProducator(), produsSters.getPret());
	}
};

class UndoModifica :public ActiuneUndo
{
	Produs produsDeModificat;
	RepoFileProduse& repo;
public:
	UndoModifica(RepoFileProduse& repo, const Produs& p) :repo{ repo }, produsDeModificat{ p } {}
	void doUndo()override
	{
		int poz = repo.find(produsDeModificat.getNume());
		repo.sterge(repo.getAll()[poz].getNume());
		repo.adauga(produsDeModificat.getNume(), produsDeModificat.getTip(), produsDeModificat.getProducator(), produsDeModificat.getPret());
	}
};