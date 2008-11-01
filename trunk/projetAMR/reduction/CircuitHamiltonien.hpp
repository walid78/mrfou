#ifndef CIRCUITHAMILTONIEN_H
#define CIRCUITHAMILTONIEN_H

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.hpp"
#include "MinisatBuilder.hpp"

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
  char* pathFile;
  vector< vector<int> > vars;

  //===========================================================================
  /** Fonctions membres **/
  string generateCNFFormula();
  int* getEdgeFromVar(int var);
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const CircuitHamiltonien& g);


#endif
