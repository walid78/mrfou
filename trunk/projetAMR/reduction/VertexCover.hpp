#ifndef VERTEXCOVER_HPP
#define VERTEXCOVER_HPP

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.hpp"
#include "MinisatBuilder.hpp"
#include "Clique.hpp"

using namespace std;

class VertexCover{

  friend ostream& operator<<(ostream& o, const VertexCover& ch);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
public:
  //===========================================================================
  /** Constructeur : **/
  VertexCover(Graph g, int size);
  
  //===========================================================================
  /** Destructeur : **/
  ~VertexCover();
  
  //===========================================================================
  /** Fonctions membres : **/
  string getSolution();
  
  /*-*-*-*-* PRIVATE *-*-*-*-*/
private:
  //===========================================================================
  /** Attributs **/
  Graph graph;
  int coverSize;
  Clique clique;
  int easyCases();
  int getMaxNbEdgesInVertexCover(int nbV, int size);
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const VertexCover& g);


#endif
