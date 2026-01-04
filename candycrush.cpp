#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

typedef vector<unsigned> line;
typedef vector<line> mat;

struct maPosition
{
    unsigned abs; // ligne
    unsigned ord; // colonne
};

const unsigned KReset(0);
const unsigned KImpossible(999); // valeur "vide"

void couleur(const unsigned & coul)
{
    cout << "\033[" << coul << "m";
}

void couleurBonbon(int num)
{
    switch (num)
    {
        case 0: couleur(41); break;
        case 1: couleur(42); break;
        case 2: couleur(43); break;
        case 3: couleur(44); break;
        case 4: couleur(45); break;
        case 5: couleur(46); break;
        default: couleur(47); break;
    }
}
void initGrid(mat &grille, const size_t &matSize, const int nbBonbon)
{
    grille.resize(matSize);
    for (unsigned i = 0; i < matSize; ++i)
    {
        grille[i].resize(matSize);
        for (unsigned j = 0; j < matSize; ++j)
        {
            unsigned val;
            while (true)
            {
                 val = rand() % nbBonbon;
                // Vérification horizontale (à gauche)
                bool suiteHorizontale = (j >= 2 && val == grille[i][j-1] && val == grille[i][j-2]);
                
                // Vérification verticale (au-dessus)
                bool suiteVerticale = (i >= 2 && val == grille[i-1][j] && val == grille[i-2][j]);
    
                // Si aucune de ces conditions n'est vraie, le nombre est bon !
                if (!suiteHorizontale && !suiteVerticale) break;
            }
            grille[i][j] = val;
        }
    }
}

void displayGrid(const mat& grille)
{
    cout << "  | ";
    for (unsigned j = 0; j < grille[0].size(); ++j) cout << j + 1 << " ";
    cout << endl << "--+";
    for (unsigned j = 0; j < grille[0].size(); ++j) cout << "--";
    cout << endl;

    for (unsigned i = 0; i < grille.size(); ++i)
    {
        cout << i + 1 << " | ";
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

void makeAMove(mat & grid, const maPosition & pos, const char & direction)
{
    switch (direction)
    {
        case 'z': case 'Z':
            if (pos.abs > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs - 1][pos.ord]);
            else cout << "Bord atteint !" << endl; // Optionnel : prévenir le joueur
            break;
        case 's': case 'S':
            if (pos.abs + 1 < grid.size()) swap(grid[pos.abs][pos.ord], grid[pos.abs + 1][pos.ord]);
            else cout << "Bord atteint !" << endl;
            break;
        case 'q': case 'Q':
            if (pos.ord > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord - 1]);
            else cout << "Bord atteint !" << endl;
            break;
        case 'd': case 'D':
            if (pos.ord + 1 < grid[0].size()) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord + 1]);
            else cout << "Bord atteint !" << endl;
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

bool atLeastThreeInAColumn(const mat & grid, maPosition & pos, unsigned & howMany)
{
    for (size_t j = 0; j < grid[0].size(); ++j)
    {
        unsigned cpt = 1;
        for (size_t i = 1; i < grid.size(); ++i)
        {
            if (grid[i][j] == grid[i - 1][j]) {
                cpt++;
            }
            else {
                if (cpt >= 3)
                {
                    pos.abs = i - cpt;
                    pos.ord = j;
                    howMany = cpt;
                    return true;
                }
                cpt = 1;
            }
        }
        if (cpt >= 3)
        {
            pos.abs = grid.size() - cpt;
            pos.ord = j;
            howMany = cpt;
            return true;
        }
    }
    return false;
}

void removalInColumn(mat & grid, const maPosition & pos, unsigned howMany)
{
    if (pos.ord + howMany > grid.size())
    {
        return;
    }
    for (unsigned i = pos.ord; i + howMany < grid.size(); ++i)
    {
        grid[i][pos.abs] = grid[i + howMany][pos.abs];
    }
    for (unsigned i = grid.size() - howMany; i < grid.size(); ++i)
    {
        grid[i][pos.abs] = KImpossible ;
    }
}

void removalInRow(mat & grid, const maPosition & pos, unsigned howMany)
{
    for ( unsigned colone = pos.abs; colone <pos.abs + howMany; ++colone)
    {
        removalInColumn(grid, {pos.ord, colone}, 1);

    }
}

int main ()
{
    srand((unsigned)time(0));
    const unsigned nbBonbon = 6;
    const size_t matSize = 7;

    mat grille;
    initGrid(grille, matSize, nbBonbon);

    int nbTours = 10;
    unsigned points = 0;
    while (nbTours > 0)
    {
        displayGrid(grille);
        cout << endl << "Points : " << points << " | Tours : " << nbTours << endl;
        maPosition pos;
        char direction;
        cout << "Ligne (1-7) : ";
        if(!(cin >> pos.abs) || pos.abs < 1 || pos.abs > matSize)
        {
            cout << "Ligne non existante" << endl;
            continue;
        } 

        cout << "Colonne (1-7) : ";
        if(!(cin >> pos.ord) || pos.ord < 1 || pos.ord > matSize)
        { 
            cout << "Colonne non existante" << endl;
            continue;
        }

        cout << "Direction (z = haut, q = gauche, s = bas, d = droite) : ";
        cin >> direction;
        if (direction != 'z' && direction != 's' && direction != 'q' && direction != 'd' &&
            direction != 'Z' && direction != 'S' && direction != 'Q' && direction != 'D') 
        {
            cout << "direction invalide !" << endl;
            continue;
        }
        pos.abs--; pos.ord--;
    }
}
