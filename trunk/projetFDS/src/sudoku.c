/*
 * File:   main.c
 * Author: eewans fkuntz
 *
 * Created on 19 décembre 2008, 22:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef unsigned short uint16_t;

/*Affiche le tableau passé entre paramètre*/
void affiche(int *tableau, int tailleTableau) {
  int i;

  for (i = 0; i <= tailleTableau; i++) {
    printf("%i\n", tableau[i]);
  }
}

/*
  void remplir(int *tableau, int tailleTableau) {
  long i;

  for (i = 0; i < tailleTableau; i++) {
  tableau[i] = -1;
  }
  }
*/

/*retourne le nombre de lignes du fichier passé entre paramètre*/
int nbLignes(FILE *fp) {
  int n = 0, c;

  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      n++;
    }
  }
  fseek(fp, 0, SEEK_SET); 
  return n;
}

/*Parse la grille du fichier passé entre paramètre dans le tableau passé entre paramètre*/
int parserGrille(FILE *fp, int *tab) {
  int position = 0;
  int caractereActuel;

  if (fp == NULL) {
    printf("Erreur fichier en entrée!!!\n");
    return EXIT_FAILURE;
  }

  do // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    {
      caractereActuel = fgetc(fp); // On lit le caractère

      if ( (caractereActuel-'0') >=0 && (caractereActuel-'0') <=9 ){
	// C'est un chiffre
	tab[position]=caractereActuel-'0';
	printf("%c ", caractereActuel);
	position++;
      }

      else if(caractereActuel=='_'){
	// C'est un underscore
	printf("%c ", caractereActuel);
	tab[position]=-1;
	position++;
      }

      else if(caractereActuel >='A' && caractereActuel <= 'F'){
	// C'est une lettre correspondant a un nombre hexadecimal
	printf("%c ", caractereActuel);
	tab[position]=caractereActuel -'A'+10;
	position++;
      }


    } while (caractereActuel != EOF);

  printf("parsage fini position = %i \n",position);

  fseek(fp, 0, SEEK_SET); 
  return EXIT_SUCCESS;

}

int main(int argc, char *argv[]) {

  /* Ouverture du fichier */
  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");

  int n = nbLignes(fp);
  int d = sqrt(n);

  printf("Taille du tableau : %ix%i\n", n, n);
  //uint16_t grille[n*n];
  int tab[n*n];

  parserGrille(fp, tab);
  //remplir(tab, taille);
  //affiche(tab,taille);

  //int tab[15];
  //remplir(tab,15);
  //affiche(tab,15);

  
  fclose(fp);

  return EXIT_SUCCESS;
}
