#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<unsigned> line;
typedef vector<line> mat;

struct maPosition {
    unsigned abs; // ligne
    unsigned ord; // colonne
};

const unsigned KReset(0);
const unsigned KImpossible(999); // valeur "vide"

// ----------- fonctions utilitaires (les tiennes) -----------

void couleur (const unsigned & coul) { cout << "\033[" << coul << "m"; }

void couleurBonbon(int num) {
    switch (num) {
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
            val = rand() % nbBonbon;

            grille[i][j] = val;
        }
    }
}

void displayGrid (mat grille)
{
    cout << "  | ";
    for (unsigned j = 0; j < grille[0].size(); ++j) cout << j << " ";
    cout << "\n--+-";
    for (unsigned j = 0; j < grille[0].size(); ++j) cout << "--";
    cout << "\n";

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
        cout << "\n";
    }
}

void makeAMove (mat & grid, const maPosition & pos, const char & direction)
{
    switch (direction)
    {
    case 'z': case 'Z':
        if (pos.abs > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs - 1][pos.ord]);
        break;
    case 's': case 'S':
        if (pos.abs + 1 < grid.size()) swap(grid[pos.abs][pos.ord], grid[pos.abs + 1][pos.ord]);
        break;
    case 'q': case 'Q':
        if (pos.ord > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord - 1]);
        break;
    case 'd': case 'D':
        if (pos.ord + 1 < grid[0].size()) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord + 1]);
        break;
    default:
        break;
    }
}

bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany)
{
    for (size_t i = 0; i < grid.size(); ++i)
    {
        unsigned cpt = 1;
        for (size_t j = 1; j < grid[i].size(); ++j)
        {
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i][j - 1]) cpt++;
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

bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany)
{
    for (size_t j = 0; j < grid[0].size(); ++j)
    {
        unsigned cpt = 1;
        for (size_t i = 1; i < grid.size(); ++i)
        {
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i - 1][j]) cpt++;
            else {
                if (cpt >= 3) {
                    pos.abs = i - cpt;
                    pos.ord = j;
                    howMany = cpt;
                    return true;
                }
                cpt = 1;
            }
        }
        if (cpt >= 3) {
            pos.abs = grid.size() - cpt;
            pos.ord = j;
            howMany = cpt;
            return true;
        }
    }
    return false;
}

// ----------- suppressions -----------

void removalInColumn(mat & grid, const maPosition & pos, unsigned howMany, unsigned nbBonbon)
{
    const unsigned nRows = grid.size();
    const unsigned col   = pos.ord; // colonne
    const unsigned start = pos.abs; // ligne départ

    if (nRows == 0) return;
    if (col >= grid[0].size()) return;
    if (start >= nRows) return;
    if (howMany == 0) return;
    if (start + howMany > nRows) howMany = nRows - start;

    for (unsigned r = start + howMany; r < nRows; ++r)
        grid[r - howMany][col] = grid[r][col];

    for (unsigned r = nRows - howMany; r < nRows; ++r)
        grid[r][col] = rand() % nbBonbon;
}

void removalInRow(mat & grid, const maPosition & pos, unsigned howMany, unsigned nbBonbon)
{
    if (grid.empty()) return;

    const unsigned nRows = grid.size();
    const unsigned nCols = grid[0].size();
    const unsigned row   = pos.abs; // ligne
    const unsigned start = pos.ord; // colonne départ

    if (row >= nRows) return;
    if (start >= nCols) return;
    if (howMany == 0) return;
    if (start + howMany > nCols) howMany = nCols - start;

    for (unsigned c = start; c < start + howMany; ++c)
    {
        maPosition p{row, c};
        removalInColumn(grid, p, 1, nbBonbon);
    }
}

// ----------- MAIN -----------

int main()
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
        cout << "\n=========== GRILLE ==========\n";
        displayGrid(grille);

        cout << "\nPoints : " << points << "\n";
        cout << "Tours restants : " << nbTours << "\n\n";

        maPosition pos;
        char direction;

        cout << "Ligne (0-6) : ";
        cin >> pos.abs;
        cout << "Colonne (0-6) : ";
        cin >> pos.ord;
        cout << "Direction (z haut, s bas, q gauche, d droite) : ";
        cin >> direction;

        // coup joué
        makeAMove(grille, pos, direction);

        cout << "\n--- Après déplacement ---\n";
        displayGrid(grille);

        // on supprime tant qu'il y a des alignements (combo)
        bool didSomething = true;
        while (didSomething)
        {
            didSomething = false;

            maPosition foundPos;
            unsigned howMany;

            if (atLeastThreeInARow(grille, foundPos, howMany))
            {
                removalInRow(grille, foundPos, howMany, nbBonbon);
                points += 10 * howMany;
                didSomething = true;

                cout << "\n>>> Suppression LIGNE (" << howMany << ") à partir de ("
                     << foundPos.abs << "," << foundPos.ord << ")\n";
                displayGrid(grille);
            }
            else if (atLeastThreeInAColumn(grille, foundPos, howMany))
            {
                removalInColumn(grille, foundPos, howMany, nbBonbon);
                points += 10 * howMany;
                didSomething = true;

                cout << "\n>>> Suppression COLONNE (" << howMany << ") à partir de ("
                     << foundPos.abs << "," << foundPos.ord << ")\n";
                displayGrid(grille);
            }
        }

        cout << "\n--------------------------------\n";
        nbTours--;
    }

    cout << "\nFIN ! Score final = " << points << "\n";
    return 0;
}
