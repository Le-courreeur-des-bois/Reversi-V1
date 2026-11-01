
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8

int main() {
    int plateau[N][N];
    int i, j, d, k;
    int joueur_actuelle = 1; // 1 = Noir, 2 = Blanc
    int adversaire = 2;
    int partie_en_cours = 1;
    int lig, col;
    int total_retournes = 0;
    int nx, ny, rx, ry, nb_pions;
    int cases_vides;
    int score1, score2;
    int mode_jeu = 1; // 1: Humain vs Humain, 2: Humain vs Robot Aléatoire, 3: Humain vs Robot Glouton

    // Initialisation du générateur aléatoire pour le robot niveau 1
    srand(time(NULL));

    // Les tableaux de direction (notre boussole)
    int x[N] = {-1, -1, -1,  0,  0,  1,  1,  1};
    int y[N] = {-1,  0,  1, -1,  1, -1,  0,  1};

    // 1. INITIALISATION DU PLATEAU
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            plateau[i][j] = 0;
        }
    }
    // Pions de départ au centre
    plateau[3][3] = 2;
    plateau[4][4] = 2;
    plateau[3][4] = 1;
    plateau[4][3] = 1;

    // MENU DE SÉLECTION DU MODE DE JEU
    printf("=== BIENVENUE SUR LE JEU DU REVERSI ===\n");
    printf("Choisissez le mode de jeu :\n");
    printf("1. Humain vs Humain\n");
    printf("2. Humain vs Robot Aléatoire (Niveau 1)\n");
    printf("3. Humain vs Robot Glouton (Niveau 2)\n");
    printf("Votre choix (1, 2 ou 3) : ");

    if (scanf("%d", &mode_jeu) != 1) {
        while (getchar() != '\n');
        mode_jeu = 1;
    }

    // 2. LA BOUCLE PRINCIPALE DU JEU (S'arrête naturellement si partie_en_cours passe à 0)
    while (partie_en_cours == 1) {

        // A. Affichage du plateau avec fermeture propre de la grille
        printf("\n    ");
        for (j = 0; j < N; j++) printf(" %d", j);
        printf("\n  +-----------------+\n");
        for (i = 0; i < N; i++) {
            printf("%d |", i);
            for (j = 0; j < N; j++) {
                if (plateau[i][j] == 0) printf(" .");
                else printf(" %d", plateau[i][j]);
            }
            printf(" |\n");
        }
        printf("  +-----------------+\n");

        // B. Boucle de saisie sécurisée
        int coup_valide = 0;

        while (coup_valide == 0 && partie_en_cours == 1) {

            // Si c'est le tour du Joueur 2 et qu'on est en mode Robot
            if (joueur_actuelle == 2 && (mode_jeu == 2 || mode_jeu == 3)) {

                lig = -1;
                col = -1;

                // ==========================================
                // ROBOT NIVEAU 1 : ALÉATOIRE (Sans break)
                // ==========================================
                if (mode_jeu == 2) {
                    printf("\nTour du Robot Aléatoire (Réflexion...)...\n");

                    int coups_possibles_lig[64];
                    int coups_possibles_col[64];
                    int nb_coups = 0;

                    for (i = 0; i < N; i++) {
                        for (j = 0; j < N; j++) {
                            if (plateau[i][j] == 0) {
                                int test_valide = 0;
                                for (d = 0; d < N; d++) {
                                    nx = i + x[d];
                                    ny = j + y[d];
                                    int nb = 0;
                                    while (nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == adversaire) {
                                        nx = nx + x[d];
                                        ny = ny + y[d];
                                        nb++;
                                    }
                                    if (nb > 0 && nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == joueur_actuelle) {
                                        test_valide = 1;
                                    }
                                }
                                if (test_valide == 1) {
                                    coups_possibles_lig[nb_coups] = i;
                                    coups_possibles_col[nb_coups] = j;
                                    nb_coups++;
                                }
                            }
                        }
                    }

                    if (nb_coups > 0) {
                        int choix_hasard = rand() % nb_coups;
                        lig = coups_possibles_lig[choix_hasard];
                        col = coups_possibles_col[choix_hasard];
                    }
                }

                // ==========================================
                // ROBOT NIVEAU 2 : GLOUTON
                // ==========================================
                else if (mode_jeu == 3) {
                    printf("\nTour du Robot Glouton (Réflexion...)...\n");

                    int meilleur_score = -1;

                    for (i = 0; i < N; i++) {
                        for (j = 0; j < N; j++) {
                            if (plateau[i][j] == 0) {
                                int pions_retournes_ici = 0;
                                for (d = 0; d < N; d++) {
                                    nx = i + x[d];
                                    ny = j + y[d];
                                    int nb = 0;
                                    while (nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == adversaire) {
                                        nx = nx + x[d];
                                        ny = ny + y[d];
                                        nb++;
                                    }
                                    if (nb > 0 && nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == joueur_actuelle) {
                                        pions_retournes_ici += nb;
                                    }
                                }
                                if (pions_retournes_ici > meilleur_score) {
                                    meilleur_score = pions_retournes_ici;
                                    lig = i;
                                    col = j;
                                }
                            }
                        }
                    }
                }

                // Application du coup choisi par le robot
                if (lig == -1 || col == -1) {
                    printf("Le Robot n'a aucun coup valide et passe son tour.\n");
                    coup_valide = 1;
                } else {
                    for (d = 0; d < N; d++) {
                        nx = lig + x[d];
                        ny = col + y[d];
                        nb_pions = 0;
                        while (nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == adversaire) {
                            nx = nx + x[d];
                            ny = ny + y[d];
                            nb_pions++;
                        }
                        if (nb_pions > 0 && nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == joueur_actuelle) {
                            rx = lig + x[d];
                            ry = col + y[d];
                            for (k = 0; k < nb_pions; k++) {
                                plateau[rx][ry] = joueur_actuelle;
                                rx = rx + x[d];
                                ry = ry + y[d];
                            }
                        }
                    }
                    plateau[lig][col] = joueur_actuelle;
                    printf("Le Robot a joue en : lig %d, col %d\n", lig, col);
                    coup_valide = 1;
                }

            } else {
                // Tour classique d'un joueur humain
                printf("\nJoueur %d, entrez ligne et colonne (-1 -1 pour passer, -2 -2 pour quitter) : ", joueur_actuelle);

                if (scanf("%d %d", &lig, &col) != 2) {
                    printf("Erreur : Veuillez entrer uniquement des nombres valides !\n");
                    while (getchar() != '\n');
                    lig = -99;
                    col = -99;
                }

                if (lig == -2 && col == -2) {
                    partie_en_cours = 0;
                    coup_valide = 1;
                }
                else if (lig == -1 && col == -1) {
                    printf("Le joueur %d passe son tour.\n", joueur_actuelle);
                    coup_valide = 1;
                }
                else if (lig < 0 || lig >= N || col < 0 || col >= N) {
                    printf("Erreur : Coordonnées hors du plateau ! Réessayez.\n");
                }
                else if (plateau[lig][col] != 0) {
                    printf("Erreur : Cette case est déjà occupée ! Réessayez.\n");
                }
                else {
                    total_retournes = 0;
                    for (d = 0; d < N; d++) {
                        nx = lig + x[d];
                        ny = col + y[d];
                        nb_pions = 0;

                        while (nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == adversaire) {
                            nx = nx + x[d];
                            ny = ny + y[d];
                            nb_pions++;
                        }

                        if (nb_pions > 0 && nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == joueur_actuelle) {
                            total_retournes = total_retournes + nb_pions;
                            rx = lig + x[d];
                            ry = col + y[d];
                            for (k = 0; k < nb_pions; k++) {
                                plateau[rx][ry] = joueur_actuelle;
                                rx = rx + x[d];
                                ry = ry + y[d];
                            }
                        }
                    }

                    if (total_retournes == 0) {
                        printf("Coup invalide : vous devez retourner au moins un pion adverse ! Réessayez.\n");
                    } else {
                        plateau[lig][col] = joueur_actuelle;
                        coup_valide = 1;
                    }
                }
            }
        }

        // C. Changement de joueur (exécuté uniquement si la partie continue)
        if (partie_en_cours == 1) {
            if (joueur_actuelle == 1) {
                joueur_actuelle = 2;
                adversaire = 1;
            } else {
                joueur_actuelle = 1;
                adversaire = 2;
            }

            // D. Vérification si le plateau est plein
            cases_vides = 0;
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                    if (plateau[i][j] == 0) {
                        cases_vides++;
                    }
                }
            }
            if (cases_vides == 0) {
                partie_en_cours = 0;
            }
        }
    }

    // 3. FIN DE PARTIE ET CALCUL DES SCORES
    score1 = 0;
    score2 = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (plateau[i][j] == 1) score1++;
            else if (plateau[i][j] == 2) score2++;
        }
    }

    printf("\n=== FIN DE LA PARTIE ===\n");
    printf("Score Joueur 1 : %d\n", score1);
    printf("Score Joueur 2 : %d\n", score2);
    if (score1 > score2) printf("Le Joueur 1 gagne !\n");
    else if (score2 > score1) {
        if (mode_jeu >= 2) printf("Le Robot gagne !\n");
        else printf("Le Joueur 2 gagne !\n");
    } else {
        printf("Égalité !\n");
    }

    return 0;
}






