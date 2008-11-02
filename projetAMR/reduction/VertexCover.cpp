#include <iostream>
#include <sstream>
#include <vector>

#include "VertexCover.hpp"

/** Constructeur : **/
//===========================================================================
VertexCover::VertexCover(Graph g, int size):graph(g),
					    coverSize(size),
					    clique(g.complementary(), 
						   graph.getNbVertexes() - size){

}

/** Destructeur : **/
//===========================================================================
VertexCover::~VertexCover(){
	
}

/** Fonctions membres : **/
//===========================================================================
string VertexCover::getSolution(){
  stringstream answer;

  string s;
  bool* varAssign = clique.transmitSolution();
  int nbVertexes = graph.getNbVertexes();
  
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
