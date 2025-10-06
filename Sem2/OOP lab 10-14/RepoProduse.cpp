#include "RepoProduse.h"
#include "exception.h"
#include <algorithm>
#include <sstream> // pentru istringstream

vector<Produs>& RepoProduse::getAll(){
    return this->listaProduse;
}

int RepoProduse::len() const noexcept{
    return static_cast<int>(this->listaProduse.size());
}

void RepoProduse::adauga(const string &nume, const string &tip, const string &producator, const int pret) {
    if (find(nume) != -1)
        throw RepoProduseException("Produs existent!");
    this->listaProduse.push_back(Produs(nume, tip, producator, pret));
}


int RepoProduse::find(const string &name) const{
    auto it = find_if(this->listaProduse.begin(),
        this->listaProduse.end(),
        [name](const Produs& p)
        { if (p.getNume() == name)
            return true;return false;});
    const int poz = static_cast<int>(std::distance(this->listaProduse.begin(), it));
    if (it != this->listaProduse.end()) //verific daca e la sf
        return poz;
    return -1;
}

void RepoProduse::sterge(const string &nume) {
    const int poz = find(nume);
    if (poz != -1) {
        this->listaProduse.erase(this->listaProduse.begin() + poz);
    }
    else {
        throw RepoProduseException("Produs inexistent!");
    }
}

void RepoProduse::modifica(const string &tip_nou, const string &producator_nou, const int pret_nou, const string &nume) {
    const int poz = find(nume);
    if (poz != -1) {
        this->listaProduse[poz].setTip(tip_nou);
        this->listaProduse[poz].setProducator(producator_nou);
        this->listaProduse[poz].setPret(pret_nou);
    }
    else {
        throw RepoProduseException("Produs inexistent!");
    }
}



void RepoFileProduse::ReadFromFile() {
    std::ifstream fin(fisier);
    if (!fin.is_open()) {
        throw RepoProduseException("Fisierul nu a putut fi deschis: " + fisier);
    }

    std::string linie;
    while (std::getline(fin, linie)) {
        std::istringstream linieStream(linie);
        std::string nume, tip, producator, pretStr;

        std::getline(linieStream, nume, ',');
        std::getline(linieStream, tip, ',');
        std::getline(linieStream, producator, ',');
        std::getline(linieStream, pretStr, ',');

        int pret = std::stoi(pretStr);

        RepoProduse::adauga(nume, tip, producator, pret);
    }

    fin.close();
}


void RepoFileProduse::WriteToFile() {
    std::ofstream fout(fisier);
    if (!fout.is_open()) {
        throw RepoProduseException("Fisierul nu a putut fi deschis: " + fisier);
    }

    for (const auto& p : RepoProduse::getAll()) {
        fout << p.getNume() << ","
            << p.getTip() << ","
            << p.getProducator() << ","
            << p.getPret() << "\n";
    }

    fout.close();
}
