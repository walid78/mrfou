#ifndef TREE_HPP
#define TREE_HPP

#include "Graph.hpp"

class Tree{
  
public:
  //===========================================================================
  /** Constructeur : **/
  Tree(Graph& g, int r); 

  //===========================================================================
  /** Destructeur : **/
  ~Tree();

  //===========================================================================
  /** Fonctions membres : **/
  bool isLeaf();
  int getRoot();
  
private:
  //===========================================================================
  /** Attributs **/
  Graph tree;
  int root;
  int nbVertexes;

  //===========================================================================
  /** Fonctions membres : **/
  void makeTreeDFS(Graph& g, int r);
  void makeTreeDFS_aux(Graph& g, int node, bool* mark);
  
};

#endif
