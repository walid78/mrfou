#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

//Nombre de couleurs
int n;
//Dimension
int d;
//Nombre de positions
int nb_pos;

//==============================================================================
void usage(){
  printf("USAGE : ./sudoku fichier_grille\n");
  exit(EXIT_FAILURE);
}

//==============================================================================
uint16_t* val_copie(uint16_t* val){
  uint16_t* copie = (uint16_t*)malloc(nb_pos*sizeof(uint16_t));

  for(int i=0 ; i<nb_pos ; ++i){
    copie[i] = val[i];
  }

  return copie;
}

//==============================================================================
bool* coul_presentes(uint16_t x){
  bool* coul = (bool*)malloc(n*sizeof(bool));
  for(int i=0 ; i<n ; ++i)
    coul[i] = false;
  
  for(int i=0 ; i<n ; ++i){
    if(x>>i & 1){
      coul[i] = true;
    }
  }

  return coul;
}

//==============================================================================
void affiche_coul_presentes(uint16_t x){
  bool* coul = coul_presentes(x);
  for(int i=0 ; i<n ; ++i)
    if(coul[i])
      printf("%i ", i);
}

//==============================================================================
bool est_vide(uint16_t x){
  return ((x & ((1<<n)-1)) == 0);
}

//==============================================================================
bool est_singl(uint16_t x){
  
  return !est_vide(x) && (((x & (x-1)) & ((1<<n)-1)) == 0);
}

/*Affiche le tableau passé entre paramètre*/
//==============================================================================
void affiche(uint16_t *grille) {
  bool* coul;
  for(int i=0 ; i<n ; ++i){
    for(int j=0 ; j<n ; ++j){
      printf("{");
      coul = coul_presentes(grille[n*i+j]);
      if(coul != NULL){
	for(int k=0 ; k<n ; ++k){
	  if(coul[k])
	    printf("%i", k);
	}
      }else
	printf("bottom");
      printf("}");
/*       printf(" "); */
    }
    free(coul);
    printf("\n");
  }
}

/*retourne le nombre de lignes du fichier passé entre paramètre*/
//==============================================================================
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
//==============================================================================
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
	tab[position]=1<<(caractereActuel-'0');
	printf("%c ", caractereActuel);
	position++;
      }

      else if(caractereActuel=='_'){
	// C'est un underscore
	printf("%c ", caractereActuel);
	tab[position]=(1<<n)-1;
	position++;
      }

      else if(caractereActuel >='A' && caractereActuel <= 'F'){
	// C'est une lettre correspondant a un nombre hexadecimal
	printf("%c ", caractereActuel);
	tab[position]=1<<(caractereActuel -'A'+10);
	position++;
      }


    } while (caractereActuel != EOF);

  printf(" Parsage fini position = %i \n",position);

  fseek(fp, 0, SEEK_SET); 
  return EXIT_SUCCESS;

}

//==============================================================================
uint16_t contraintes(uint16_t* val0, int p){
  uint16_t result = 0;
  int q,r;

  result |= val0[p];
  
  /* Même colonne */
  for(int q=p%n ; q<nb_pos ; q+=n){
    if(q != p){
      if(est_singl(val0[q])){
	result &= (~val0[q]);
      }
    }
  }

  /* Même ligne */
  q = (p/n)*n;
  for(int i=0 ; i<n ; ++i, ++q){
    if(q != p){
      if(est_singl(val0[q])){
	result &= (~val0[q]);
      }
    }
  }
  /* Même bloc */
  //calcul du coin supérieur gauche du bloc
  r = (((p/n)/d)*d)*n + ((p%n) - ((p%n)%d));

  for(int i=0 ; i<d ; ++i){
    for(int j=0 ; j<d ; ++j){
      q = (r+j) + (n*i);
      if(q != p){
	if(est_singl(val0[q])){
	  result &= (~val0[q]);
	}
      }
    }
  }
  
  return result;
}

//==============================================================================
uint16_t* round_robin(uint16_t* val0){
  uint16_t* X = (uint16_t*)malloc(nb_pos*sizeof(uint16_t));
  for(int i=0 ; i<nb_pos ; ++i)
    X[i] = 0;

  bool change;
  uint16_t new;

  do{
    change = false;
    for(int i=0 ; i<nb_pos ; ++i){
      new = contraintes(val0, i);
      //Si new n'est pas inclus dans Xp      
      if((X[i]&new) != new){
	change = true;
	X[i] |= new;
      }
    }
  }while(change);
  
  return X;
}

//==============================================================================
void sudoku(uint16_t* val0){
  uint16_t* val = round_robin(val0);
  int p;

  for(p=0 ; p<nb_pos ; ++p){
    if(est_singl(val[p]) || est_vide(val[p])){
      if(est_vide(val[p])){
	free(val);
	return;
      }
    }else{
      break;
    }
  }
  
  if(p>=nb_pos){
    printf("GRILLE SOLUTION\n");
    affiche(val);
    exit(EXIT_SUCCESS);
  }else{
    bool* coul = coul_presentes(val[p]);
    uint16_t* val0_prim = val_copie(val);
    for(int i=0 ; i<n ; ++i){
      if(coul[i]){
	val0_prim[p] = 1<<i;
	sudoku(val0_prim);
      }
    }
    free(val0_prim);
    free(coul);
  }
  free(val);
}

//==============================================================================
int main(int argc, char *argv[]) {

  if(argc != 2)
    usage();
  

  /* Ouverture du fichier */
  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");

  n = nbLignes(fp);
  d = sqrt(n);
  nb_pos = n*n;
  printf("Taille du tableau : %ix%i\n", n, n);
  uint16_t* valI = (uint16_t*)malloc(nb_pos*sizeof(uint16_t));

  parserGrille(fp, valI);
  fclose(fp);

  printf("GRILLE ENTREE\n");
  affiche(valI);
  sudoku(valI);

  free(valI);

  return EXIT_SUCCESS;
}
