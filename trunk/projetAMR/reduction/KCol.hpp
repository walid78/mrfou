#ifndef KCOL_HPP
#define KCOL_HPP

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.h"
//#include "MinisatBuilder.hpp"

using namespace std;

class KCol{

  friend ostream& operator<<(ostream& o, const KCol& ch);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
 public:
    //===========================================================================
  /** Constructeur : **/
  KCol(Graph g, int nbColors);
  
  //===========================================================================
  /** Destructeur : **/
  ~KCol();
  
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

  /** Constante **/
  const int NB_COLORS;

  //===========================================================================
  /** Fonctions membres **/
  string generateCNFFormula();
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const KCol& g);


#endif
