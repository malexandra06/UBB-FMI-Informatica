#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <queue>
#include <functional>
#include <cmath>

#define INF 1000
using namespace std;

ifstream in("graf.txt");

struct Muchie {
    int u, v;
    float w;
};

struct nod {
    int cx, cy, pi;
    float d;

};

float distanta(nod n1, nod n2)
{
    return sqrt((n1.cx - n2.cx) * (n1.cx - n2.cx) + (n1.cy - n2.cy) * (n1.cy - n2.cy));
}

struct Graf {
    int n, m;
    Muchie muchii[200];
    nod V[105];
};

void initializare_s(Graf& g, int s) {
    for (int i = 1; i <= g.n; i++) {
        g.V[i].d = INF;
        g.V[i].pi = -1;
    }
    g.V[s].d = 0;
}

void Dijkstra(Graf& g, int s) {
    initializare_s(g, s);

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> q;
    q.push({ 0, s });

    while (!q.empty()) {
        float dist_u = q.top().first;
        int u = q.top().second;
        q.pop();
        if (dist_u > g.V[u].d)
            continue;

        for (int i = 1; i <=g.m; i++) {
            if (g.muchii[i].u == u) {
                int v = g.muchii[i].v;
                float w = g.muchii[i].w;
                if (g.V[v].d > g.V[u].d + w) {
                    g.V[v].d = g.V[u].d + w;
                    g.V[v].pi = u;
                    q.push({ g.V[v].d, v });
                }
            }
        }
    }
}

int main() {
    Graf g;
    int s,d;
    in >> g.n >> g.m;
    for (int i = 1;i <=g.n;i++)
    {
        in >> g.V[i].cx >> g.V[i].cy;
    }
    for (int i = 1; i <= g.m; i++) {
        in >> g.muchii[i].u >> g.muchii[i].v;
        g.muchii[i].w = distanta(g.V[g.muchii[i].u], g.V[g.muchii[i].v]);
    }
    /*for (int i = 1;i <=g.n;i++)
        for (int j = 1;j <=g.n;j++)
        {
            float d = distanta(g.V[i], g.V[j]);
            cout << d<< endl;
        }
    */
    s = 1;
    Dijkstra(g, s);
    d = 9;
    cout << "Distanta minima de la nodul " << s << " la " << d;
    if (g.V[d].d == INF)
        cout << " INF";
    else
        cout << " = " << g.V[d].d;
    return 0;
}