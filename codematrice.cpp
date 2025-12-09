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

void initGrid(mat &grille, const size_t &matSize, const int nbBonbon)
{
    grille.resize(matSize);
    for (unsigned i = 0; i < matSize; ++i)
    {
        grille[i].resize(matSize);
        for (unsigned j = 0; j < matSize; ++j)
        {
            grille[i][j] = rand() % nbBonbon;
        }
    }
}


void displayGrid (mat grille)
{
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
            cout << grille[i][j] << " ";
        }
        cout << endl;
    }
}


int main() 
{
    const int nbBonbon = 7;
    mat grille;
    const size_t matSize = 7;
    initGrid(grille, matSize, nbBonbon);
    displayGrid(grille);
    return 0;
}
