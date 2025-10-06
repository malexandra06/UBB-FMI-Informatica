#include "Matrice.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

// Constructor
Matrice::Matrice(int m, int n)
///Theta(1) complexitate
{
    if (m <= 0 || n <= 0)
        throw invalid_argument("Numărul de linii și coloane trebuie să fie pozitiv!");

    this->nrL = m;
    this->nrC = n;
    this->dim = 0;
    this->cp = 2; 

    this->elemente = new TElem[cp];
    this->index = new int[cp];
    this->linii = new int[m + 1] {0}; 
}

Matrice::~Matrice() 
//Theta(1) complexitate
{
    delete[] linii;
    delete[] index;
    delete[] elemente;
}

int Matrice::nrLinii() const 
//Theta(1) complexitate
{
    return this->nrL;
}

int Matrice::nrColoane() const 
//Theta(1) complexitate
{
    return this->nrC;
}

TElem Matrice::element(int i, int j) const 
//BC : cand elementul cautat se afla pe coloana de la care incepe linia i Theta(1)
//WC : elementul cautat este NULL Theta(n), n este numarul de coloane intre care se situeaza linia i
//Overall: O(n)
{
    if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC)
        throw out_of_range("Pozitie invalida!");

    int start = this->linii[i];
    int end = this->linii[i + 1];

    for (int k = start; k < end; k++)
        if (this->index[k] == j)
            return this->elemente[k];

    return NULL_TELEMENT; 
}


TElem Matrice::modifica(int i, int j, TElem e) 
//BC : cand elementul cautat se afla pe coloana de la care incepe linia i, iar elementul cu care va fi inlocuit este diferit de NULL; Theta(1)
//WC : elementul cautat pe pozitiile i,j este NULL, iar elementul cu care se va modifica nu ,iar dim==cp; Theta(n)+Theta(dim)+Theta(nrL)+Theta(n), n este numarul de coloane intre care se situeaza linia i
//     daca presupunem ca redimensionarea are complexitate amortizata (se intampla rar): Theta(n)+Theta(nrL)
//Overall: O(n)+O(nrL)
{
    TElem vechi = NULL_TELEMENT;
    if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC)
        throw out_of_range("Pozitie invalida!");

    int start = this->linii[i];
    int end = this->linii[i + 1];

    for (int k = start; k < end; k++) {
        if (this->index[k] == j) {//cautam 
            vechi = this->elemente[k];

            if (e == NULL_TELEMENT) {//trebuie sa il stergem 

                for (int p = k; p < this->dim - 1; p++) {
                    this->elemente[p] = this->elemente[p + 1];
                    this->index[p] = this->index[p + 1];
                }
                this->dim--;
                for (int p = i + 1; p <= nrL; p++)
                    this->linii[p]--;
                return vechi;
            }

            else if (e != NULL_TELEMENT)
            {
                this->elemente[k] = e;
                return vechi;
            }
        }
    }

    if (e != NULL_TELEMENT and vechi == NULL_TELEMENT)
    {//practic il adaugam

        if (this->dim == this->cp) {
            int newCp = cp * 2;
            TElem* newElemente = new TElem[newCp];
            int* newColoane = new int[newCp];

            for (int p = 0; p < dim; p++) {
                newElemente[p] = elemente[p];
                newColoane[p] = index[p];
            }

            delete[] elemente;
            delete[] index;
            elemente = newElemente;
            index = newColoane;
            cp = newCp;
        }

        int ind = this->linii[i + 1];

        for (int p = dim; p > ind; p--) {
            this->elemente[p] = this->elemente[p - 1];
            this->index[p] = this->index[p - 1];
        }

        this->elemente[ind] = e;
        this->index[ind] = j;
        this->dim++;

        for (int p = i + 1; p <= nrL; p++)
            this->linii[p]++;

        return NULL_TELEMENT;
    }
}

// BC: nu trebuie sa se faca redimensionare, iar linia respectiva are elemente pe fiecare coloana theta(nrC)
// WC: linia nu contine elemente theta(nrC*complexitate_modifica worst case)
// Overall: O(nrC*(n+nrL))
void Matrice::setElemsOnLine(int line, TElem elem)
{
    if (line < 0 || line >= this->nrL)
        throw out_of_range("Linie invalida");

    for (int i = 0;i < this->nrC;i++)
        this->modifica(line, i, elem);   
}

/*
* subalgoritm setElemsOnLine(Matrice m,int line,TElem elem)
* 
* daca line<0 sau line>nrL atunci
*   @se arunca exceptie out_of_range
* 
* pentru i<-0,m.nrC-1 executa
*   modifica(m,line,i,elem)
* 
*/


