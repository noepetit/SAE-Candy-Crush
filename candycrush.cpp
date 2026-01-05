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

void couleur(const unsigned & coul)
{
    cout << "\033[" << coul << "m";
}

void clearScreen () {
    cout << "\033[H\033[2J";
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

void couleurBonbonInverse(int num)
{
    switch (num)
    {

    case 0: couleur(41); break;
    case 1: couleur(42); break;
    case 2: couleur(44); break;
    case 3: couleur(46); break;
    case 4: couleur(45); break;
    case 5: couleur(41); break;
    default: couleur(47); break;
    }
}

void initGrid(mat &grille, const size_t &matSize, const int nbBonbon)
{
    srand(time(0));
    grille.resize(matSize);
    for (unsigned i = 0; i < matSize; ++i) //i = ligne
    {
        grille[i].resize(matSize);
        for (unsigned j = 0; j < matSize; ++j) //j = colonne
        {
            unsigned val;
            while (true)
            {
                val = rand() % nbBonbon;
                // Vérification horizontale
                bool suiteHorizontale = (j >= 2 && val == grille[i][j-1] && val == grille[i][j-2]);

                // Vérification verticale
                bool suiteVerticale = (i >= 2 && val == grille[i-1][j] && val == grille[i-2][j]);

                if (!suiteHorizontale && !suiteVerticale) break;
            }
            grille[i][j] = val;
        }
    }
}

void displayGrid(const mat& grille, bool inverse)
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
            if (inverse)
            {
                couleurBonbonInverse(num);
            }
            else
            {
                couleurBonbon(num);
            }
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
        else cout << "Bord atteint" << endl;
        break;
    case 's': case 'S':
        if (pos.abs + 1 < grid.size()) swap(grid[pos.abs][pos.ord], grid[pos.abs + 1][pos.ord]);
        else cout << "Bord atteint" << endl;
        break;
    case 'q': case 'Q':
        if (pos.ord > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord - 1]);
        else cout << "Bord atteint" << endl;
        break;
    case 'd': case 'D':
        if (pos.ord + 1 < grid[0].size()) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord + 1]);
        else cout << "Bord atteint" << endl;
        break;
    case 'e': case 'E':
        break;
    }
}


void makeAMoveInverse(mat & grid, const maPosition & pos, const char & direction)
{
    switch (direction)
    {
    case 'e': case 'E':
        break;

    case 'z': case 'Z':
        if (pos.abs + 1 < grid.size()) swap(grid[pos.abs][pos.ord], grid[pos.abs + 1][pos.ord]);
        else cout << "Bord atteint" << endl;
        break;

    case 's': case 'S':
        if (pos.abs > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs - 1][pos.ord]);
        else cout << "Bord atteint" << endl;
        break;

    case 'q': case 'Q':
        if (pos.ord + 1 < grid[0].size()) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord + 1]);
        else cout << "Bord atteint" << endl;
        break;

    case 'd': case 'D':
        if (pos.ord > 0) swap(grid[pos.abs][pos.ord], grid[pos.abs][pos.ord - 1]);
        else cout << "Bord atteint" << endl;
        break;
    }
}

bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany)
{
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
    if (pos.abs + howMany > grid.size()) return;

    for (unsigned i = pos.abs; i + howMany < grid.size(); ++i)
    {
        grid[i][pos.ord] = grid[i + howMany][pos.ord];
    }

    for (unsigned i = grid.size() - howMany; i < grid.size(); ++i)
    {
        grid[i][pos.ord] = rand() % 6; // Nombre généré aleatoirement aprés la supression
    }
}

void removalInRow(mat & grid, const maPosition & pos, unsigned howMany)
{
    for (unsigned colonne = pos.ord; colonne < pos.ord + howMany; ++colonne)
    {
        removalInColumn(grid, {pos.abs, colonne}, 1);
    }
}

void modeClassique()
{
    const unsigned nbBonbon = 6;
    const size_t matSize = 7;

    mat grille;
    initGrid(grille, matSize, nbBonbon);

    int nbTours = 8;
    unsigned points = 0;
    clearScreen();
    while (nbTours > 0)
    {
        displayGrid(grille, false);
        cout << endl << "Points : " << points << " | Tours restants : " << nbTours << endl;
        maPosition pos;
        char direction;
        cout << "Ligne (1-7) : ";
        if(!(cin >> pos.abs) || pos.abs < 1 || pos.abs > matSize)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "Ligne non existante" << endl;
            continue;
        }

        cout << "Colonne (1-7) : ";
        if(!(cin >> pos.ord) || pos.ord < 1 || pos.ord > matSize)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "Colonne non existante" << endl;
            continue;
        }

        cout << "Direction (z = haut, q = gauche, s = bas, d = droite, e = quitter) : ";
        cin >> direction;
        if (direction == 'e' || direction == 'E')
        {
            clearScreen();
            return; // Retour au menu
        }
        if (direction != 'z' && direction != 's' && direction != 'q' && direction != 'd' &&
            direction != 'Z' && direction != 'S' && direction != 'Q' && direction != 'D')
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "direction invalide" << endl;
            continue;
        }
        pos.abs--; pos.ord--;
        mat grilleAvantCoup = grille;
        makeAMove(grille, pos, direction);
        maPosition position;
        unsigned howMany;
        // Pas de suite trouvée
        if (!atLeastThreeInARow(grille, position, howMany) &&
            !atLeastThreeInAColumn(grille, position, howMany))
        {
            clearScreen();
            cout << endl << "Coup invalide" << endl;
            grille = grilleAvantCoup;
            continue;
        }

        // Boucle pour les réactions en chaine
        while (true)
        {
            maPosition position;
            unsigned howMany;

            // alignement horizontal
            if (atLeastThreeInARow(grille, position, howMany))
            {
                unsigned numero = grille[position.abs][position.ord];
                unsigned gain = ((numero) * howMany) * howMany; // Calcul des points
                removalInRow(grille, position, howMany);
                points += gain;

                cout << endl;
            }
            // alignement vertical
            else if (atLeastThreeInAColumn(grille, position, howMany))
            {
                unsigned numero = grille[position.abs][position.ord];
                unsigned gain = ((numero) * howMany) * howMany;
                removalInColumn(grille, position, howMany);
                points += gain;

                cout << endl;
            }
            // Aucun alignement trouvé
            else
            {
                break;
            }
        }
        nbTours--;
    }
    cout << "Partie terminée avec " << points << "points !";
}

void modeInverse()
{
    const unsigned nbBonbon = 6;
    const size_t matSize = 7;

    mat grille;
    initGrid(grille, matSize, nbBonbon);

    int nbTours = 8;
    unsigned points = 0;
    clearScreen();
    while (nbTours > 0)
    {
        displayGrid(grille, true);
        cout << endl << "Points : " << points << " | Tours restants : " << nbTours << endl;
        maPosition pos;
        char direction;
        cout << "Ligne (1-7) : ";
        if(!(cin >> pos.abs) || pos.abs < 1 || pos.abs > matSize)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "Ligne non existante" << endl;
            continue;
        }

        cout << "Colonne (1-7) : ";
        if(!(cin >> pos.ord) || pos.ord < 1 || pos.ord > matSize)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "Colonne non existante" << endl;
            continue;
        }

        cout << "Direction (z = haut, q = gauche, s = bas, d = droite, e = quitter) : ";
        cin >> direction;
        if (direction == 'e' || direction == 'E')
        {
            clearScreen();
            return; // Retour au menu
        }
        if (direction != 'z' && direction != 's' && direction != 'q' && direction != 'd' &&
            direction != 'Z' && direction != 'S' && direction != 'Q' && direction != 'D')
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "direction invalide" << endl;
            continue;
        }
        pos.abs--; pos.ord--;
        mat grilleAvantCoup = grille;
        makeAMoveInverse(grille, pos, direction);
        maPosition position;
        unsigned howMany;
        // Pas de suite trouvée
        if (!atLeastThreeInARow(grille, position, howMany) &&
            !atLeastThreeInAColumn(grille, position, howMany))
        {
            clearScreen();
            cout << endl << "Coup invalide" << endl;
            grille = grilleAvantCoup;
            continue;
        }

        // Boucle pour les réactions en chaine
        while (true)
        {
            maPosition position;
            unsigned howMany;

            // alignement horizontal
            if (atLeastThreeInARow(grille, position, howMany))
            {
                unsigned numero = grille[position.abs][position.ord];
                int scoreParNumero;

                switch (numero)
                {
                case 0: scoreParNumero = 5;  break;
                case 1: scoreParNumero = 4;  break;
                case 2: scoreParNumero = 3;  break;
                case 3: scoreParNumero = 2;  break;
                case 4: scoreParNumero = 1;  break;
                case 5: scoreParNumero = -1; break;
                default: scoreParNumero = 0; break;
                }

                int gain = (scoreParNumero*howMany)*howMany;

                removalInRow(grille, position, howMany);
                points += gain;

                cout << endl;
            }
            // alignement vertical
            else if (atLeastThreeInAColumn(grille, position, howMany))
            {
                unsigned numero = grille[position.abs][position.ord];
                int scoreParNumero;

                switch (numero)
                {
                case 0: scoreParNumero = 5;  break;
                case 1: scoreParNumero = 4;  break;
                case 2: scoreParNumero = 3;  break;
                case 3: scoreParNumero = 2;  break;
                case 4: scoreParNumero = 1;  break;
                case 5: scoreParNumero = -1; break;
                default: scoreParNumero = 0; break;
                }

                int gain = (scoreParNumero*howMany)*howMany;

                removalInColumn(grille, position, howMany);
                points += gain;

                cout << endl;
            }
            // Aucun alignement trouvé
            else
            {
                break;
            }
        }
        nbTours--;
    }
    cout << "Partie terminée avec " << points << "points !";
}

void modeInfini ()
{
    const unsigned nbBonbon = 6;
    const size_t matSize = 7;

    mat grille;
    initGrid(grille, matSize, nbBonbon);

    unsigned nbTours = 0;
    unsigned points = 0;
    clearScreen();
    while (true)
    {
        displayGrid(grille, false);
        cout << endl << "Points : " << points << " | Tours : " << nbTours << endl;
        maPosition pos;
        char direction;
        cout << "Ligne (1-7) : ";
        if(!(cin >> pos.abs) || pos.abs < 1 || pos.abs > matSize)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "Ligne non existante" << endl;
            continue;
        }

        cout << "Colonne (1-7) : ";
        if(!(cin >> pos.ord) || pos.ord < 1 || pos.ord > matSize)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "Colonne non existante" << endl;
            continue;
        }

        cout << "Direction (zqsd, e = quitter) : ";
        cin >> direction;
        if (direction == 'e' || direction == 'E')
        {
            clearScreen();
            return; // Retour au menu
        }
        if (direction != 'z' && direction != 's' && direction != 'q' && direction != 'd' &&
            direction != 'Z' && direction != 'S' && direction != 'Q' && direction != 'D')
        {
            cin.clear();
            cin.ignore(1000, '\n');
            clearScreen();
            cout << "direction invalide" << endl;
            continue;
        }
        pos.abs--; pos.ord--;
        mat grilleAvantCoup = grille;
        makeAMove(grille, pos, direction);
        maPosition position;
        unsigned howMany;
        // Pas de suite trouvée
        if (!atLeastThreeInARow(grille, position, howMany) &&
            !atLeastThreeInAColumn(grille, position, howMany))
        {
            clearScreen();
            cout << endl << "Coup invalide" << endl;
            grille = grilleAvantCoup;
            continue;
        }

        // Boucle pour les réactions en chaîne
        while (true)
        {
            maPosition position;
            unsigned howMany;

            // alignement horizontal
            if (atLeastThreeInARow(grille, position, howMany))
            {
                unsigned numero = grille[position.abs][position.ord];
                unsigned gain = numero* howMany; // Calcul des points
                removalInRow(grille, position, howMany);
                points += gain;

                cout << endl;
            }
            // alignement vertical
            else if (atLeastThreeInAColumn(grille, position, howMany))
            {
                unsigned numero = grille[position.abs][position.ord];
                unsigned gain = numero*howMany;
                removalInColumn(grille, position, howMany);
                points += gain;

                cout << endl;
            }
            // Aucun alignement trouvé
            else
            {
                break;
            }
        }
        nbTours++;
    }
    cout << "Partie terminée avec " << points << "points !";
}


int main ()
{
    unsigned choix;
    while (true)
    {
        cout << "Menu Principale" << endl;
        cout << endl;
        cout << "1-Mode classique" << endl;
        cout << "2-Mode inversé" << endl;
        cout << "3-Mode infini" << endl;
        cout << "Choissisez votre mode : ";
        if (!(cin >> choix) || choix > 3 || choix < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Choix entre 3 nombres et t'as quand meme echoué...";
            return 0;
        }
        switch (choix)
        {
        case 1:
            clearScreen();
            modeClassique();
            break;
        case 2:
            clearScreen();
            modeInverse();
            break;
        case 3:
            clearScreen();
            modeInfini();
            break;
        default:
            break;
        }
    }
    return 0;
}
