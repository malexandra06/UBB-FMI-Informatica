#pragma once
#include <vector>
#include <string>
#include "produs.h"
#include "observator.h"
using std::vector;
using std::string;


class RepoCos{
private:
    vector<Produs>cosCumparaturi;
    int sumaTotala = 0;
public:
    RepoCos() = default;
    RepoCos(const RepoCos& ot) = delete;
    // Metode const care nu modificã starea
    vector<Produs>& getAll();
    int find(const string& name)const;
    void adaugaCos(const Produs& p);
    void golesteCos();
    void sterge(const string& nume);
    void adaugaRandom(const int nr, vector<Produs>produse);
    int getSuma()const;
};