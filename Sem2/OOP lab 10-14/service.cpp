#include "service.h"
#include "algorithm"
#include "exception.h"
#include <iostream>
#include <fstream>
// Constructor pentru ServiceProd
// Inițializează service-ul cu un repository de produse
ServiceProd::ServiceProd(RepoFileProduse& repo, RepoCos& cos) noexcept : repo(repo),cos(cos) {}

// Returnează lista tuturor produselor din repository
vector<Produs>&ServiceProd::getAll()
{
    return this->repo.getAll();
}

vector<Produs>& ServiceProd::getAllCos()
{
    return this->cos.getAll();
}

// Returnează numărul total de produse din repository
int ServiceProd::len()const noexcept
{
    return this->repo.len();
}

// Adaugă un produs în repository
//void ServiceProd::adauga(const string &nume, const string &tip, const string &producator, const int pret)
//{
//    try {this->validator.valideaza(nume, tip, producator, pret);}catch (const ValidatorException& e) {std::cout << e.what()<<"\n";}
//    try { this->repo.adauga(nume, tip, producator, pret); }catch(const RepoProduseException& e) { std::cout << e.what() << "\n"; }
//}

void ServiceProd::adauga(const string& nume, const string& tip, const string& producator, const int pret)
{
    this->validator.valideaza(nume, tip, producator, pret);
    if(repo.find(nume)==-1)
        ActiuniUndo.push_back(std::make_unique<UndoAdauga>(this->repo, Produs(nume,tip,producator,pret)));
    this->repo.adauga(nume, tip, producator, pret);
}


// Caută un produs după ID și returnează indexul său
// Returnează -1 dacă produsul nu este găsit
int ServiceProd::find(const string &nume)const
{
    if (this->repo.find(nume) == -1) throw ServiceException("Produs inexistent!");
    return this->repo.find(nume);
}

// Șterge un produs din repository pe baza ID-ului
//void ServiceProd::sterge(const string &nume)
//{
//    try {this->repo.sterge(nume);}
//    catch (const RepoProduseException &e) { std::cout << e.what()<<"\n"; }
//}
void ServiceProd::sterge(const string& nume)
{
    if (repo.find(nume) != -1)
    {
        ActiuniUndo.push_back(std::make_unique<UndoSterge>(this->repo, this->getAll()[this->repo.find(nume)]));
    }
    this->repo.sterge(nume);
}

// Modifică un produs existent din repository
// Găsește produsul după ID și îi actualizează atributele
void ServiceProd::modifica(const string& tip, const string& producator, const int pret, const string &numeCautat)
{
    this->validator.valideaza(numeCautat, tip, producator, pret);
    if(repo.find(numeCautat)!=-1)
        ActiuniUndo.push_back(std::make_unique<UndoModifica>(this->repo,this->getAll()[this->repo.find(numeCautat)]));
    this->repo.modifica(tip, producator, pret,numeCautat);
}

// Filtrează produsele
const vector<Produs> ServiceProd::filtrare(const Criteriu criteriu,const string &valoare) {
    const vector<Produs> produse = repo.getAll();
    vector<Produs> rezultateFiltrate(produse.size());

    switch (static_cast<int>(criteriu)) {
    case static_cast<int>(Criteriu::NUME): {
        auto iterator1 = copy_if(produse.begin(), produse.end(), rezultateFiltrate.begin(),
            [valoare](const Produs& p) { return p.getNume() == valoare; });
        rezultateFiltrate.resize(distance(rezultateFiltrate.begin(), iterator1));
        break;}
    case static_cast<int>(Criteriu::TIP): {
        auto iterator2 = copy_if(produse.begin(), produse.end(), rezultateFiltrate.begin(),
            [valoare](const Produs& p) { return p.getTip() == valoare; });
        rezultateFiltrate.resize(distance(rezultateFiltrate.begin(), iterator2));
        break;}
    case static_cast<int>(Criteriu::PRODUCATOR): {
        auto iterator3 = copy_if(produse.begin(), produse.end(), rezultateFiltrate.begin(),
            [valoare](const Produs& p) { return p.getProducator() == valoare; });
        rezultateFiltrate.resize(distance(rezultateFiltrate.begin(), iterator3));
        break;}}
    return rezultateFiltrate;
}

// Filtrează produsele pe baza prețului
const vector<Produs> ServiceProd::filtrarePret(const int valoare)
{
    const vector<Produs>produse = repo.getAll();
    vector<Produs> rezultateFiltrate(produse.size());
    auto iterator = copy_if(produse.begin(), produse.end(), rezultateFiltrate.begin(), [valoare](const Produs& p) {
        return p.getPret() == valoare;
        });
    rezultateFiltrate.resize(distance(rezultateFiltrate.begin(), iterator));
    return rezultateFiltrate;
}

// Compară două produse în funcție de un criteriu specific (Nume, Preț, Nume+Tip)
// Returnează true dacă p1 trebuie să fie după p2 în ordine descrescătoare
// Implementare (service.cpp)
bool ServiceProd::comparaNume(const Produs& p1, const Produs& p2)
{
    return p1.getNume() < p2.getNume(); // Sortare crescătoare A-Z
}
bool ServiceProd::comparaPret(const Produs& p1, const Produs& p2)noexcept
{
    return p1.getPret() < p2.getPret(); // Sortare crescătoare A-Z
}
bool ServiceProd::comparaNume_Tip(const Produs& p1, const Produs& p2)
{
    if (p1.getNume() == p2.getNume())return p1.getTip() < p2.getTip();return p1.getNume() <p2.getNume();
}
vector<Produs> ServiceProd::sortare(CriteriuSortare crt)
{
    vector<Produs> rezultat = this->getAll();
    bool(*functieDeComparare)(const Produs & p1, const Produs & p2)=comparaNume_Tip;
    switch (static_cast<int>(crt)){
    case static_cast<int>(CriteriuSortare::NUME_S):
        functieDeComparare = comparaNume;
        break;
    case static_cast<int>(CriteriuSortare::PRET):
        functieDeComparare = comparaPret;
        break;}
    sort(rezultat.begin(), rezultat.end(), functieDeComparare);
    return rezultat;
}

void ServiceProd::adaugaCos(const string& nume) {
    if (this->find(nume) == -1)
        throw ServiceException("Produs inexistent in stoc!\n");
    Produs p = this->getAll()[this->find(nume)];
    this->cos.adaugaCos(p);
    notify();
}

void ServiceProd::golesteCos() {
    this->cos.golesteCos();
    notify();
}

void ServiceProd::stergeCos(const string& nume)
{
    this->cos.sterge(nume);
    notify();
}

void ServiceProd::adaugaRandom(int dimensiune) {
    if (dimensiune > 2 * this->len())
        throw ServiceException("Nu se pot adauga atatea produse in cos!\n");
    this->cos.adaugaRandom(dimensiune, this->getAll());
    notify();
}


void ServiceProd::exportaInCSV(const string& numeFisier) {
    std::ofstream fout(numeFisier, std::ios::trunc);
    vector<Produs>produse = this->getAllCos();
    if (!fout.is_open()) { throw RepoProduseException("Fisierul cu numele " + numeFisier + " nu a putut fi deschis!\n"); }
    for (const auto& produs : produse) {
        fout << produs.getNume() << "," << produs.getTip() << "," << produs.getProducator() << "," << produs.getPret() << "\n";
    }
    fout.close();
}

void ServiceProd::exportaInHTML(const string& numeFisier) {
    std::ofstream fout(numeFisier);
    if (!fout.is_open()) { throw RepoProduseException("Fisierul cu numele " + numeFisier + " nu a putut fi deschis!\n"); }
    vector<Produs>produse = this->getAllCos();
    fout << "<html><body>\n";
    fout << "<table border=\"1\" style=\"width:100 % \">\n";
    for (const auto& produs : produse) {
        fout << "<tr>\n";
        fout << "<td>" << produs.getNume()<< "</td>\n";
        fout << "<td>" << produs.getTip()<< "</td>\n";
        fout << "<td>" << produs.getProducator() << "</td>\n";
        fout << "<td>" << produs.getPret()<< "</td>\n";
        fout << "</tr>\n";
    }
    fout << "</table>\n";
    fout << "</body></html>\n";
    fout.close();
}


int ServiceProd::sumaTotala()
{
    return this->cos.getSuma();
}

map<string,int> ServiceProd::raportTip()
{
    map<string, int> raport;
    for (const Produs& p : this->getAllCos())
    {
        string tip = p.getTip();
        if (raport.find(tip) == raport.end())
            raport[tip] = 1;
        else
        {
            raport[tip]++;
        }
    }
    return raport;
}

map<string, int> ServiceProd::raportTipProduse()
{
    map<string, int> raport;
    for (const Produs& p : this->getAll())
    {
        string tip = p.getTip();
        if (raport.find(tip) == raport.end())
            raport[tip] = 1;
        else
        {
            raport[tip]++;
        }
    }
    return raport;
}

void ServiceProd::undo()
{
    if (ActiuniUndo.empty()) { throw ServiceException{ "Nu mai este undo de facut!\n" }; }
    ActiuniUndo.back()->doUndo();
    ActiuniUndo.pop_back();
}