#ifndef HAMILCIRCUIT_HPP
#define HAMILCIRCUIT_HPP

#include "Graph.hpp"

using namespace std;

class HamilCircuit{

  friend ostream& operator<<(ostream& o, const HamilCircuit& ch);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
 public:
    //===========================================================================
  /** Constructeur : **/
  HamilCircuit(Graph g);
  
  //===========================================================================
  /** Destructeur : **/
  ~HamilCircuit();
  
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
  string pathFile;
  vector< vector<int> > vars;

  //===========================================================================
  /** Fonctions membres **/
  string generateCNFFormula();
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const HamilCircuit& g);


#endif
