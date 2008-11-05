#include <iostream>
#include <sstream>
#include <vector>

#include "VertexCover.hpp"

/** Constructeur : **/
//===========================================================================
VertexCover::VertexCover(Graph g, int size):graph(g),
					    coverSize(size),
					    clique(g.complementary(), 
						   //si c'est négatif, le programme
						   //s'arrete sans utiliser clique
						   abs(graph.getNbVertexes() - size)){


}

/** Destructeur : **/
//===========================================================================
VertexCover::~VertexCover(){
	
}

/** Fonctions membres : **/
//===========================================================================
int VertexCover::getMaxNbEdgesInVertexCover(int nbV, int size){
  //Nombre maximum d'arêtes dans un graphe de nbVertexes sommets
  int NB_MAX_EDGES = nbV * (nbV-1) / 2;
  
  return NB_MAX_EDGES - clique.getMinNbEdgesInClique(nbV - size);
}

//===========================================================================
int VertexCover::easyCases(){

  int nbVertexes = graph.getNbVertexes();

  /* Cas faciles */

  //VC de taille < 0 => Erreur
  if(coverSize < 0)
    return 1;

  //VC de taille > nombre de sommets => Impossible
  else if(coverSize > nbVertexes)
    return 2;

  //Pour que k sommets puissent représenter une VC dans un graphe de taille n,
  //Il ne faut pas que le nombre d'arêtes dépasse un certain nombre.
  else if(graph.getNbEdges() > getMaxNbEdgesInVertexCover(nbVertexes, coverSize))
    return 3;
  
  return 0;
}


//===========================================================================
string VertexCover::getSolution(){
  stringstream answer;
  int nbVertexes = graph.getNbVertexes();
  
  int easyCase = easyCases();

  /* Cas faciles 
   * 
   * 1) VC de taille < 0 => Erreur
   * 2) VC de taille > nombre de sommets => Impossible
   * 3) Pour que k sommets puissent représenter une VC dans un graphe de taille n,
   **** Il ne faut pas que le nombre d'arêtes dépasse un certain nombre.
   *
   */
  
  switch(easyCase){
    
  case 0:
    break;
    
  case 1:
    // 1) VC de taille < 0 => Erreur
    answer << "Erreur sur la taille de la couverture entrée.";
    break;
   
  case 2:
    // 2) VC de taille > nombre de sommets => Impossible
    answer << "Le graphe n'admet pas de couverture par sommets de taille" << coverSize << 
      " car le nombre de sommets du graphe (" << nbVertexes << ") est " <<
      "inférieur à cette taille (" << coverSize << ").";
    break;
   
  case 3:
    // 3) Pour que k sommets puissent représenter une VC dans un graphe de taille n,
    // Il ne faut pas que le nombre d'arêtes dépasse un certain nombre.
    answer << "Le graphe n'admet pas de couverture de taille " << coverSize <<
      " car le nombre d'arêtes du graphe (" << graph.getNbEdges() << ") est " <<
      "trop grand (il en faudrait au maximum " << getMaxNbEdgesInVertexCover(nbVertexes, 
									     coverSize) << 
      ") pour pouvoir espérer former " << "une couverture.";
    break;
    
  default:
    cerr << "Résultat inattendu" << endl;
    exit(0);
  }

  if((easyCase > 0) && (easyCase < 4))
    return answer.str();


  /* Calcul */
  string s;

  bool* varAssign = clique.transmitSolution();
  
  //solve renvoie NULL lorsque c'est non sat
  if(varAssign == NULL){
    answer << "Le graphe n'admet pas de couverture par sommets de taille " << 
      coverSize << ".";
    s = answer.str();
  }else{
    answer << "Le graphe admet une couverture par sommets de taille " << 
      coverSize << "." << endl << 
      "Il suffit de considérer les sommets suivants :" << endl << "{ ";

    bool inClique[nbVertexes];
    
    for(int i=0 ; i<nbVertexes*(nbVertexes - coverSize) ; ++i){
      if(varAssign[i])
	inClique[i/(nbVertexes - coverSize)] = true;
    }

    for(int i=0 ; i<nbVertexes ; ++i){
      if(!inClique[i])
	answer << i << ", ";
    }

    s = answer.str();
    int size = s.size();
    s[size-2]= ' ';
    s[size-1]= '}';
  }

  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const VertexCover& ch){
  return o << ch.graph;
}
