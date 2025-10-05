#include <iostream>
#include <fstream>
using namespace std;
ifstream in("graf.txt");

#define INFINIT 200
#include <queue>
//typedef struct
//{
//    int ind;
//    char color[20];
//    int d;
//    int pi;
//} nod;

typedef struct
{
    int v1, v2;
} muchie;

typedef struct
{
    muchie E[200];
    int V[100];
    int adj[100][100]; 
    int n, m;          // n = număr noduri, m = număr muchii
} Graf;

void Moore(Graf G, int u, int I[100], int p[100])
{
    for (int i = 1;i <= G.n;i++)
    {
        I[i] = INFINIT;
        p[i] = -1;
    }
    I[u] = 0;
    queue<int>Q;
    Q.push(u);

    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for (int i = 1;i <= G.n;i++)
        {
            if (G.adj[x][i] == 1)
            {
                if(I[i] == INFINIT)
                {
                    p[i] = x;
                    I[i] = I[x] + 1;
                    Q.push(i);
                }
            }
        }

    }
}

void MooreDrum(int I[100], int p[100], int v,int u[100])
{
    int k = I[v];
    u[k] = v;
    while (k != 0)
    {
        u[k - 1] = p[u[k]];
        k = k - 1;
    }
}

void AfiseazaDrum(int u[100], int k)
{
    cout << "Cel mai scurt drum este: ";
    for (int i = 0; i <= k; i++)
    {
        cout << u[i] << (i == k ? "" : " -> ");
    }
    cout << endl;
}

int main()
{
    Graf G;
    int x, y;
    in >> G.n;
    G.m = 0;
    for (int i = 1;i <= G.n;i++)
    {
        for (int j = 1;j <= G.n;j++)
            G.adj[i][j] = 0;
    }
    while (in >> x >> y)
    {
        G.m++;
        G.adj[x][y] = 1;
    }

    int I[100], p[100], u[100];
    Moore(G, 2, I, p);
    MooreDrum(I, p, 3, u);


    int k = I[3]; // Distanța de la nodul 1 la nodul 3
    AfiseazaDrum(u, k); 
}


