#include <iostream>
#include <fstream>
#define INF 1000
using namespace std;

ifstream in("input2.txt");

int main()
{
    int n, x, y, m, nr_vec[100] = { 0 },list_adj[100][100],adj[100][100];
    m = 0;
    in >> n;
    for (int i = 1;i <= n;i++)
        for (int j = 1;j <= n;j++)
            adj[i][j] = 0;
    while (in >> x >> y)
    {
        m++;
        nr_vec[x] += 1;
        list_adj[x][nr_vec[x]] = y;
        adj[x][y] = 1;
    }
    cout << "Matrice de adiacenta: " << endl;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= n;j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
    cout << "Noduri izolate: ";
    for (int i = 1;i <= n;i++)
        if (nr_vec[i] == 0)
            cout << i << " ";
    cout << endl;
    int ok = 1;
    for (int i = 1;i < n;i++)
        if (nr_vec[i] != nr_vec[i + 1])
            ok = 0;
    if (ok == 0)
        cout << "Graful nu este regular";
    else
        cout << "Graful este regular";
    cout << endl;

    int dist[100][100];

    for (int i = 1;i <= n;i++)
        for (int j = 1;j <= n;j++)
            if (adj[i][j] == 1)
                dist[i][j] = 1;
            else if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;

    for (int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    cout << "Matricea distantelor: " << endl;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= n;j++)
            cout << dist[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    ok = 1;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= n;j++)
            if (i!=j and dist[i][j]==INF)
                ok = 0;
    }
    if (ok == 0)
        cout << "Graful nu este conex";
    else
        cout << "Graful este conex";
    return 0;
}
