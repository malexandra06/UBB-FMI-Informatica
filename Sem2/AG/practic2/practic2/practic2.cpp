#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream in("graf.in");
ofstream out("graf.txt");

struct Muchie {
    int u, v, w, idx;
    bool in_MST = false;
};

int N, M;
vector<Muchie> muchii;
vector<int> parinte, rang;

int find(int x) {
    if (parinte[x] != x)
        parinte[x] = find(parinte[x]);
    return parinte[x];
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        if (rang[rx] < rang[ry])
            parinte[rx] = ry;
        else {
            parinte[ry] = rx;
            if (rang[rx] == rang[ry])
                rang[rx]++;
        }
    }
}

int main() {
    in >> N >> M;
    muchii.resize(M);
    for (int i = 0; i < M; ++i) {
        in >> muchii[i].u >> muchii[i].v >> muchii[i].w;
        muchii[i].idx = i;
        if (i < N - 1)
            muchii[i].in_MST = true; 
    }

    for (int i = 0; i < N - 1; ++i) {
        
        parinte.resize(N);
        rang.assign(N, 0);
        for (int j = 0; j < N; ++j)
            parinte[j] = j;

        
        for (int j = 0; j < N - 1; ++j) {
            if (i == j) continue; 
            unite(muchii[j].u, muchii[j].v);
        }

        int best_idx = -1;
        int best_cost = 1e9;

        
        for (int j = N - 1; j < M; ++j) {
            int ru = find(muchii[j].u);
            int rv = find(muchii[j].v);
            if (ru != rv && muchii[j].w < best_cost) {
                best_cost = muchii[j].w;
                best_idx = muchii[j].idx;
            }
        }

        out << best_idx << "\n";
    }

    return 0;
}
