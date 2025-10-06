#pragma once
#include "RepoProduse.h"
#include "RepoCos.h"
#include "validator.h"
#include <map>
#include "undo.h"
#include <functional>
#include <memory>

using std::map;
enum class Criteriu {
    NUME, TIP, PRODUCATOR
};

enum class CriteriuSortare {
    NUME_S, PRET, NUME_TIP
};

class ServiceProd : public Subject{
private:
    RepoCos& cos;
    RepoFileProduse& repo;
    Validator validator;
    std::vector<std::unique_ptr<ActiuneUndo>> ActiuniUndo;

public:
    ServiceProd(RepoFileProduse& repo,RepoCos& cos)noexcept;
    ServiceProd(const ServiceProd& other) = delete;
    vector<Produs>&getAll();
    vector<Produs>& getAllCos();
    int len() const noexcept;
    void adauga(const string &nume, const string &tip, const string &producator, const int pret);
    int find(const string &nume)const;
    void sterge(const string &nume);
    void modifica(const string& tip, const string& producator, const int pret, const string &numeCautat);
    const vector<Produs> filtrare(const Criteriu criteriu, const string& valoare);
    const vector<Produs> filtrarePret(const int valoare);
    static bool comparaNume(const Produs &p1, const Produs &p2);
    static bool comparaPret(const Produs& p1, const Produs& p2)noexcept;
    static bool comparaNume_Tip(const Produs& p1, const Produs& p2);
    vector<Produs> sortare(const CriteriuSortare);
    void adaugaCos(const string& nume);
    void stergeCos(const string& nume);
    void golesteCos();
    void adaugaRandom(int dim);
    void exportaInCSV(const string& numeFisier);
    void exportaInHTML(const string& numeFisier);
    int sumaTotala();
    map<string,int> raportTip();
    map<string, int> raportTipProduse();
    void undo();
};