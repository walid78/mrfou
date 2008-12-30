

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void affiche(int *tableau, int tailleTableau) {
    int i;

    for (i = 0; i < tailleTableau; i++) {
        printf("%i\n", tableau[i]);
    }
}

void remplir(int *tableau, int tailleTableau) {
    long i;

    for (i = 0; i < tailleTableau; i++) {
        tableau[i] = -1;
    }
}

int nbLignes(FILE *fp) {
    int n = 0, c;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            n++;
        }
    }
    return n;
}

int parserGrille(char *filename, int *tab) {
    int position = 0;
    
    FILE *fp;
    //char data[10];
    int i, j;
    int caractereActuel = 0;

    fp = fopen(filename, "r");

    //printf("Descripteur de fichier ouvert\n");

    if (fp == NULL) {
        printf("Erreur fichier en entrée!!!\n");
        return EXIT_FAILURE;
    }

    //printf("fichier correct\n");

    do // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    {
        caractereActuel = fgetc(fp); // On lit le caractère
        //printf("%c", caractereActuel);

        if (isdigit(caractereActuel)){

            tab[position]=caractereActuel;
            printf("%c ", caractereActuel);
            position++;
        }

        if(caractereActuel=='_'){
            printf("%c ", caractereActuel);
            tab[position]==-1;
            position++;
        }


    } while (caractereActuel != EOF);

    printf("parsage fini position = %i \n",position);

    fclose(fp);
    return EXIT_SUCCESS;

}

int main(int argc, char *argv[]) {
    FILE *fp = fopen("/home/eewans/grids/4x4-1.txt", "r");
    int lignes = nbLignes(fp);
    int taille = lignes * lignes - 1;

    fclose(fp);
    printf("Taille du tableau %i\n", taille);
    int tab [taille];


    parserGrille("/home/eewans/grids/4x4-1.txt", tab);
    //remplir(tab, taille);
    affiche(tab,taille);

    //int tab[15];
    //remplir(tab,15);
    //affiche(tab,15);
}








/*
 * File:   main.c
 * Author: eewans
 *
 * Created on 19 décembre 2008, 22:22
 */

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remplirZero(int **matrice, int taille){
    int i,j;

    for(int i=0;i<taille;i++)
        for(int j=0;j<taille;j++){
            matrice[i][j]=0;
        }
}


void AfficheMatrice(int **Mat, int nbSommets) {

    int i, j;

    for (i = 0; i < nbSommets; i++) {
        for (j = 0; j < nbSommets; j++)
            printf("%d ", Mat[i][j]);
        printf("\n");
    }
}

int main(int argc, char ** argv) {
    int tab[10][10];
    remplirZero(&tab,10);
 */
//T = afficher_fichier(T, 4);
/*


}
 */


