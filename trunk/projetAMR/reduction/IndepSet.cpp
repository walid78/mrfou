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
string IndepSet::getSolution(){
  stringstream answer;

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
