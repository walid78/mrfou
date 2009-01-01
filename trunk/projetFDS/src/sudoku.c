#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>

//Nombre de couleurs
int n;

//Dimension
int d;

int* test(uint16_t x){
  int nb_coul = 0;
  
  if(x==(uint16_t)-1)
    return NULL;

  //Tableau des couleurs initialisé à -1
  int *coul = (int*)malloc(n*sizeof(int));
  for(int i=0 ; i<n ; ++i)
    coul[i] = -1;

  for(int i=0 ; i<n ; ++i){
    if(x>>i & 1){
      coul[nb_coul] = i;
    }
    nb_coul++;
  }

  return coul;
}



/*Affiche le tableau passé entre paramètre*/
void affiche(uint16_t *grille, int n) {
  int *coul;
  for(int i=0 ; i<n ; ++i){
    for(int j=0 ; j<n ; ++j) {
      printf("{");
      coul = test(grille[n*i+j]);
      if(coul != NULL){
	for(int k=0 ; k<n ; ++k){
	  if(coul[k] != -1)
	    printf("%i", coul[k]);
	}
      }
      printf("}");
    }
    printf("\n");
  }
  free(coul);
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
int parserGrille(FILE *fp, uint16_t *tab) {
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
	tab[position]=pow(2,(caractereActuel-'0'));
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
	tab[position]=pow(2,(caractereActuel -'A'+10));
	position++;
      }


    } while (caractereActuel != EOF);

  printf(" Parsage fini position = %i \n",position);

  fseek(fp, 0, SEEK_SET); 
  return EXIT_SUCCESS;

}

int main(int argc, char *argv[]) {

  /* Ouverture du fichier */
  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");

  n = nbLignes(fp);
  d = sqrt(n);

  printf("Taille du tableau : %ix%i\n", n, n);
  uint16_t grille[n*n];
/*   uint16_t t=4; */
  /* int tab[n*n]; */

  parserGrille(fp, grille); 
   affiche(grille, n);

  for(int i=0 ; i<n*n ; ++i)
    printf("%u ",grille[i]);
  printf("\n");
  
 /*  uint32_t tmp = -1; */

/*   int* tmp2 = test(tmp); */

/*   if(tmp2==NULL) */
/*     printf("NULL"); */
/*   else */
/*     for(int i=0 ; i<n ; ++i) */
/*       printf("%i ",tmp2[i]); */
  
/*   printf("\n"); */

/*   free(tmp2); */



/*   remplir(tab, taille); */
/*   affiche(tab,taille); */

/*   int tab[15]; */
/*   remplir(tab,15); */
/*   affiche(tab,15); */

  
  fclose(fp);

  return EXIT_SUCCESS;
}
