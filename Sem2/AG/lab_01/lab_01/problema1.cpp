#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ifstream fin("input.txt");
int main()
{
    int n,m,x,y;
 
    in >> n>>m;
    int lista_adj[100][100], nr_vec[100] = { 0 };
    int a[100][100];
    int mat_ind[100][200];

    for (int i = 1;i <= n;i++)
        for (int j = i;j <= n;j++)
            a[i][j] = a[j][i]=0;

    for (int i = 1;i <= n;i++)
        for (int j = 1;j <= m;j++)
            mat_ind[i][j] = 0;

    for (int i = 1;i <= m;i++)
    {
        in >> x >> y;
        a[x][y] = a[y][x] = 1;
        nr_vec[x] += 1;
        nr_vec[y] += 1;
        lista_adj[x][nr_vec[x]] = y;
        lista_adj[y][nr_vec[y]] = x;
        mat_ind[x][i] = mat_ind[y][i]=1;
    }
    cout << "Matrice de adiacenta: " << endl;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= n;j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    
    cout << "Lista de adiacenta: " << endl;
    for (int i = 1;i <= n;i++)
    {
        cout << i << ": ";
        for (int j = 1;j <= nr_vec[i];j++)
            cout << lista_adj[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    cout << "Matrice de incidenta: " << endl;
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= m;j++)
            cout << mat_ind[i][j] << " ";
        cout << endl;
    }

    return 0;
}
