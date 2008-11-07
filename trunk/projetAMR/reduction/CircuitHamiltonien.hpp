#ifndef CIRCUITHAMILTONIEN_HPP
#define CIRCUITHAMILTONIEN_HPP

#include "Graph.hpp"

using namespace std;

class CircuitHamiltonien{

  friend ostream& operator<<(ostream& o, const CircuitHamiltonien& ch);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
 public:
    //===========================================================================
  /** Constructeur : **/
  CircuitHamiltonien(Graph g);
  
  //===========================================================================
  /** Destructeur : **/
  ~CircuitHamiltonien();
  
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
ostream& operator<<(ostream& o, const CircuitHamiltonien& g);


#endif
