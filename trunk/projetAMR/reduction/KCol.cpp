#include <vector>
#include <iostream>
#include <sstream>

#include "KCol.hpp"
#include "MinisatBuilder.hpp"

#define N NB_COLORS

/** Constructeur : **/
//===========================================================================
KCol::KCol(Graph g, int nbColors):graph(g),
				  pathFile(g.getPathFile()),
				  NB_COLORS(nbColors){
  nbVars = g.getNbVertexes()*N;
  nbClauses = 0;
}

/** Destructeur : **/
//===========================================================================
KCol::~KCol(){
	
}

/** Fonctions membres : **/
//===========================================================================
string KCol::generateCNFFormula(){
  stringstream CNFFormula;
  
  int nbVertexes = graph.getNbVertexes();
  
  /* Chaque sommet est colorié */
  CNFFormula << "c Chaque sommet est colorié" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=1 ; j<=N ; ++j)
      CNFFormula << (N*i+j) << " ";
    CNFFormula << "0" << endl;
    ++nbClauses;
  }

  /* Une seule couleur par sommet */
  CNFFormula << "c Une seule couleur par sommet" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=1 ; j<=N ; ++j)
      for(int k=1 ; k<=N ; ++k)
	if(j < k){
	  CNFFormula << "-" << (N*i+j) << " -" << (N*i+k) << " 0" << endl;
	  nbClauses++;
	  
	}

  /* Deux sommets qui se suivent n'ont pas la même couleur */
  CNFFormula << "c Deux sommets qui se suivent n'ont pas la même couleur" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      for(int k=1 ; k<=N ; ++k)
	if(i < graph[i][j]){
	  CNFFormula << "-" << (N*i+k) << " -" << (N*graph[i][j]+k) << " 0" << endl;
	  nbClauses++;
	}

  return CNFFormula.str();
}

//===========================================================================
int KCol::easyCases(){

  /* Cas faciles */

  //Le nombre de couleurs est négatif  
  if(N <= 0)
    return 1;

  //Le nombre de couleurs est supérieur au nombre de sommets
  else if(N >= graph.getNbVertexes())
    return 2;
  
  else 
    return 0;
}

//===========================================================================
string KCol::getSolution(){
  stringstream answer;
  int easyCase = easyCases();

  /* Cas faciles 
   * 
   * 1) Le nombre de couleurs est négatif  
   * 2) Le nombre de couleurs est supérieur au nombre de sommets
   *
   */

  switch(easyCase){
    
  case 0:
    break;

  case 1:
    // 1) Le nombre de couleurs est négatif  
    answer << "Le nombre de couleurs proposé n'est pas correct.";
    break;

  case 2:
    // 2) Le nombre de couleurs est supérieur au nombre de sommets
    answer << "Coloration évidente des sommets en prenant pour chacun" <<
      " une couleur différente.";
    break;

  default:
    cerr << "Résultat inattendu" << endl;
    exit(0);
  }
    
  if((easyCase > 0) && (easyCase < 3))
    return answer.str();

  /* Calcul */

  MinisatBuilder mb(pathFile,
		    nbVars,
		    nbClauses,
		    generateCNFFormula()
		    );

  bool* varAssign = mb.solve();

  int nbVertexes = graph.getNbVertexes();
  string s;
      
  if(varAssign == NULL){
    answer << "Le graphe n'admet pas de " << N << "-Coloration.";
    return answer.str();
  }else{
    answer << "Le graphe admet une " << N << "-Coloration." << endl <<
      "Il suffit de considérer la coloration des sommets suivante :" << endl <<
      "{ ";
    
    for(int i=0 ; i<nbVertexes ; ++i){
      for(int j=1 ; j<=N ; ++j){
	if(varAssign[N*i+j-1]){
	  answer << i << " -> C" << j << ", ";
	  //	  if(((i%10) == 0) && (i!=0) && (i!=nbVertexes-1))
	  // answer << endl;
	}
      }
    }

    s = answer.str();
    int size = s.size();
    s[size-2]= ' ';
    s[size-1]= '}';
  }

  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const KCol& kc){
  return o << kc.graph;
}
