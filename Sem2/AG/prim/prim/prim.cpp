// prim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#define INF 10000
#include <queue>
#include <vector>
using namespace std;
ifstream in("graf.in");
ofstream out("graf.out");

struct Varf
{
    int key;
    int pi;
    bool inQueue = true;
};

struct Muchie
{
    int u, v, w;
};

struct Graf
{
    int m, n;
    Varf v[2000];
    Muchie muchii[2000];
    int adj[100][100];
};

int mst_prim(Graf &g, int r,int& cost,int&nr)
{
    nr = 0;
    cost = 0;
    for (int i = 0;i < g.n;i++)
    {
        g.v[i].key = INF;
        g.v[i].pi = -1;
        g.v[i].inQueue = true;
    }
    g.v[r].key = 0;
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.push({ 0,r });
    while (!q.empty())
    {
        int w = q.top().first;
        int u = q.top().second;
        q.pop();
        if (!g.v[u].inQueue) continue;
        g.v[u].inQueue = false;
        for (int i = 0; i < g.m; i++) {
            int x = g.muchii[i].u;
            int y = g.muchii[i].v;
            int w = g.muchii[i].w;

            int v = -1;
            if (x == u) v = y;
            else if (y == u) v = x;
            else continue;

            if (g.v[v].inQueue && w < g.v[v].key) {
                g.v[v].pi = u;
                g.v[v].key = w;
                q.push({ g.v[v].key, v });
            }
        }
    }
    for (int i = 0; i < g.n; i++) {
        if (g.v[i].pi != -1)
        {
            cost += g.v[i].key;
            nr++;
        }
    }
    return cost;
}
int main()
{
    Graf g;
    int r;
    in >> g.n >> g.m;
    for (int i = 0;i < g.m;i++)
        in >> g.muchii[i].u >> g.muchii[i].v >> g.muchii[i].w;

    int cost, nr;
    mst_prim(g, 0,cost,nr);
    out << cost << endl<<nr<<endl;
    for (int i = 0;i < g.n;i++)
        if (g.v[i].pi != -1)
            out << g.v[i].pi << " " << i << endl;
}

