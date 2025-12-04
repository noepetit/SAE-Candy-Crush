#include <iostream>
#include <vector>
#include <random>
using namespace std;

typedef vector<unsigned> line;
typedef vector<line> mat;
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

void couleur (const unsigned & coul)
{
    cout << "\033[" << coul <<"m";
}

int main() {
    mat grille(7, line(7));

    cout << "  | ";
    for (unsigned j = 0; j < grille[0].size(); ++j)
    {
        cout << j << " ";
    }
    cout << endl;

    cout << "--+-";
    for (unsigned j = 0; j < grille[0].size(); ++j)
    {
        cout << "--";
    }
    cout << endl;

    for (unsigned i = 0; i < grille.size(); ++i)
    {
        cout << i << " | ";
        for (unsigned j = 0; j < grille[i].size(); ++j)
        {
            grille[i][j] = rand() % 10;
            cout << grille[i][j] << " ";
        }
        cout << endl;
    }
}
