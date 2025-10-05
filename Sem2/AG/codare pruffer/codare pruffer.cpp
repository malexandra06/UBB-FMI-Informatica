#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");

struct Arbore {
    int n;
    vector<int> tati;          
    vector<int> grade;         
    set<int> frunze;           
};

vector<int> codarePruffer(Arbore a) {
    vector<int> codPruffer;

    
    for (int i = 0; i < a.n; i++) {
        if (a.tati[i] != -1) {
            a.grade[a.tati[i]]++;
            a.grade[i]++;
        }
    }

    for (int i = 0; i < a.n; i++) {
        if (a.grade[i] == 1 && a.tati[i] != -1) { 
            a.frunze.insert(i);
        }
    }

    while (codPruffer.size() < a.n - 1) {
        if (a.frunze.empty()) break;

        int frunza = *a.frunze.begin();
        a.frunze.erase(a.frunze.begin());

        int tata = a.tati[frunza];
        codPruffer.push_back(tata);

        a.grade[tata]--;
        if (a.grade[tata] == 1) {
            a.frunze.insert(tata);
        }
    }

    return codPruffer;
}

int main() {
    Arbore a;
    in >> a.n;
    a.tati.resize(a.n);
    a.grade.resize(a.n, 0);

    for (int i = 0; i < a.n; i++) {
        in >> a.tati[i];
    }

    vector<int> cod = codarePruffer(a);
    out << cod.size() << endl;
    for (int val : cod) {
        out << val << " ";
    }

    return 0;
}