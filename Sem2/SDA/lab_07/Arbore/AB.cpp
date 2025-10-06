#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>
#include <unordered_map>

AB::AB() {
    //Theta(1)
    cp = 10;
    dim = 0;
    noduri = new Nod[cp];
    radacina = -1;
    primLiber = 0;  
}

void AB::redimensionare() {
    //Theta(n) n=dim
    Nod* nou = new Nod[cp * 2];
    for (int i = 0; i < dim; i++)
        nou[i] = noduri[i];
    cp *= 2;
    delete[] noduri;
    noduri = nou;
}

AB::AB(const AB& ab) {
    //theta(n) n=dim
    cp = ab.cp;
    dim = ab.dim;
    radacina = ab.radacina;
    primLiber = ab.primLiber;
    noduri = new Nod[cp];
    for (int i = 0; i < dim; i++)
        noduri[i] = ab.noduri[i];
}

AB::AB(TElem e) {
    //theta(1)
    cp = 10;
    dim = 0;
    noduri = new Nod[cp];
    noduri[dim] = { e, -1, -1 };
    radacina = dim;
    dim++;
    primLiber = dim;
}

AB::AB(const AB& st, TElem e, const AB& dr) {
    //theta(st.dim+dr.dim)
    cp = st.cp + dr.cp + 10;
    noduri = new Nod[cp];
    dim = 0;

    int radSt = -1;
    for (int i = 0; i < st.dim; i++)
        noduri[i] = st.noduri[i];
    if (!st.vid())
        radSt = st.radacina;
    dim += st.dim;

    int offsetDr = dim;
    int radDr = -1;
    for (int i = 0; i < dr.dim; i++) {
        Nod nd = dr.noduri[i];
        if (nd.st != -1) nd.st += offsetDr;
        if (nd.dr != -1) nd.dr += offsetDr;
        noduri[dim++] = nd;
    }
    if (!dr.vid())
        radDr = dr.radacina + offsetDr;
    noduri[dim] = { e, radSt, radDr };
    radacina = dim;
    dim++;
    primLiber = dim;  
}

void AB::adaugaSubSt(const AB& st) {
    //BC: fara redimensionare: theta(st.dim)
    //WC: cu redimensionare: theta(st.dim*dim)
    //Overall: O(st.dim*dim)
    if (vid())
        throw std::exception();

    int offset = dim;
    for (int i = 0; i < st.dim; i++) {
        Nod nd = st.noduri[i];
        if (nd.st != -1) nd.st += offset;
        if (nd.dr != -1) nd.dr += offset;
        if (dim == cp)
            redimensionare();
        noduri[dim++] = nd;
    }

    if (!st.vid())
        noduri[radacina].st = st.radacina + offset;

    primLiber = dim;  
}

void AB::adaugaSubDr(const AB& dr) {
    //BC: fara redimensionare: theta(dr.dim)
    //WC: cu redimensionare: theta(dr.dim*dim)
    //Overall: O(dr.dim*dim)
    if (vid())
        throw std::exception();

    int offset = dim;
    for (int i = 0; i < dr.dim; i++) {
        Nod nd = dr.noduri[i];
        if (nd.st != -1) nd.st += offset;
        if (nd.dr != -1) nd.dr += offset;
        if (dim == cp)
            redimensionare();
        noduri[dim++] = nd;
    }

    if (!dr.vid())
        noduri[radacina].dr = dr.radacina + offset;

    primLiber = dim;  
}

TElem AB::element() const {
    //theta(1)
    if (vid())
        throw std::exception();
    return noduri[radacina].info;
}

AB AB::stang() const {
    //O(n) din cauza bfs ,n=numarul de noduri din arborele stang
    if (vid())
        throw std::exception();

    int rootIndex = noduri[radacina].st;
    if (rootIndex == -1) {
        return AB();
    }

    std::unordered_map<int, int> indexMap; //tine evidenta indecsilor vechi si a celor noi
    AB st;
    st.cp = dim;
    st.noduri = new Nod[st.cp];
    st.dim = 0;
    st.radacina = 0;

    std::queue<int> toCopy;//pentru bfs
    toCopy.push(rootIndex);
    indexMap[rootIndex] = st.dim++; 

    while (!toCopy.empty()) {
        int oldIndex = toCopy.front();
        toCopy.pop();
        Nod original = noduri[oldIndex];
        Nod& newNode = st.noduri[indexMap[oldIndex]];

        newNode.info = original.info;

        if (original.st != -1) {
            indexMap[original.st] = st.dim; 
            newNode.st = st.dim++;
            toCopy.push(original.st);
        }
        else {
            newNode.st = -1;
        }

        if (original.dr != -1) {
            indexMap[original.dr] = st.dim;
            newNode.dr = st.dim++;
            toCopy.push(original.dr);
        }
        else {
            newNode.dr = -1;
        }
    }

    st.primLiber = st.dim; 
    return st;
}

AB AB::drept() const {
    //O(n) din cauza bfs ,n=numarul de noduri din arborele drept
    if (vid())
        throw std::exception();

    int rootIndex = noduri[radacina].dr;
    if (rootIndex == -1) {
        return AB();
    }

    std::unordered_map<int, int> indexMap;
    AB dr;
    dr.cp = dim;
    dr.noduri = new Nod[dr.cp];
    dr.dim = 0;
    dr.radacina = 0;

    std::queue<int> toCopy;
    toCopy.push(rootIndex);
    indexMap[rootIndex] = dr.dim++;

    while (!toCopy.empty()) {
        int oldIndex = toCopy.front();
        toCopy.pop();
        Nod original = noduri[oldIndex];
        Nod& newNode = dr.noduri[indexMap[oldIndex]];

        newNode.info = original.info;

        if (original.st != -1) {
            indexMap[original.st] = dr.dim;
            newNode.st = dr.dim++;
            toCopy.push(original.st);
        }
        else {
            newNode.st = -1;
        }

        if (original.dr != -1) {
            indexMap[original.dr] = dr.dim;
            newNode.dr = dr.dim++;
            toCopy.push(original.dr);
        }
        else {
            newNode.dr = -1;
        }
    }

    dr.primLiber = dr.dim;
    return dr;
}
AB::~AB() {
    //theta(1)
    delete[] noduri;
}

bool AB::vid() const {
    //theta(1)
    return dim == 0;
}

IteratorAB* AB::iterator(string s) const {
    if (s == "preordine")
        return new IteratorPreordine(*this);
    if (s == "inordine")
        return new IteratorInordine(*this);
    if (s == "postordine")
        return new IteratorPostordine(*this);
    if (s == "latime")
        return new IteratorLatime(*this);
    return nullptr;
}

int AB::valoareMinima()const
{   //theta(n) n=nr vf (BFS)
    if (vid())
        return NULL_TVALOARE;
    int minn = INT_MAX;
    int curent = radacina;
    std::queue<int> q;
    q.push(curent);
    while (!q.empty())
    {
        curent = q.front();
        q.pop();
        if (noduri[curent].info < minn)
            minn = noduri[curent].info;
        if (noduri[curent].st != -1)
            q.push(noduri[curent].st);
        if (noduri[curent].dr != -1)
            q.push(noduri[curent].dr);
    }
    return minn;
}

/*
* subalgoritm valoareMinima(AB a)
*   
*   daca a.vid()=true atunci
*       valoareMinima<-NULL_TVALOARE
*   sf_daca
* 
*   minn<-INT_MAX
*   curent=a.radacina
*  
*   q.push(curent)
*   cat timp q nu e vida executa
*       curent<-q.front()
* 
*       daca a.noduri[curent].info<minn atunci
*           minn<-a.noduri[curent].info
*       sf_daca
* 
*       daca a.noduri[curent].st != -1 atunci
*           q.push(a.noduri[curent].st);
*       sf_daca
* 
*       daca a.noduri[curent].dr != -1 atunci
*           q.push(a.noduri[curent].dr);
*       sf_daca
* 
*   sf_cat timp
*   valoareMinima<-minn
*/