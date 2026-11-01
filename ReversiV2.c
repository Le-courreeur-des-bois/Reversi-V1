#include <stdio.h>
#define N 8

int main() {
    int plateau[N][N];
    int i, j, d, k;
    int joueur_actuelle = 1; // 1 pour Noir, 2 pour Blanc
    int adversaire = 2;
    int partie_en_cours = 1;
    int lig, col;
    int total_retournes = 0;
    int nx, ny, rx, ry, nb_pions;
    int cases_vides;
    int score1, score2;

    // Les tableaux de direction
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

    printf("=== BIENVENUE SUR LE JEU DU REVERSI ===\n");

    // 2. LA BOUCLE PRINCIPALE DU JEU
    while (partie_en_cours == 1) {

        // A. Affichage du plateau
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
            printf("\nJoueur %d, entrez ligne et colonne (-1 -1 pour passer, -2 -2 pour quitter) : ", joueur_actuelle);
            scanf("%d %d", &lig, &col);

            // 1. Quitter le jeu
            if (lig == -2 && col == -2) {
                partie_en_cours = 0;
                coup_valide = 1; // Permet de sortir proprement de la boucle de saisie
            }
            // 2. Passer son tour
            else if (lig == -1 && col == -1) {
                printf("Le joueur %d passe son tour.\n", joueur_actuelle);
                coup_valide = 1; // Sort de la boucle de saisie

                // Changement de joueur pour le tour passé
                if (joueur_actuelle == 1) {
                    joueur_actuelle = 2;
                    adversaire = 1;
                } else {
                    joueur_actuelle = 1;
                    adversaire = 2;
                }
            }
            // 3. Coordonnées hors du plateau
            else if (lig < 0 || lig >= N || col < 0 || col >= N) {
                printf("Erreur : Coordonnées hors du plateau ! Réessayez.\n");
                // coup_valide reste à 0, la boucle recommence toute seule
            }
            // 4. Case déjà occupée
            else if (plateau[lig][col] != 0) {
                printf("Erreur : Cette case est déjà occupée ! Réessayez.\n");
                // coup_valide reste à 0, la boucle recommence toute seule
            }
            // 5. Test des directions et application du coup
            else {
                total_retournes = 0;
                for (d = 0; d < N; d++) {
                    nx = lig + x[d];
                    ny = col + y[d];
                    nb_pions = 0;

                    // Avancer tant qu'on voit des pions adverses
                    while (nx >= 0 && nx < N && ny >= 0 && ny < N && plateau[nx][ny] == adversaire) {
                        nx = nx + x[d];
                        ny = ny + y[d];
                        nb_pions++;
                    }

                    // Si la pince est fermée, on retourne les pions
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

                // Bilan du coup
                if (total_retournes == 0) {
                    printf("Coup invalide : vous devez retourner au moins un pion adverse ! Réessayez.\n");
                    // coup_valide reste à 0, la boucle redemande les coordonnées
                } else {
                    plateau[lig][col] = joueur_actuelle; // Pose le pion
                    coup_valide = 1; // Le coup est valide, on sort de la boucle de saisie

                    // Changement de joueur pour un coup normal
                    if (joueur_actuelle == 1) {
                        joueur_actuelle = 2;
                        adversaire = 1;
                    } else {
                        joueur_actuelle = 1;
                        adversaire = 2;
                    }
                }
            }
        }

        // C. Vérification si le plateau est plein (uniquement si la partie n'a pas été quittée)
        if (partie_en_cours == 1) {
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
            if (plateau[i][j] == 1) {
                score1++;
            } else if (plateau[i][j] == 2) {
                score2++;
            }
        }
    }

    printf("\n=== FIN DE LA PARTIE ===\n");
    printf("Score Joueur 1 : %d\n", score1);
    printf("Score Joueur 2 : %d\n", score2);
    if (score1 > score2) {
        printf("Le Joueur 1 gagne !\n");
    } else if (score2 > score1) {
        printf("Le Joueur 2 gagne !\n");
    } else {
        printf("Égalité !\n");
    }

    return 0;
}







