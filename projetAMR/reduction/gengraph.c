/* gcc gengraph.c -o gengraph ; strip gengraph */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG(s) (strcmp(argv[i],s)==0)
#define LMAX 8    /* nb d'arêtes max affichées par ligne */
#define DIMAX 256 /* nb maximum de paramètres d'un graphe */

int N;           /* N=nb de sommets du graphes avant suppression */
int *V;          /* étiquette des sommets, en principe V[i]=i */
int PARAM[DIMAX];/* liste des paramètres du graphe */
double DELE=0.0; /* proba de supprimer une arêtes */
double DELV=0.0; /* proba de supprimer un sommet */
int PERMUTE=0;   /* vrai ssi -permute */
int NOT=0;       /* vrai ssi -not */
int LIGNE=0;     /* nb d'arêtes par ligne sur la sortie */
int ARGC;        /* variable globale pour argc */
char **ARGV;     /* variable globale pour argv */


void Erreur(int error){
  char *s;
  switch(error){
    case 1: s="Erreur : nombre d'argument insuffisant."; break;
    case 2: s="Erreur : argument inconnu."; break;
    case 3: s="Erreur : espace mémoire insuffisant."; break;
    case 4: s="Erreur : nombre trop grand de paramètres."; break;
    default: s="Erreur : code d'erreur inconnue.";
  }
  printf("%s\n",s);
  exit(0);
}


void *TabAllocInt(int n){
  /*
    Créer un tableau de n tableaux d'entiers
  */
  int *p;
  p=malloc(n*sizeof(int*));
  if(p==NULL) Erreur(3);
  return p;
}


int *AllocInt(int n){
  /*
    Créer un tableau de n entiers
  */
  int *p;
  p=malloc(n*sizeof(int));
  if(p==NULL) Erreur(3);
  return p;
}


/***********************************

           GRAPHES DE BASE
               (début)

***********************************/

/*
  Les fonctions d'adjacences adj(i,j) doivent avoir les fonctionalités
  suivantes :

  1. adj(-1,j): inialise l'adjacence (appelée avant)
  2. adj(i,-1): finalise l'adjacence (appelée après)
  3. adj(i,j) pour i,j>=0, retourne 1 ssi i est adjacent à j

 */

int prime(int i,int j){
  if(j<0) return 0;
  if(i<0){ N=PARAM[0]; return N; }
  return (i>1)? ((j%i)==0) : 0;
}

int ring(int i,int j){
  int k,x=0;
  if(j<0) return 0;
  if(i<0){ N=PARAM[0]; return N; }

  for(k=0;k<PARAM[1];k++)
    if((j==((i+PARAM[2+k])%N))||(i==((j+PARAM[2+k])%N))) x=1;
  return x;
}

int WRAP[DIMAX]; /* WRAP[k]=1 ssi la dimension k est "torique" */

int grid(int i,int j){
  int x,y,k,z,d,p,h,b;

  if(j<0) return 0;
  if(i<0){
    N=1;
    for(k=0;k<PARAM[0];k++){
      p=PARAM[k+1];
      WRAP[k]=(p<0);
      p=abs(p);
      PARAM[k+1]=p;
      N *= p;
    }
    return N;
    }

  d=PARAM[0];
  z=h=k=b=0;

  while((k<d)&&(b<2)&&(h<2)){
    p=PARAM[k+1];
    x=i%p;
    y=j%p;
    h=abs(x-y);
    if(h==0) z++;
    if((h>1)&&(WRAP[k])&&(((x==0)&&(y==p-1))||((y==0)&&(x==p-1)))) h=1;
    if(h==1) b++;
    i /= p;
    j /= p;
    k++;
  }

  return (b==1)&&(z==(d-1));
}

int *TREE;
/* 
   Tableau global pour les arbres

   Ex: arbre avec N=5 sommets, soit n=4 arêtes
   B=[0,1,2,1] ce qui donne le mot de Dick "01011010"
   On décale le mot sur un minimum (r=1 dans B), d'où le
   mot "10110100":

   Mot     3   4        Arbre   0
          / \ / \              / \
     1   2   2   2            1   2
    / \ /         \              / \
   0   0           0            3   4

   TREE=[0,1,0,2,3,2,4,2,0]: c'est la liste des sommets
   rencontrés sur une marche le long du mot.
   Adjacence: i-j ssi on trouve ...i,j... dans le tableau TREE.
*/


int tree(int i,int j){
  /*
    Utilise le fait que i<j
  */
  int n,r,k,s,m,t,h;
  int *B,*H; /* tableaux auxiliaires */

  if(j<0){ free(TREE); return 0;}

  if(i<0){
    N=PARAM[0];/* attention, il faut au moins 2 sommets (= 1 arête) */
    if(N<2) return N;

    TREE=AllocInt(2*N-1);
    B=AllocInt(N-1);
    H=AllocInt(N+1); /* hauteurs possibles: 0...N */
    n=N-1;

    /* remplit B de valeurs dont la somme fait n */

    for(k=0;k<n;k++) B[k]=0;
    for(k=0;k<n;k++) B[rand()%n]++;

    /* cherche la racine r, et donc la hauteur minimum */

    r=-1;
    s=h=0;
    for(k=0;k<n;k++){
      s += B[k]-1;
      if(s<h) { h=s; r=k; }
    }
    r=(r+1)%n;

    /*
      Remplissage de TREE:
      On parcours le mot à partir de la racine r.
      H[h]=dernier sommet rencontré de hauteur h
      h=hauteur du dernier sommet de H
      s=numéro du prochain sommet
      t=index libre du tableau TREE
    */
    TREE[0]=H[0]=h=0; /* on traite le sommet 0 */
    s=t=1;

    for(k=0;k<n;k++){
      m=B[(k+r)%n];
      for(j=0;j<m;j++){
	TREE[t++]=s;
	H[++h]=s++;
      }
      TREE[t++]=H[--h];
    }

    free(B); /* ne garde que le tableau TREE */
    free(H);

    return N;
  }

  /*
    Test d'adjacence i-j ?
  */
  n=2*N-2;
  k=r=0; /* r=résultat=0 ou 1 */
  while((k<n)&&(r==0)){
    if((TREE[k]==i)&&(TREE[k+1]==j)) r=1;
    k++;
  }

  return r;
}


int **REP; /* associe à chaque sommet une représentation sous forme de
	      tableau d'entiers. Sert pour les graphes d'intersections */

void FreeREP(int n,int t){
  /*
    Libère le tableau REP de taille t
  */
  int k;  
  for(k=0;k<n;k++) free(REP[k]);
  free(REP);
}


void AllocREP(int n,int t){
  /*
    Alloue un tableau de n tableaux d'entiers chacun de longueur t
  */
  int k;  
    REP=TabAllocInt(n);
    for(k=0;k<n;k++) REP[k]=AllocInt(t);
}


int permutation(int i,int j){
  int k,x,m;

  if(j<0){ FreeREP(N,1); return 0; }
  if(i<0){
    N=PARAM[0];
    AllocREP(N,1);

    /* génère dans une permutation aléatoire de [0,N[ */
    for(k=0;k<N;k++){
      m=k+(rand()%(N-k));
      x=REP[m][0]; REP[m][0]=REP[k][0]; REP[k][0]=x;
    }

    return N;
  }

  return ((i-REP[i][0])*(j-REP[j][0])<0);
}


int interval(int i,int j){
  int k,x,m;

  if(j<0){ FreeREP(N,2); return 0; }
  if(i<0){
    N=PARAM[0];
    m=2*N;

    /* génère un intervalle REP[k] pour k, [a,b] dans [0,2N[ avec a<=b */
    AllocREP(N,2);
    for(k=0;k<N;k++){
      x=rand()%m;
      REP[k][0]=x;
      REP[k][1]=x+rand()%(m-x);
    }
    return N;
  }

  return ( ((REP[i][0]<=REP[j][0])&&(REP[j][1]<=REP[i][1])) || ((REP[j][0]<=REP[i][0])&&(REP[i][1]<=REP[j][1])) );
}


int kneser(int i,int j){
  int *B,n,k,r,v,x,y;

  if(j<0) { FreeREP(N,PARAM[1]); return 0; }
  if(i<0){
    n=PARAM[0];
    k=PARAM[1];
    r=PARAM[2];

    /*
      Calcule l'entier N={n choose k}.  Cela est nécessaire pour
      allouer le tableau REP. Et malheureusement, on ne peut pas le
      faire à la volée au moment où l'on génère les ensembles
      représentant les sommets, à part faire des realloc() mais sera
      au final bien plus lent que de calculer N.

      L'algorithme utilisé ici est en O(k). Il n'utilise que des
      multiplications et divisions entières sur des entiers en O(N).
      L'algorithme issu du Triangle de Pascal est lui en O(nk),
      utilise un espace (tableaux d'entiers en N) en O(k), mais
      n'utilise que des additions sur des entiers en O(N).

      Principe: N = n x (n-1) x ... x (n-k+1) / k x (k-1) x ... x 1

      On réecrit en (((n/1) x (n-1)) / (k-1)) x (n-2)) / (k-2) ...
      c'est-à-dire en multipliant le plus grand numérateur et en
      divisant la le plus petit numérateur. Chaque terme est ainsi un
      certain binomial, et donc un entier.
    */

    N=x=n;
    for(y=2;y<=k;y++){
      x--;
      N=(N*x)/y;
    }

    AllocREP(N,k); /* on connaît N */

    /*
      Calcule tous les sous-ensembles à k éléments. L'idée est de
      maintenir une sorte de compteur B qui représente le
      sous-ensemble courant et qui va passer par tous les
      sous-ensembles possibles à k éléments. Au départ on part du plus
      "petit" ensemble, B=[0 1 2 ... k-1], les éléments étant rangés
      dans l'ordre croissant. La stratégie pour "incrémenter" B,
      c'est-à-dire pour passer au sous-ensemble suivant, est la
      suivante : on essaye d'incrémenter le plus petit élément de B,
      donc B[0], tout en restant strictement inférieur à l'élément
      suivant B[1]. Si cela n'est pas possible, on réinitialise B[0] à
      sa plus petite valeur, 0 ici, et on essaye d'incrémenter le
      second plus petit élément de B, soit B[1]. On arête si on a pas
      pu incrémenter B[k-1] sans dépasser la sentiennelle B[k]=n. Dès
      qu'on a trouvé un élément B[i] que l'on peut incrémenter on le
      fait, et on a donc généré le nouvel ensemble B. On recommence
      ensuite la méthode en essayant d'incrémenter le plus petit
      élement, etc. A priori l'algorithme est en O(N*k), mais de
      manière amortie c'est sans doute moins, on incrémente moins
      souvent B[j] que B[i] si j>i. Ceci dit on paye de toute façon
      une copie du tableau REP=B de taille k pour chacun des N
      sous-ensembles. Cela reste en O(N*k).
     */

    B=AllocInt(k+1);
    for(x=0;x<k;x++) B[x]=x;
    B[k]=n; /* sentinelle importante */

    v=0; /* v=sommet courant */
    goto jump1; /* la première fois REP[0]=B */

    while(x<k){
      if(++B[x]<B[x+1]){ /* cas où B est correct */
      jump1:
	x=0;
	for(y=0;y<k;y++) REP[v][y]=B[y];
	v++;
      }
      else B[x]=x++; /* B n'est pas correct */
    }

    free(B);
    return N;
  }

  /*
    Calcule si l'intersection possède au plus r éléments. L'algorithme
    ici est en O(k) en utilisant le fait que les éléments de REP sont
    rangés dans un ordre croissant.
   */

  v=0; /* v=nb d'élements commun */
  x=y=0; /* indices pour i et j */
  k=PARAM[1];
  r=PARAM[2];

  while((v<=r)&&(x<k)&&(y<k)){
    if(REP[i][x]==REP[j][y]) {
      v++;
      x++;
      y++;
    }
    else
      if(REP[i][x]<REP[j][y]) x++; else y++;
  }

  return (v<=r);
}


/***********************************

           GRAPHES DE BASE
               (fin)

***********************************/

int InitVertex(int n){
/*
** Remplit le tableau V[] donnant l'étiquette du sommet i.
** Si PERMUTE est vrai V est remplit d'une permutation aléatoire de [0,n[
** V[i]=-1 signifie que i a été supprimé.
** La fonction retourne le nb de sommets supprimés d'étiquette >=0.
** Si k sommets on été supprimé, alors les valeurs de V sont dans [0,n-k[
*/	

  int i,j,k,seuil;

  seuil=(double)DELV*(double)RAND_MAX;
  j=0;
  for(i=0;i<n;i++)
    if(rand()<seuil) V[i]=-1; else V[i]=j++;

  if(PERMUTE)
    for(i=0;i<n;i++){
      j=i+(rand()%(n-i));
      k=V[j]; V[j]=V[i]; V[i]=k;
    }

  return j;
}


int LAST=-1;     /* extrémité de la dernière arête affichée */

void Out(int i,int j){
  /*
    Affiche l'arête i-j.
    Si j<0, alors affiche i seul (sommet isolé).
    Si i=LAST, alors affiche ...-j.
    Si i<0, alors affiche un retour de ligne (fin de fonction)
   */
  char *s;

  if(i<0){ printf("\n"); return; }

  s=(LIGNE==0)?"":" ";

  if(j<0){
    printf("%s%i",s,V[i]);
    LAST=-1;
    goto ligne;
  }

  if(i==LAST){
    printf("-%i",V[j]);
    LAST=j;
    goto ligne;
  }

  printf("%s%i-%i",s,V[i],V[j]);
  LAST=j;
  
 ligne:
  if(LIGNE++>LMAX){
    LIGNE=0;
    LAST=-1;
    printf("\n");
  }
}


void Help(void){
  /*
    Affiche l'aide en ligne
  */

  char s[256]="sed -n '/*[#] ###/,/### #/p' ";
  strcat(strcat(s,ARGV[0]),".c");
  strcat(s," | sed 's/\\/\\*[#] ###//g'");
  strcat(s," | sed 's/### [#]\\*\\///g' | more");
  system(s);
  exit(0);
}


char *NextArg(int *i){
  /*
    Retourne argv[i] s'il existe, puis incrémente i
  */

  if((*i)==ARGC) Erreur(1);
  return ARGV[(*i)++];
}

/***********************************

               MAIN

***********************************/


int main(int argc, char *argv[]){

  int (*adj)(int i,int j);
  int i,j,k,seuil,*inc;
  
  ARGC=argc;
  ARGV=argv;

  if(argc==1) Help(); /* aide si aucun argument */

  adj=ring; PARAM[0]=0; /* valeurs par défaut */

  /* analyse de la ligne de commande */

  i=1; seuil=getpid();
  while(i<argc){
    if ARG("-help") Help();

    j=i;
    if ARG("-seed"){ i++;
      seuil=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("-permute"){ i++;
      PERMUTE=1;
      goto fin;
    }
    if ARG("-not"){ i++;
      NOT=1-NOT;
      goto fin;
    }
    if ARG("-delv"){ i++;
      DELV=atof(NextArg(&i));
      goto fin;
    }
    if ARG("-dele"){ i++;
      DELE=atof(NextArg(&i));
      goto fin;
    }
    if ARG("path"){ i++;
      adj=grid;
      PARAM[0]=1;
      PARAM[1]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("tree"){ i++;
      adj=tree;
      PARAM[0]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("prime"){ i++;
      adj=prime;
      PARAM[0]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("hypercube"){ i++;
      adj=grid;
      PARAM[0]=atoi(NextArg(&i));
      if(PARAM[0]+1>DIMAX) Erreur(4);
      for(k=0;k<PARAM[0];k++) PARAM[k+1]=2;
      goto fin;
    }
    if ARG("torus"){ i++;
      adj=grid;
      PARAM[0]=2;
      PARAM[1]=-atoi(NextArg(&i));
      PARAM[2]=-atoi(NextArg(&i));
      goto fin;
    }
    if ARG("mesh"){ i++;
      adj=grid;
      PARAM[0]=2;
      PARAM[1]=atoi(NextArg(&i));
      PARAM[2]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("ring"){ i++;
      adj=ring;
      PARAM[0]=atoi(NextArg(&i));
      PARAM[1]=atoi(NextArg(&i));
      if(PARAM[1]+2>DIMAX) Erreur(4);
      for(k=0;k<PARAM[1];k++)
	PARAM[k+2]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("grid"){ i++;
      adj=grid;
      PARAM[0]=atoi(NextArg(&i));
      if(PARAM[0]+1>DIMAX) Erreur(4);
      for(k=0;k<PARAM[0];k++)
	PARAM[k+1]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("cycle"){ i++;
      adj=ring;
      PARAM[0]=atoi(NextArg(&i));
      PARAM[1]=PARAM[2]=1;
      goto fin;
    }
    if ARG("stable"){ i++;
      adj=ring;
      PARAM[0]=atoi(NextArg(&i));
      PARAM[1]=0;
      goto fin;
    }
    if ARG("clique"){ i++;
      adj=ring;
      NOT=1-NOT;
      PARAM[0]=atoi(NextArg(&i));
      PARAM[1]=0;
      goto fin;
    }
    if ARG("random"){ i++;
      adj=ring;
      NOT=1-NOT;
      PARAM[0]=atoi(NextArg(&i));
      DELE=1.0-atof(NextArg(&i));
      PARAM[1]=0;
      goto fin;
    }
    if ARG("interval"){ i++;
      adj=interval;
      PARAM[0]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("permutation"){ i++;
      adj=interval;
      PARAM[0]=atoi(NextArg(&i));
      goto fin;
    }
    if ARG("petersen"){ i++;
      adj=kneser;
      PARAM[0]=5;
      PARAM[1]=2;
      PARAM[2]=0;
      goto fin;
    }
    if ARG("kneser"){ i++;
      adj=kneser;
      PARAM[0]=atoi(NextArg(&i));
      PARAM[1]=atoi(NextArg(&i));
      PARAM[2]=atoi(NextArg(&i));
      if(PARAM[1]>PARAM[0]/2) PARAM[1]=PARAM[0]-PARAM[1];
      goto fin;
    }
  fin:
    if(j==i) Erreur(2); /* option non trouvée */
  }

  srand(seuil); /* initialise le générateur aléatoire */
  adj(-1,0); /* initialisation du graphe, calcul N avant
                suppression des sommets */

  V=AllocInt(N);
  InitVertex(N);
  seuil=(double)(1.0-DELE)*(double)RAND_MAX;
  inc=AllocInt(N); /* inc[i]=1 ssi i possède un voisin */
  for(i=0;i<N;i++) inc[i]=0;

  /* génère les adjacences i-j en tenant
     compte des sommets isolés et des sommets supprimés */

  for(i=0;i<N;i++)
    if(V[i]>=0){
      for(j=i+1;j<N;j++)
	if(V[j]>=0)
	  if((rand()<seuil)&&(adj(i,j)^NOT)){
	    inc[i]=inc[j]=1;
	    Out(i,j);
	  }
      if(inc[i]==0) Out(i,-1);
    }

  Out(-1,0); /* fin d'affichage */
  adj(0,-1); /* libère éventuellement la mémoire utilisée pour adj() */

  free(V);
  free(inc);
  return 0;
}

/*# ###
Générateur de graphes - v1.2 - © Cyril Gavoille - Octobre 2007

USAGE

       gengraph [-option] graph_name parameter_list


DESCRIPTION

       Permet de générer un graphe non orienté sous forme d'une liste
       d'adjacence (voir le format exact ci-dessous). En paramètre
       figure le type de graphe ainsi que ses paramètres éventuels
       (par exemple le nombre de sommets, etc.).


OPTIONS

-help

       Affiche ce texte, c'est-à-dire l'aide en ligne, qui est
       contenue dans le fichier source (.c) du générateur. Pour cela,
       le fichier source doit être dans le même répertoire que la
       commande.

-permute

       Permet de permuter aléatoirement le nom des sommets qui restent
       dans l'intervalle [0,n[ où n est le nombre de sommets du graphe
       généré.

-dele p
      
       Permet de supprimer chaque arête du graphe générée avec
       probabilité p.

-delv p

       Similaire à -dele p, mais concerne les sommets. Le sommets et
       ses arêtes incidentes sont alors supprimées. Si k sommets sont
       supprimés, alors le nom des sommets restant sont dans
       l'intervalle [0,n-k[ où n est le nombre de sommets initial du
       graphe. Les noms des sommets sont donc éventuellement
       renumérotés.

-not

       Inverse la fonction d'adjacence, et donc affiche le complément du
       graphe.

-seed s

       Permet d'initialiser le générateur aléatoire avec la graine s,
       permettant de générer plusieurs fois la même suite
       aléatoire. Par défaut, la graine est initialisée avec le numéro
       de processus de la commande, donc génère par défaut des suites
       différentes à chaque lancement.


-format type

       Option non encore implémentée.

       Pour l'instant le format est une liste d'arêtes, les sommets
       étant numéroté consécutivement de 0 à n-1 où n est le nombre de
       sommets présents dans le graphe, une arête entre i et j étant
       de la forme i-j.  Les sommets isolés et les arêtes (ou suite
       d'arêtes) sont séparés par des espaces ou des sauts de
       ligne. Par exemple, le texte : 0 1-2-3-1 représente un graphe à
       4 sommets, composé d'un cycle à trois sommets (1,2,3) et d'un
       sommet isolé (0).


GRAPHES

       Deux types de graphes sont possibles : les graphes de base et les
       graphes composés. Ces derniers peuvent être obtenus en modifiant, à
       l'aide des options, un graphe de base.


  GRAPHES DE BASE :

    grid d n_1 ... n_d
       Grille à d dimensions de taille n_1 x ... x n_d. Si la dimension
       n_i est négative, alors cette dimension est cyclique.
       E.g. "grid 1 -10" donnera un cycle à 10 sommets.

    ring n k c_1 ... c_k
       Anneaux de cordes à n sommets avec k cordes de longueur c_1,...,c_k.

    tree n
       Arbre plan enraciné aléatoire à n sommets.

    kneser n k r
       Graphe de Kneser généralisé, le graphe de Kneser K(n,k)
       original est obtenu avec r=0. Les sommets sont tous les
       sous-ensembles à k éléments de [0,n[, et i et j sont adjacents
       ssi leurs ensembles correspondant ont au plus r éléments en
       commun. Le nombre chromatique de K(n,k), établit par Lovasz,
       vaut n-2k+2 pour tout n>=2k-1>0.

    interval n
       Graphe d'intersection de n intervalles aléatoires uniformes de [0,2n[.

    permutation n
       Graphe de permutation sur une permutation aléatoire uniformes de [0,n[.

    prime n
       Graphe à n sommets tel que i-j ssi i>1 et j divisible par i.


  GRAPHES COMPOSES :

    mesh p q (grid 2 p q)
       Grille 2D de p x q sommets.

    hypercube d (grid d 2 ... 2)
       Hypercube de dimension d.

    path n (grid 1 n)
       Chemin à n sommets.

    cycle n (ring n 1 1)
       Cycle à n sommets.

    torus p q (grid 2 -p -q)
       Tore à p x q sommets.

    stable n (ring n 0)
       Stable à n sommets.

    clique n (-not ring n 0)
       Graphe complet à n sommets.

    random n p (-not ring n 0 -dele 1-p)
       Graphe aléatoire à n sommets et de probabilité d'avoir une arête p.

    petersen (kneser 5 2 0)
       Graphe de Kneser particulier bien connu à 10 sommets et 3-régulier.


A FAIRE :

       outerplanar n: arbre plan bicoloré sauf la dernière branche
       geometric n r: intersection graph of radius-r balls in [0,1]^2
       -redirect p: avec proba p redirige l'arête uniformément

### #*/
