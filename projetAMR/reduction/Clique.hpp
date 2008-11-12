#ifndef CLIQUE_HPP
#define CLIQUE_HPP

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.hpp"
#include "MinisatBuilder.hpp"

using namespace std;

class Clique{

  friend ostream& operator<<(ostream& o, const Clique& ch);

  /*-*-*-*-* PUBLIC *-*-*-*-*/
 public:
  //===========================================================================
  /** Constructeur : **/
  Clique(Graph g, int size);
  
  //===========================================================================
  /** Destructeur : **/
  ~Clique();
  
  //===========================================================================
  /** Fonctions membres : **/
  int getMinNbEdgesInClique(int size);
  int getMinNbEdgesWhichObligesClique(int size);
  string getSolution();
  bool* transmitSolution();
  
  /*-*-*-*-* PRIVATE *-*-*-*-*/
 private:
  //===========================================================================
  /** Attributs **/
  Graph graph;
  int nbClauses;
  int nbVars;
  int cliqueSize;
  vector< vector<int> > vars;
  string pathFile;

  //===========================================================================
  /** Fonctions membres **/
  string generateCNFFormula();
  int easyCases();

};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const Clique& g);


#endif
