#ifndef TREE_HPP
#define TREE_HPP

#include "Graph.hpp"

using namespace std;

class Tree{
  
public:
  //===========================================================================
  /** Constructeur : **/
  Tree(const Graph& g, int node); 
  Tree(const Graph& g); 

  //===========================================================================
  /** Destructeur : **/
  ~Tree();

  //===========================================================================
  /** Fonctions membres : **/
  bool isLeaf();
  
private:
  //===========================================================================
  /** Attributs **/
  Graph tree;
  int nbVertexes;

  //===========================================================================
  /** Fonctions membres : **/
  void makeTreeDFS(const Graph& g, int node);
 //  void makeTreeDFS_aux(const Graph& g, int node);
  
}

#endif
