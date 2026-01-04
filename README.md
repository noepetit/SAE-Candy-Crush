
TD_01_E_08_PETIT_REGUIG.zip

Sae candy crush
SAE 1.01
Ce que l’on a fait : 
Durant cette SAE notre but était de reproduire le jeu Candy Crush en C++. Pour cela nous avons réalisé l'intégralité du TP lié, Prog 10, où nous avons écrit les corps de fonction demander, et personnaliser notre jeu. Pour réaliser le jeu, nous avions besoin de créer une matrice, où les nombres étaient choisis de manière aléatoire entre 0 et 5. Pour ce qui est du code, la documentation générée par doxygen se trouve dans le dossier. Pour pouvoir avancer durant les vacances et se partager le code on à créer un repository sur github, nous nous sommes appelé pour pouvoir avancer à deux et nous mettre d'accord sur les modes de jeu, le calcul du score, la répartition des tâches, etc. 

Les difficultés rencontrées : au début nous avons inversé le pos.abs et pos.ord, donc nous arrivions pas à comprendre pourquoi la matrice faisait toujours l’inverse que ce qu’on voulait. De plus, la matrice se répétait à chaque fois dans le terminal, cela n’était pas propre et on pouvait se perdre, donc nous avons décidé de l’effacer à chaque nouvelle action. nous avons aussi rencontré des difficultés dans les fonctions, lors des choix des directions et leur codage. Noé à rencontrer une difficulté lors de l'installation de QT creators sur MacOs, les kits étaient indisponible donc impossible de créer un projet, il a donc dû passer par les lignes de  commande pour directement les implanter.

Les règles du jeu :
Bienvenue dans notre Candy Crush, ce jeu de stratégie et de réflexion où l’objectif est de créer des combinaisons de nombres identiques entre 0 et 5, pour marquer des points, le but du jeu est de réaliser des combinaisons de nombre (compris entre 0 et 5) identiques sur une grille pour marquer des points et supprimer les chiffres de la grille. Le joueur gagne une fois que le nombre de tours est atteint (selon le mode de jeu). La grille est composée de lignes et de colonnes comportant des nombres aléatoires, sur une grille de 7x7. Les nombres rapportent un nombre de points qui est proportionnel à sa place entre 0 et 5, nous leur avons attribué une couleur en fonction des nombres, pour les commandes de direction ‘z’ pour aller en haut, ’s’ pour aller en bas, ‘d’ pour aller à droite et ‘q’ pour aller à gauche (selon les modes de jeu). Nous offrons différents modes de jeu, permettant de varier le jeu et sa difficulté, mais ils comportent tous un point commun :  on ne peut pas enchaîner les coups.



Les mode de jeux : 
Pour pousser le jeu plus loin, nous avons ajouté quelques modes de jeu.
Mode classic : 
Dans un premier temps, le mode classique se fait en 10 tours, il faut choisir la ligne puis la colonne et la direction, pour le score c’est la somme des chiffres alignés, multiplier par le nombre case. Par exemple : si on aligne le chiffre 3 sur 4 case, le scores sera de (3+3+3+3) x 4 = 36. dans le cas ou nous avons aligner plusieurs 0, le zéro prendra la valeur de 0, par exemple : si on aligne le chiffre 0 sur 3 cases, le score sera de (0+0+0) x 3 =0



Mode inversé : 
Dans un second temps, le mode de jeux inversé, ce mode de jeu invers toute les commande de direction, pour aller en haut c’est ‘s’, pour aller en bas c’est ‘z’, pour aller à gauche c’est ‘d’ et pour aller à droite c’est ‘q’. cela rajoute un peu de difficulté au jeu de base. Le calcule du score est le même, les couleurs au sein de la matrice elles sont aussi inversées entre elles. Le score dans ce mode de jeu lui est aussi inversé, le 5 vaut -1 point, le 4 vaut 1 point, le 3 vaut 2 points, le 2 vaut 3 points, 1 vaut 4 points et le 0 vaut 5 points.
Par exemple, si on aligne le chiffre 2 sur 3 cases, le score sera (3+3+3) x 3 = 27
Autre exemple, si on aligne le chiffre 5 sur 4 cases, le score sera de (-1-1-1-1) x 4 = -16



Mode infini :
Dans un troisième temps, le mode de jeu dit infini, ce mode de jeu ne comporte pas de tours maximum pour jouer, donc infini, les couleurs des chiffres restent les mêmes que le mode classic, mais le calcul du score lui est différent. Pour le calcul, on va venir multiplier le nombre de cases par le chiffre dans la case, par exemple : on aligne le chiffre 5 sur 3 cases, alors on va faire 5 x 3 = 15.
