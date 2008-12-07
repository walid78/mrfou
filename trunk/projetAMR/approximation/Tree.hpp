#ifndef TREE_HPP
#define TREE_HPP

#include "Graph.hpp"

using namespace std;

class Tree{
  
public:
  //===========================================================================
  /** Constructeur : **/
  Tree(const Graph& g, int node); 

  //===========================================================================
  /** Constructeur : **/
  ~Tree();

  //===========================================================================
  /** Fonctions membres : **/
  bool isLeaf();
  
private:
  //==========================================================================
  /** Attributs **/
  Graph graph;
  int nbVertexes;
  
}

#endif
