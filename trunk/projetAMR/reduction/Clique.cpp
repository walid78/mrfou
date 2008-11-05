#include <iostream>
#include <sstream>
#include <vector>

#include "Clique.hpp"

/** Constructeur : **/
//===========================================================================
Clique::Clique(Graph g, int size):graph(g),
				  cliqueSize(size),
				  pathFile(g.getPathFile()){
  
  int nbVertexes = g.getNbVertexes();

  nbVars = 0;
  nbClauses = 0;

  // Remplissage du tableau des variables en mettant cliqueSize variables k par 
  // sommet pour exprimer le fait que le sommet est en k^ième position
  for(int i=0 ; i<nbVertexes ; ++i){
    vars.push_back(vector<int>(size, -1));
    for(int j=0 ; j<size ; ++j)
      vars[i][j] = ++nbVars;
  }
}

/** Destructeur : **/
//===========================================================================
Clique::~Clique(){
	
}

/** Fonctions membres : **/
//===========================================================================
string Clique::generateCNFFormula(){
  stringstream CNFFormula;
  
  int nbVertexes = graph.getNbVertexes();

  /* Chaque noeud est dans la clique <=>
     Au moins un noeud est le jième sommet de la clique */
  CNFFormula << "c Chaque noeud est dans la clique <=>" << endl;
  CNFFormula << "c Au moins un noeud est le jième sommet de la clique" << endl;
  for(int j=0 ; j<cliqueSize ; ++j){
    for(int i=0 ; i<nbVertexes ; ++i){
      CNFFormula << vars[i][j] << " ";
    }
    CNFFormula << "0" << endl;
    nbClauses++;
  }
 
  /* Un noeud a exactement une position dans la clique <=>
     Aucun noeud n'est le jième et le lième sommet de la clique */
  CNFFormula << "c Un noeud a exactement une position dans la clique <=>" << endl;
  CNFFormula << "c Aucun noeud n'est le jième et le kième sommet de la clique" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<cliqueSize ; ++j)
      for(int k=j+1 ; k<cliqueSize ; ++k){
	CNFFormula << "-" << vars[i][j] << " -" << vars[i][k] << " 0" << endl;
	nbClauses++;
      }

  /* Deux sommets non voisins ne peuvent pas être ensemble dans la clique */
  CNFFormula << "c Deux sommets non voisins ne peuvent pas être ensemble " << 
    "dans la clique" << endl;

  for(int i=0 ; i<nbVertexes ; ++i){
    vector<bool> noEdge(nbVertexes, true);
    noEdge[i] = false;
    // On enlève les sommets reliés à i
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      noEdge[graph[i][j]] = false;
    }

    for(int i2=i+1 ; i2<nbVertexes ; ++i2)
      if(noEdge[i2])
	for(int j=0 ; j<cliqueSize ; ++j)
	  for(int k=0 ; k<cliqueSize ; ++k)
	    if(j != k){
	      CNFFormula << "-" << vars[i][j] << " -" << vars[i2][k] << " 0" << endl;
	      nbClauses++;
	    }
  }
   
  /* Deux sommets n'ont pas la même position dans la clique
   */
  CNFFormula << "c Deux sommets n'ont pas la même position dans la clique" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int i2=i+1; i2<nbVertexes ; ++i2)
      for(int j=0 ; j<cliqueSize ; ++j){
	CNFFormula << "-" << vars[i][j] << " -" << vars[i2][j] << " 0" << endl;
	nbClauses++;
      }
    
  return CNFFormula.str();
}

//===========================================================================
bool* Clique::transmitSolution(){
  MinisatBuilder mb(pathFile,
		    nbVars,
		    nbClauses,
		    generateCNFFormula()
		    );
  return mb.solve();
}

//===========================================================================
int Clique::getMinNbEdgesInClique(int size){
  if(size <= 1)
    return 0;
  else 
    return getMinNbEdgesInClique(size-1) + (size-1);
}

//===========================================================================
int Clique::getMinNbEdgesWhichObligesClique(int nbVert){
  //int nbVertexes = graph.getNbVertexes();
  if(cliqueSize == nbVert)
    return getMinNbEdgesInClique(nbVert);
  else 
    return getMinNbEdgesWhichObligesClique(nbVert-1) + (nbVert + cliqueSize - 3) / 2;
}

int Clique::easyCases(){

  int nbVertexes = graph.getNbVertexes();

  /* Cas faciles */

  //Clique de taille < 0 => Erreur
  if(cliqueSize < 0)
    return 1;

  //Clique de taille 0 => Toujours vrai
  if(cliqueSize == 0)
    return 2;

  //Clique de taille 1 => 1 sommet
  else if(cliqueSize == 1)
    return 3;
  
  //Clique de taille 2 => 1 arête
  else if(cliqueSize == 2)
    return 4;

  //Clique de taille supérieure au nombre de sommets => impossible
  else if(cliqueSize > nbVertexes)
    return 5;
  else{
    int nbEdges = graph.getNbEdges();
    
    //A partir d'un certain nombre d'arêtes par rapport à un nombre de sommets,
    //Il est obligatoire d'obtenir une clique d'une certaine taille
    if(getMinNbEdgesWhichObligesClique(nbVertexes) <= nbEdges){
      return 6;
      
    }else{
      int minNbEdgesInClique = getMinNbEdgesInClique(cliqueSize);
      //Il faut un nombre d'arêtes minimum pour former une clique d'une certaine taille
      //Exemple : clique 3 -> 3 arêtes min, clique 4 -> 6 arêtes min.
      if(nbEdges < minNbEdgesInClique){
	return 7;
      }
    }
  }
  
  return 0;
}

//===========================================================================
string Clique::getSolution(){

  stringstream answer;
  int nbVertexes = graph.getNbVertexes();
  int easyCase = easyCases();
  int nbEdges = graph.getNbEdges();
  char c = ' ';

  /* Cas faciles 
   * 
   * 1) Clique de taille < 0 => Erreur en entrée
   * 2) Clique de taille 0 => Toujours vrai
   * 3) Clique de taille 1 => nécessite 1 sommet
   * 4) Clique de taille 2 => nécessite 1 arête
   * 5) Clique de taille supérieure au nombre de sommets => impossible
   * 6) A partir d'un certain nombre d'arêtes par rapport à un nombre de sommets,
   **** Il est obligatoire d'obtenir une clique d'une certaine taille
   * 7) Il faut un nombre d'arêtes minimum pour former une clique d'une certaine taille
   **** Exemple : clique 3 -> 3 arêtes min, clique 4 -> 6 arêtes min.
   *
   */

  switch(easyCase){

  case 0:
    break;

  case 1:
    // 1) Clique de taille < 0 => Erreur en entrée
    answer << "Erreur sur la taille de la clique entrée.";
    break;

  case 2:
    // 2) Clique de taille 0 => Toujours vrai
    answer << "Tout graphe a une clique de taille 0.";
    break;

  case 3:
    // 3) Clique de taille 1 => 1 sommet
    if(nbVertexes > 0)
      // Avec 1 sommet => vrai
      answer << "Le graphe admet une clique de taille 1, il suffit de choisir un sommet.";
    else
      // Sans sommet => faux
      answer << "Le graphe n'admet pas de clique de taille 1 car il n'a aucun sommet.";
    break;
      
  case 4:
    // 4) Clique de taille 2 => nécessite 1 arête
    if(nbEdges > 0)
      // Avec 1 arête => vrai
      answer << "Le graphe admet une clique de taille 2, il suffit de choisir " << 
	"n'importe quelle arête.";
    else
      // Sans arête => faux
      answer << "Le graphe n'admet pas de clique de taille 2, car il n'a pas d'arête.";
    break;
      
  case 5:
    // 5) Clique de taille supérieure au nombre de sommets => impossible
    answer << "Le graphe n'admet pas de clique de taille " << cliqueSize <<
      " car le nombre de sommets du graphe (" << nbVertexes << ") est " <<
      "inférieur à cette taille (" << cliqueSize << ").";
    break;

  case 6:
    // 6) A partir d'un certain nombre d'arêtes par rapport à un nombre de sommets,
    // Il est obligatoire d'obtenir une clique d'une certaine taille
    cout << "Le graphe admet forcément une clique de taille " << cliqueSize <<
      " car le nombre d'arêtes du graphe (" << nbEdges << ") oblige le graphe " <<
      "à contenir une clique de taille (" << cliqueSize << ").";
      
      // Voulez-vous trouver une assignation des sommets ?
      while((c != 'O') && (c != 'N')){
	printf("Voulez-vous un exemple de clique ? (O/N)\n");
	scanf("%c",&c);
      }

      if(c == 'O')
	easyCase = 8;
      break;

  case 7:
    // 7) Il faut un nombre d'arêtes minimum pour former une clique d'une certaine taille
    // Exemple : clique 3 -> 3 arêtes min, clique 4 -> 6 arêtes min.
    answer << "Le graphe n'admet pas de clique de taille " << cliqueSize <<
      " car le nombre d'arêtes du graphe (" << nbEdges << ") est " <<
      "insuffisant (il en faudrait " << getMinNbEdgesInClique(cliqueSize) << 
      ") pour former " << "une clique de taille " << cliqueSize << ".";
    break;

  default:
    cerr << "Résultat inattendu" << endl;
    exit(0);
  }

  if((easyCase > 0) && (easyCase < 8))
    return answer.str();

  /* Calcul */
  MinisatBuilder mb(pathFile,
		    nbVars,
		    nbClauses,
		    generateCNFFormula()
		    );
  
  string s;
  bool* varAssign = mb.solve();
  
  //solve renvoie NULL lorsque c'est non sat
  if(varAssign == NULL){
    answer << "Le graphe n'admet pas de clique de taille " << cliqueSize << ".";
    s = answer.str();
  }else{
    answer << "Le graphe admet une clique de taille " << cliqueSize << "." << 
      endl << "Il suffit de considérer les sommets suivants :" << 
      endl << "{ ";
    
    for(int i=0 ; i<nbVars ; ++i){
      if(varAssign[i])
	answer << (i/cliqueSize) << ", ";
    }
    
    s = answer.str();
    int size = s.size();
    s[size-2]= ' ';
    s[size-1]= '}';
  }
  
  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const Clique& ch){
  return o << ch.graph;
}
