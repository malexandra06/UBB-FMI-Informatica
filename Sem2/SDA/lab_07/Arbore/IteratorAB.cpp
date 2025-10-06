#include "AB.h"
#include "IteratorAB.h"
#include <stack>
#include <queue>
#include <stdexcept>

IteratorInordine::IteratorInordine(const AB& _ab) : ab(_ab) {}

void IteratorInordine::prim() {
    //theta(h), h=inaltimea arborelui
    while (!stiva.empty()) stiva.pop();
    int curent = ab.radacina;
    while (curent != -1) {
        stiva.push(curent);
        curent = ab.noduri[curent].st;
    }
}

bool IteratorInordine::valid() {
    //theta(1)
    return !stiva.empty();
}

TElem IteratorInordine::element() {
    //theta(1)
    if (!valid()) throw std::runtime_error("Iterator invalid");
    return ab.noduri[stiva.top()].info;
}

void IteratorInordine::urmator() {
    //theta(h) h=inaltimea arborelui
    if (!valid()) throw std::runtime_error("Iterator invalid");

    int curent = stiva.top();
    stiva.pop();
    curent = ab.noduri[curent].dr;

    while (curent != -1) {
        stiva.push(curent);
        curent = ab.noduri[curent].st;
    }
}

IteratorPreordine::IteratorPreordine(const AB& _ab) : ab(_ab) {}

void IteratorPreordine::prim() {
    //theta(1)
    while (!stiva.empty()) stiva.pop();
    if (!ab.vid()) stiva.push(ab.radacina);
}

bool IteratorPreordine::valid() {
    //theta(1)
    return !stiva.empty();
}

TElem IteratorPreordine::element() {
    //theta(1)
    if (!valid()) throw std::runtime_error("Iterator invalid");
    return ab.noduri[stiva.top()].info;
}

void IteratorPreordine::urmator() {
    //theta(1)
    if (!valid()) throw std::runtime_error("Iterator invalid");

    int nod = stiva.top();
    stiva.pop();

    // Mai întâi push drept, apoi stâng (pentru a procesa stânga mai întâi)
    if (ab.noduri[nod].dr != -1) stiva.push(ab.noduri[nod].dr);
    if (ab.noduri[nod].st != -1) stiva.push(ab.noduri[nod].st);
}

IteratorPostordine::IteratorPostordine(const AB& _ab) : ab(_ab) {}

void IteratorPostordine::prim(){
    //theta(n), n=numarul de noduri
    stiva = std::stack<int>();
    output = std::stack<int>();

    if (!ab.vid()) {
        stiva.push(ab.radacina);

        while (!stiva.empty()) {
            int current = stiva.top();
            stiva.pop();
            output.push(current);

            if (ab.noduri[current].st != -1)
                stiva.push(ab.noduri[current].st);
            if (ab.noduri[current].dr != -1)
                stiva.push(ab.noduri[current].dr);
        }
    }
}

bool IteratorPostordine::valid(){
    //theta(1)
    return !output.empty();
}

TElem IteratorPostordine::element(){
    //theta(1)
    if (!valid()) throw std::exception();
    return ab.noduri[output.top()].info;
}

void IteratorPostordine::urmator(){
    //theta(1)
    if (!valid()) throw std::exception();
    output.pop();
}

IteratorLatime::IteratorLatime(const AB& _ab) : ab(_ab) {}

void IteratorLatime::prim() {
    //theta(1)
    while (!coada.empty()) coada.pop();
    if (!ab.vid()) coada.push(ab.radacina);
}

bool IteratorLatime::valid() {
    //theta(1)
    return !coada.empty();
}

TElem IteratorLatime::element() {
    //theta(1)
    if (!valid()) throw std::runtime_error("Iterator invalid");
    return ab.noduri[coada.front()].info;
}

void IteratorLatime::urmator() {
    //theta(1)
    if (!valid()) throw std::runtime_error("Iterator invalid");
    int nod = coada.front();
    coada.pop();
    if (ab.noduri[nod].st != -1) coada.push(ab.noduri[nod].st);
    if (ab.noduri[nod].dr != -1) coada.push(ab.noduri[nod].dr);
}
