#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NBLIG  6 // Nombre maximal de ligne dans la grille
#define NBCOL  7 // Nombre maximal de colonne dans la grille
#define VICTOIRE 4 // Permet de vérifier si un joueur a gagné
#define GAUCHE 'q' // Permet de se déplacer dans la colonne de gauche pour choisir sa colonne
#define DROITE 'd' // Permet de se déplacer dans la colonne de droite pour choisir sa colonne

#define PION_A 'X' // Définit le pion du joueur 1
#define PION_B 'O' // Définit le pion du joueur 2
#define INCONNU ' ' // Caractère vide utilisé dans le main pour savoir s'il y'a un vainqueur
#define VIDE ' ' // Espace vide pour initialiser la grille


const int COLONNE_DEBUT =NBCOL/2; // La colonne de départ est celle du milieu


typedef char Grille[NBLIG][NBCOL]; // Permet de créer la grile


void init(Grille g);// Initialise la grille avec des caractères vides
void afficher(Grille g, char pion, int colonne); // Permet d'afficher la grille de jeu
bool grille_pleine(Grille g);// Renvoie vrai si la grille est pleine, et faux sinon
void jouer(Grille g, char pion, int *ligne, int *colonne); // Procédure qui fais appel à choisir_colonne et trouver_ligne pour jouer au puissance 4
int choisir_colonne(Grille g,char pion, int colonne);// Fonction qui permet de choisir une colonne en appuyant sur 'q' ou 'd'
int trouver_ligne(Grille g,int colonne);// Trouve la bonne ligne pour mettre le pion dans la colonne
bool estVainqueur(Grille g,int ligne, int colonne);// Renvoie vrai si le joueur a aligné 4 pion, et continue la partie sinon
void fin_de_partie(char pion);// Affiche quel joueur a gagné la partie, ou s'il y'a une égalité
    


// Le programme principal utilise les fonctions créées pour jouer au puissance 4 

int main() 
{
    char vainqueur;
    int ligne, colonne;
    Grille grille;

    init(grille);
    vainqueur = INCONNU;
    afficher(grille, PION_A, COLONNE_DEBUT);   
    
    while  ((vainqueur == INCONNU) &&  !(grille_pleine(grille))){
        jouer(grille,PION_A,&ligne, &colonne);
        afficher(grille,PION_B, COLONNE_DEBUT);
        if (estVainqueur(grille,ligne,colonne)){
            vainqueur= PION_A;

        }else if (!grille_pleine(grille))
            {
                jouer(grille,PION_B,&ligne, &colonne);
                afficher(grille, PION_A,COLONNE_DEBUT);
                if(estVainqueur(grille,ligne,colonne)){
                    vainqueur = PION_B;
                }
            }
    }
    fin_de_partie(vainqueur);
    return EXIT_SUCCESS;
} 

// Procédure qui initialise la grille avec des caractères vides
void init(Grille g){
    for (int i =0; i< NBLIG;i++){
        for(int y =0; y <NBCOL; y++){
            g[i][y]= VIDE;
        }
    }
}

//Procédure qui permet d'afficher la grille, avec les numéros de colonne et ligne, et le pion au dessus de la grille
void afficher(Grille g, char pion, int colonne){
    int x, i ;
    system("clear");
    int g2[NBCOL]={1,2,3,4,5,6,7};
    char g3[NBCOL];
    for (i =0; i < NBCOL; i++){
        g3[i] = ' ';
    }
    g3[colonne]=pion;
    printf("   | %d | %d | %d | %d | %d | %d | %d | \n", g2[0],g2[1], g2[2],g2[3], g2[4],g2[5], g2[6]);
    printf("   | %c | %c | %c | %c | %c | %c | %c |", g3[0],g3[1], g3[2],g3[3], g3[4],g3[5], g3[6]);
    int a =1;
    printf("\n--------------------------------");
    for (x =0; x<NBLIG;x++){
            
            printf("\n %d | %c | %c | %c | %c | %c | %c | %c | ",a,g[x][0],g[x][1],g[x][2],g[x][3],g[x][4],g[x][5],g[x][6]);
            a++;
            printf("\n--- --- --- --- --- --- --- ----");
        }
    printf("\n");
}

// Fonction qui regarde si la grille est pleine ou non, et renvoie true si elle l'est

bool grille_pleine(Grille g){
    bool pleine = true;
    int y ;
    
    for (int i =0; i< NBLIG;i++){
        for(y =0; y <NBCOL; y++){
            if (g[i][y]==VIDE){
                pleine = false;
                
            }
        }
    } 

    return pleine;
}

// Procédure qui permet de jouer

void jouer(Grille g, char pion, int *ligne, int *colonne){
    *colonne = choisir_colonne(g, pion, COLONNE_DEBUT);
    *ligne = trouver_ligne(g,*colonne);
    g[*ligne][*colonne]=pion;
    

}

// Fonction qui permet de choisir la colonne où mettre le pion, en se déplaçant soit à gauche soit à droite

int choisir_colonne(Grille g,char pion, int colonne){
    char caractere;
    ;
    do{
        printf("Tapez sur d pour avancer votre pion à droite et q pour avancer à gauche \nPuis appuyez sur la barre 'ESPACE' pour placer le pion \n");
        scanf("%c", &caractere);
        if ((caractere == DROITE)&& (colonne < NBLIG)) {
            colonne++;
        }
        else if ((caractere == GAUCHE)&& (colonne > 0)){
            colonne--;
        
        }
        else {
            colonne = colonne;
        }
        afficher(g, pion, colonne);

    }while(caractere != VIDE);

    if (g[0][colonne] != VIDE){
        printf("Vous ne pouvez plus jouer dans cette colonne ! Rejouez ! \n");
        return choisir_colonne(g,pion,colonne);
    }
    return colonne;

}

// Fonction qui trouve la première ligne vide de la colonne pour pouvoir y jouer le pion

int trouver_ligne(Grille g,int colonne){
    int ligne = -1;
    int i =0;
    
        while((g[i][colonne] !='X' || g[i][colonne] !='O') && (i < NBLIG)){
            if (g[i][colonne]==' '){
                ligne++;
            }
            i++;
        }
    
    return ligne;
}

// Fonction qui vérifie si le joueur a aligné 4 pion ou non

bool estVainqueur(Grille g,int ligne, int colonne){
    bool vainqueur = false;
    int i, j;
    int compteur = 0;
    char joueur=g[ligne][colonne];
    // vérification des lignes
    for (i = 0; i < NBCOL; i++) {
        compteur = 0;
        for (j = 0; j < NBCOL; j++) {
            if (g[i][j] == joueur) {
                compteur++;
            } else {
                compteur = 0;
            }
            if (compteur == VICTOIRE) {
                vainqueur = true;
            }
        }
    }
    // vérification des colonnes
    for (j = 0; j < NBCOL; j++) {
        compteur = 0;
        for (i = 0; i < NBCOL; i++) {
            if (g[i][j] == joueur) {
                compteur++;
            } else {
                compteur = 0;
            }
            if (compteur == VICTOIRE) {
                vainqueur = true;
            }
        }
    }
    // vérification des diagonales
    for (i = 0; i < NBCOL - 3; i++) {
        for (j = 0; j < NBCOL - 3; j++) {
            if (g[i][j] == joueur && g[i + 1][j + 1] == joueur && g[i + 2][j + 2] == joueur && g[i + 3][j + 3] == joueur) {
                vainqueur = true;
            }
        }
    }
    for (i = 0; i < NBCOL - 3; i++) {
        for (j = 3; j < NBCOL; j++) {
            if (g[i][j] == joueur && g[i + 1][j - 1] == joueur && g[i + 2][j - 2] == joueur && g[i + 3][j - 3] == joueur) {
                vainqueur = true;
            }
        }
    }
    return vainqueur;
}

// Permet d'afficher le joueur qui a gagné ou la fin de partie s'il y'a égalité

void fin_de_partie(char pion){
    if (pion =='X'){
        printf("Joueur 1 a gagné ! \n");
    }else if ( pion =='O'){
        printf("Joueur 2 a gagné !\n");
    }else{
        printf("Toutes les cases sont remplies !\n Fin de partie ! \n");
    }
}