#include <iostream>
#include <fstream>
using namespace std;
ifstream in("input.txt");

int main()
{
	int adj[100][100],n,m,x,y;
	in >> n >> m;
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
		{
			adj[i][j] = 0;
			if (i == j)
				adj[i][j] = 1;
		}

	for (int i = 1;i <= m;i++)
	{
		in >> x >> y;
		adj[x][y] = 1;
	}
	in.close();
	for (int k = 0;k < n;k++)
		for (int i = 0;i < n;i++)
			for (int j = 0;j < n;j++)
				if (adj[i][j] == 0 and adj[i][k] == 1 and adj[k][j] == 1)
					adj[i][j] = 1;

	cout << "Matricea tranzitiva:" << endl;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
			cout << adj[i][j] << " ";
		cout << endl;
	}
	return 0;
}