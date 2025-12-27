#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

typedef vector<unsigned> line;
typedef vector<line> mat;
struct maPosition { 
unsigned abs;
unsigned ord;
};


const unsigned KReset   (0);


void couleur (const unsigned & coul) {
    cout << "\033[" << coul << "m";
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

void couleurBonbon(int num) {
    switch (num) {
    case 0: couleur(41); break; // rouge
    case 1: couleur(42); break; // vert
    case 2: couleur(43); break; // jaune
    case 3: couleur(44); break; // bleu
    case 4: couleur(45); break; // magenta
    case 5: couleur(46); break; // cyan
    default: couleur(47); break; // blanc
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
            int num = grille[i][j];
            couleurBonbon(num);
            cout << grille[i][j] << " ";
            couleur(KReset);
        }
        cout << endl;
    }
}

void makeAMove (mat & grid, const maPosition & pos, const char & direction){

    switch (direction)
    {
    case 'z':
        if (pos.ord > 0) {
            swap(grid[pos.ord][pos.abs], grid[pos.ord - 1][pos.abs]);
        }
        break;
    case 's':
        if (pos.ord + 1 < grid.size()) {
            swap(grid[pos.ord][pos.abs], grid[pos.ord + 1][pos.abs]);
        }
        break;
    case 'q':
        if (pos.abs > 0) {
            swap(grid[pos.ord][pos.abs], grid[pos.ord][pos.abs - 1]);
        }
        break;
    case 'd':
        if (pos.abs + 1 < grid[0].size()) {
            swap(grid[pos.ord][pos.abs], grid[pos.ord][pos.abs + 1]);
        }
        break;

    default:
        //attente d'une direction
        break;
    }
}


bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany){
    for (size_t i = 0; i < grid.size(); ++i)
    {
        unsigned int cpt = 1;
        for (size_t j = 1; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == grid[i][j - 1]) {
                cpt++;
            }
            else {
                if (cpt >= 3) {
                    pos.abs = i;
                    pos.ord = j - cpt;
                    howMany = cpt;
                    return true;
            }
            cpt = 1;
            }
        }
        if (cpt >= 3) {
            pos.abs = i;
            pos.ord = grid[i].size() - cpt;
            howMany = cpt;
            return true;
        }
    }
    return false;
}

int main() {
    const int nbBonbon = 6;
    mat grille;
    const size_t matSize = 7;
    initGrid(grille, matSize, nbBonbon);
    displayGrid(grille);
    return 0;
}
