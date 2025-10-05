#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#define INFINIT 200
using namespace std;
ifstream in("D:\\algoritmica grafelor\\lab_03\\problema1\\graf.txt");
ofstream out("D:\\algoritmica grafelor\\lab_03\\problema1\\out.txt");

typedef struct
{
    int ind;
    char color[20];
    int d;
    int pi;
} nod;

typedef struct
{
    int v1, v2,cost;
} muchie;

typedef struct
{
    map<pair<int, int>, int> muchie;
    int nr_vec[100];
    vector<vector<int>>lista;
    int n, m;          
} Graf;

void Dijkstra(Graf G, int u,vector<int>&I,vector<int> &P)
{
    vector<int>s,t;
    s.push_back(u);
    for (int i = 0;i < G.n;i++)
        if (i != u)
        {
            t.push_back(i);
        }
    int x = u;
    while (!t.empty())
    {
        int ok = 1;
        for (int i = 0;i <G.nr_vec[x];i++)
        {
            for (int j = 0;j < t.size();j++)
                if (G.lista[x][i] == t[j])
                    ok = 0;
            if (ok == 1)
            {
                if (I[i] > I[x] + G.muchie[{x, i}])
                {
                    I[i] = I[x] + G.muchie[{x, i}];
                    P[i] = x;
                }
            }
        }
        int minn = INFINIT;
        for (int i = 0;i < t.size();i++)
            if (I[t[i]] < minn)
                minn = I[t[i]];
        x = t.back();
        t.pop_back();
        I[x] = minn;
        s.push_back(x);
    }
    for (int i = 0;i < I.size();i++)
        cout << I[i] << " ";

}
int main()
{
    Graf G;
    in >> G.n >> G.m;

    int x,y,cost,start;
    in >> start;
    G.lista.resize(G.n + 1);  
    //G.nr_vec.resize(G.n + 1, 0);
    for (int i = 0;i <G.m;i++)
    {
        in >>x >> y>>cost;
        G.muchie[{x, y}] = cost;
        G.muchie[{y, x}] = cost;
        G.nr_vec[x] += 1;
        G.nr_vec[y] += 1;
        G.lista[x].push_back(y);
        G.lista[y].push_back(x);
    }
    vector<int>I;
    vector<int>p;
    for (int i = 0;i < G.n;i++)
    {
        I.push_back(INFINIT);
        p.push_back(-1);
    }
    I[start] = 0;
    Dijkstra(G, start, I, p);
    for (int i = 0;i < I.size();i++)
        if (I[i] == INFINIT)
            out << "INF" << " ";
        else
            out << I[i] << " ";
}


