#include<stdio.h>
# define N 8

int main(){
    int plateau[N][N];
    int i, j, d, k;
    int joueur_actuelle=1;
    int adversaire=2;
    int partie_en_cours=1;
    int lig, col;
    int total_retournes=0;
    int nx, ny, rx, ry, nb_pions;
    int cases_vides;
    int score1, score2;
    int x[N]={-1, -1, -1, 0, 0, 1, 1, 1}; /*vecteur de deplacement explorer les 8 directions autour d'une case*/
    int y[N]={-1, 0, 1, -1, 1, -1, 0, 1};/*(-1,0)=Haut, (1,0)=Bas, (0,-1)=Gauche, (0,1)=droite, et les 4 diagonales*/

    for (i=0; i<N; i++){
        for(j=0; j<N; j++){
            plateau[i][j]=0;
        }
    }
    plateau[3][3]=2; /*Initialisation des pièces de depart*/
    plateau[4][4]=2;
    plateau [3][4]=1;
    plateau [4][3]=1;
    printf("Bienvunu sur le Jeu du Reversi !\n");
    printf("Bonne partie !\n");
    /* Permet d'afficher la grille(.=vide, 1 ou 2=pionsjoueurs*/
    while (partie_en_cours==1){
        printf("\n   ");
        for (j=0; j<N; j++){
            printf(" %d", j);}
        printf("\n  +-----------------+\n");
        for (i=0; i<N; i++){
            printf("%d |", i);
            for(j=0; j<N; j++){
                if (plateau[i][j]==0){
                    printf(" .");
                } else{
                    printf(" %d", plateau[i][j]);

                }
            }
            printf(" |\n");
        }
        printf("  +-----------------+\n");
        printf("Le joueur %d : Entrer ligne et colonne (ou -1 -1 pour passer, -2 -2 pour arreter) :", joueur_actuelle);
        scanf("%d %d", &lig, &col);
        if (lig==-2 && col==-2){
            partie_en_cours=0;}
        else if (lig==-1 && col==-1){
            if (joueur_actuelle==1){
                joueur_actuelle=2;
                adversaire=1;}
            else{
                joueur_actuelle=1;
                adversaire=2;
            }
        } else if (lig<0 || lig>=N || col<0 || col>=N){
            printf("Coordonnée hors du plateau !\n");
        } else if (plateau[lig][col]!=0){
            printf("Cette coordonné est déjà occupé !\n");
        } else{ /*Verifions le retournement dans les 8 directions*/
            total_retournes=0;
            for(d=0; d<N; d++){
                nx= lig +x[d];
                ny= col +y[d];
                nb_pions=0;
            /* Permet d'avancer daans la direction d du moment qu'oncroise des pions adverse*/
            while(nx >=0 && nx<N && ny>=0 && ny<N && plateau[nx][ny]==adversaire){
                nx= nx+x[d]; /*On avance tant qu'on reste sur la grille et et qu'on voit des pion adversaire*/
                ny=ny+y[d];
                nb_pions++;
            }
            /*Si la seqence des pions du joueur est separé par un ou plusieurs pions de l'adversaire, alors le coup est valide*/
            if (nb_pions >0 && nx >=0 && nx<N && ny>=0 && ny<N && plateau[nx][ny] == joueur_actuelle){
                total_retournes=total_retournes+nb_pions;
                rx=lig+x[d];
                ry=col+y[d];
                /*Retournement des pions encandrés*/
                for(k=0; k<nb_pions; k++){
                    plateau[rx][ry]=joueur_actuelle;
                    rx=rx+x[d];
                    ry=ry+y[d];
                }
             }

            }
            if (total_retournes ==0){
                printf("Coupe invalide, vous devez retourner au moin un poin adverse");}
            else{
                plateau[lig][col]=joueur_actuelle;
                if (joueur_actuelle==1){
                    joueur_actuelle=2;
                    adversaire=1;}
                else{
                    joueur_actuelle=1;
                    adversaire=2;}
            }
            /*Verirification si le plateau est plein*/
            cases_vides=0;
            for (i=0; i<N; i++){
                for (j=0; j<N; j++){
                    if (plateau[i][j]==0){
                        cases_vides++;
                    }
                }
            }
            if (cases_vides ==0){
                partie_en_cours = 0;
              }
             }
            } /*Fin de la boucle while, soit fin de la partie*/
            score1=0; /*Permet de cacluler et afficher les scores des joueurs*/
            score2=0;
            for (i=0; i<N; i++){
                for (j=0; j<N; j++){
                    if (plateau[i][j]==1){
                        score1++;
                    } else if (plateau[i][j]==2){
                        score2++;
                    }
                }
            }
            printf("\n Fin de la partie \n");
            printf("Score Joueur1 : %d\n", score1);
            printf("Score Joueur2 : %d\n", score2);
            if (score1>score2){
                printf("Le joueur 1 gagne !\n");
            } else if (score2 > score1){
                printf("Le joueur 2 gagne !\n");
            }  else {
                printf("Egalite !\n");
            }
            return 0;


}







