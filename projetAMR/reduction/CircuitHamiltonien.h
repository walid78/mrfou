#ifndef CIRCUITHAMILTONIEN_H
#define CIRCUITHAMILTONIEN_H

#include <vector>
#include <iostream>
#include <sstream>

#include "Graph.h"

using namespace std;

class CircuitHamiltonien{

  friend ostream& operator<<(ostream& o, const CircuitHamiltonien& ch);

 public:
    //===========================================================================
  /** Constructeur : **/
  CircuitHamiltonien(Graph g);
  
  //===========================================================================
  /** Destructeur : **/
  ~CircuitHamiltonien();
  
  //===========================================================================
  /** Fonctions membres : **/
  vector<bool> getSolution();
  
  string generateFormule();
  
  //===========================================================================
  /** Opérateur interne : **/
  
 private:
  vector< vector<int> > vars;
  int nbVars;
  Graph graph;
};

//===========================================================================
/** Opérateur externe : **/
ostream& operator<<(ostream& o, const CircuitHamiltonien& g);


#endif
