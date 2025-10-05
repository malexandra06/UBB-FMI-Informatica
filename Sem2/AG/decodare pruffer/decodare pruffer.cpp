#include <iostream>
#include <fstream>

using namespace std;
ifstream in("graf.in");
ofstream out("graf.out");

int t[100], k[100], fr[100];

int minim(int k[], int n)
{
    for (int i = 0; i < n; i++)
        fr[i] = 0;
    for (int i = 0; i < n; i++)
        fr[k[i]]++;
    for (int i = 0; i < n; i++)
        if (fr[i] == 0)
            return i;

}

void decodarePrufer(int k[], int t[], int& n)
{
    for (int i = 0; i < n; i++)
    {
        int x = k[0]; 
        int y = minim(k, n); 
        t[y] = x;  
        for (int i = 0; i < n; i++)
            k[i] = k[i + 1];  
        k[n - 1] = y;  
    }

}
int main()
{
    int n, x;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> x;
        k[i] = x;  
        t[i] = -1;  
    }

    decodarePrufer(k, t, n);
    out << n + 1 << "\n";
    for (int i = 0; i <= n; i++)
        out << t[i] << " ";


    return 0;
}