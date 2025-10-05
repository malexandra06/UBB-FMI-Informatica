#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>

#define INF 10000
using namespace std;

const int dx[] = { -1, 1, 0, 0 }; // Direcții: sus, jos, stânga, dreapta
const int dy[] = { 0, 0, -1, 1 };

struct Point {
    int x, y;
};

void Lee(vector<string>& lab, vector<vector<int>>& viz, int m, int n, int istart, int jstart, int ifinal, int jfinal) {
    queue<Point> q;
    q.push({ istart, jstart });
    viz[istart][jstart] = 0;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n && lab[nx][ny] != '1') {
                if (viz[nx][ny] > viz[current.x][current.y] + 1) {
                    viz[nx][ny] = viz[current.x][current.y] + 1;
                    q.push({ nx, ny });

                    if (nx == ifinal && ny == jfinal)
                        return;
                }
            }
        }
    }
}

void reconstructPath(vector<string>& lab, vector<vector<int>>& viz, int ifinal, int jfinal, int istart, int jstart) {
    int x = ifinal, y = jfinal;

    while (!(x == istart && y == jstart)) {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && viz[nx][ny] == viz[x][y] - 1) {
                lab[nx][ny] = '*'; // Marcare drum
                x = nx;
                y = ny;
                break;
            }
        }
    }
}

int main() {
    string filename;
    cout << "Introduceti numele fisierului cu labirintul (ex: labirint_1.txt): ";
    cin >> filename;

    ifstream in(filename);
    if (!in) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << filename << endl;
        return 1;
    }

    vector<string> lab;
    string line;
    while (getline(in, line)) {
        lab.push_back(line);
    }
    in.close();

    int m = lab.size();
    int n = (m > 0) ? lab[0].size() : 0;

    int istart = -1, jstart = -1, ifinal = -1, jfinal = -1;
    vector<vector<int>> viz(m, vector<int>(n, INF));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (lab[i][j] == 'S') {
                istart = i;
                jstart = j;
            }
            if (lab[i][j] == 'F') {
                ifinal = i;
                jfinal = j;
            }
        }
    }

    if (istart == -1 || ifinal == -1) {
        cerr << "Eroare: Nu s-au gasit punctele S si F in labirint" << endl;
        return 1;
    }

    Lee(lab, viz, m, n, istart, jstart, ifinal, jfinal);

    if (viz[ifinal][jfinal] == INF) {
        cout << "Labirintul nu are solutie!" << endl;
        return 0;
    }

    reconstructPath(lab, viz, ifinal, jfinal, istart, jstart);

    // Afișare labirint cu soluția marcată
    cout << "\nSolutie labirint:\n";
    for (const auto& row : lab)
        cout << row << endl;

    cout << "Distanta minima: " << viz[ifinal][jfinal] << endl;
    return 0;
}
