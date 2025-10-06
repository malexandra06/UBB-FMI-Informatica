#pragma once
#include <vector>
#include <string>
#include "produs.h"
#include <fstream>
using std::vector;
using std::string;

class RepoProduse {
protected:
    vector<Produs>listaProduse;

public:
    RepoProduse()=default;
    RepoProduse(RepoProduse& ot) = delete;
    virtual ~RepoProduse() = default;
    // Metode const care nu modificã starea
    vector<Produs>&getAll();
    int len()const noexcept;
    int find(const string &name)const;

    // Metode care modificã starea
    virtual void adauga(const string &nume, const string &tip, const string &producator, const int pret);
    virtual void sterge(const string &nume);
    virtual void modifica(const string &tip_nou, const string &producator_nou, const int pret_nou, const string &nume);
};

class RepoFileProduse :public RepoProduse
{
private:
    string fisier;
    void ReadFromFile();
    void WriteToFile();
    void Clear() {
        std::ofstream out(fisier, std::ios::trunc);
        out.close();
    }

public:
    RepoFileProduse(string fisier) :RepoProduse(), fisier{ fisier } {
        ReadFromFile();
    }
    void adauga(const string& nume, const string& tip, const string& producator, const int pret) override {
        RepoProduse::adauga(nume,tip,producator,pret);
        WriteToFile();
    }
    void sterge(const string& nume) override {
        RepoProduse::sterge(nume);
        WriteToFile();
    }
    void modifica(const string& tip_nou, const string& producator_nou, const int pret_nou, const string& nume) override {
        RepoProduse::modifica(tip_nou, producator_nou, pret_nou, nume);
        WriteToFile();
    }

    ~RepoFileProduse() override {
    }
};