#include <iostream>
#include <sstream>
#include <vector>

#include "IndepSet.hpp"

/** Constructeur : **/
//===========================================================================
IndepSet::IndepSet(Graph g, int size):graph(g),
				      indepSetSize(size),
				      clique(g.complementary(), size){

}

/** Destructeur : **/
//===========================================================================
IndepSet::~IndepSet(){
	
}

/** Fonctions membres : **/
//===========================================================================
int IndepSet::getMaxNbEdgesInIndepSet(int nbV, int size){
  //Nombre maximum d'arêtes dans un graphe de nbVertexes sommets
  int NB_MAX_EDGES = nbV * (nbV-1) / 2;
  
  return NB_MAX_EDGES - clique.getMinNbEdgesInClique(size);
}

//===========================================================================
int IndepSet::easyCases(){
  int nbVertexes = graph.getNbVertexes();

  /* Cas faciles */

  //IS de taille < 0 => Erreur
  if(indepSetSize < 0)
    return 1;

  //IS de taille 0 => Toujours vrai
  if(indepSetSize == 0)
    return 2;

  //IS de taille 1 => Toujours vrai
  if(indepSetSize == 1)
    return 3;

  //IS de taille supérieure au nombre de sommets => Impossible
  else if(indepSetSize > nbVertexes)
    return 4;
  else{
    int nbEdges = graph.getNbEdges();

    //On a forcément un IS si le nombre d'arête est trop faible
    if(nbEdges < nbVertexes - indepSetSize + 1)
      return 5;

    //Pour que k sommets puissent former un IS dans un graphe de taille n,
    //Il ne faut pas que le nombre d'arêtes dépasse un certain nombre
    //Exemple : Pour un IS de taille 1 dans un graphe de 4 sommets, le nombre
    //d'arêtes ne doit pas dépasser 3.
    else if(nbEdges > getMaxNbEdgesInIndepSet(nbVertexes, indepSetSize))
      return 6;
  }
  
  return 0;
}

//===========================================================================
string IndepSet::getSolution(){
  stringstream answer;
  int nbVertexes = graph.getNbVertexes();
  int easyCase = easyCases();
  string line;
   
  /* Cas faciles
   *
   * 1) IS de taille < 0 => Erreur
   * 2) IS de taille 0 => Toujours vrai
   * 3) IS de taille 1 => Nécessite la présence d'un seul sommet
   * 4) IS de taille supérieure au nombre de sommets => Impossible
   * 5) On a forcément un IS d'une certaine taille si le nombre d'arête est trop faible
   * 6) Pour que k sommets puissent former un IS dans un graphe de taille n,
   **** Il ne faut pas que le nombre d'arêtes dépasse un certain nombre
   **** Exemple : Pour un IS de taille 1 dans un graphe de 4 sommets, le nombre
   **** d'arêtes ne doit pas dépasser 3.
   *
   */

  switch(easyCase){
    
  case 0:
    break;
    
  case 1:
    // 1) IS de taille < 0 => Erreur
    answer << "Erreur sur la taille de la couverture entrée.";
    break;
   
  case 2:
    // 2) IS de taille 0 => Toujours vrai
    answer << "Un graphe admet toujours un ensemble indépendant de taille " << 
      indepSetSize << " par définition.";
    break;
   
  case 3:
    // 3) IS de taille 1 => Nécessite la présence d'un seul sommet
    if(nbVertexes > 0)
      // Avec 1 sommet => vrai
      answer << "Le graphe admet un ensemble indépendant de taille 1, il suffit de " <<
	"choisir un sommet.";
    else
      // Sans sommet => faux
      answer << "Le graphe n'admet pas d'ensemble indépendant de taille 1 car " <<
	"il n'a aucun sommet.";
    break;
   
  case 4:
    // 4) IS de taille supérieure au nombre de sommets => Impossible
    answer << "Le graphe n'admet pas d'ensemble indépendant de taille " << 
      indepSetSize << " car le nombre de sommets du graphe (" << nbVertexes << 
      ") est " << "inférieur à cette taille (" << indepSetSize << ").";
    break;
    
  case 5:
    // 5) On a forcément un IS si le nombre d'arête est trop faible
    cout << "Le graphe admet forcément un ensemble indépendant de taille " << 
      indepSetSize << " car le nombre trop faible d'arêtes du graphe (" << 
      graph.getNbEdges() << ") oblige le graphe à contenir un ensemble indépendant " <<
      "de cette taille." << endl;

    // Voulez-vous un exemple d'ensemble indépendant ?
    while((line.compare("O")) && (line.compare("N"))){
      cout << "Voulez-vous un exemple d'ensemble indépendant ? (O/N) " << endl;
      cin >> line;
    }

    if(!line.compare("O"))
      easyCase = 7;
    break;
   
  case 6:
    // 6) Pour que k sommets puissent former un IS dans un graphe de taille n,
    // Il ne faut pas que le nombre d'arêtes dépasse un certain nombre
    // Exemple : Pour un IS de taille 1 dans un graphe de 4 sommets, le nombre
    // d'arêtes ne doit pas dépasser 3.
    answer << "Le graphe n'admet pas d'ensemble indépendant de taille " << indepSetSize <<
      " car le nombre d'arêtes du graphe (" << graph.getNbEdges() << ") est " <<
      "trop grand (il en faudrait au maximum " << getMaxNbEdgesInIndepSet(nbVertexes, 
									  indepSetSize) << 
      ") pour pouvoir espérer former " << "un ensemble indépendant de taille " <<
      indepSetSize << ".";
    break;
   
  default:
    cerr << "Résultat inattendu" << endl;
    exit(0);
  }

  if((easyCase > 0) && (easyCase < 7))
    return answer.str();

  /* Calcul */
  string s;
  bool* varAssign = clique.transmitSolution();
  
  //solve renvoie NULL lorsque c'est non sat
  if(varAssign == NULL){
    answer << "Le graphe n'admet pas d'ensemble indépendant de taille " << 
      indepSetSize << ".";
    s = answer.str();
  }else{
    answer << "Le graphe admet un ensemble indépendant de taille " << 
      indepSetSize << "." << endl << 
      "Il suffit de considérer les sommets suivants :" << endl << "{ ";

    for(int i=0 ; i<graph.getNbVertexes()*indepSetSize ; ++i){
      if(varAssign[i])
	answer << (i/indepSetSize) << ", ";
    }

    s = answer.str();
    int size = s.size();
    s[size-2]= ' ';
    s[size-1]= '}';
  }

  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const IndepSet& ch){
  return o << ch.graph;
}
