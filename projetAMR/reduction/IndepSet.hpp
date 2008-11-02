#ifndef INDEPSET_HPP
#define INDEPSET_HPP

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.hpp"
#include "MinisatBuilder.hpp"
#include "Clique.hpp"

using namespace std;

class IndepSet{

  friend ostream& operator<<(ostream& o, const IndepSet& is);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
public:
  //===========================================================================
  /** Constructeur : **/
  IndepSet(Graph g, int size);
  
  //===========================================================================
  /** Destructeur : **/
  ~IndepSet();
  
  //===========================================================================
  /** Fonctions membres : **/
  string getSolution();
  
  /*-*-*-*-* PRIVATE *-*-*-*-*/
private:
  //===========================================================================
  /** Attributs **/
  Graph graph;
  int indepSetSize;
  Clique clique;
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const IndepSet& is);

#endif
