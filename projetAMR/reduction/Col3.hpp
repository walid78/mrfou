#ifndef COL3_HPP
#define COL3_HPP

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.h"
//#include "MinisatBuilder.hpp"

using namespace std;

class Col3{

  friend ostream& operator<<(ostream& o, const Col3& ch);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
 public:
    //===========================================================================
  /** Constructeur : **/
  Col3(Graph g);
  
  //===========================================================================
  /** Destructeur : **/
  ~Col3();
  
  //===========================================================================
  /** Fonctions membres : **/
  string getSolution();
  
  /*-*-*-*-* PRIVATE *-*-*-*-*/
 private:
  //===========================================================================
  /** Attributs **/
  Graph graph;
  int nbClauses;
  int nbVars;
  char* pathFile;

  //===========================================================================
  /** Fonctions membres **/
  string generateCNFFormula();
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const Col3& g);


#endif
