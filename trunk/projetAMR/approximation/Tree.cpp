#include "Tree.hpp"

/** Constructeur : **/
//===========================================================================
Tree::Tree(const Graph& g, int node):nbVertexes(g.getNbVertexes()){
  makeTreeDFS(g, node);
}


Tree::Tree(const Graph& g){
  this(g, 0);
}

/** Fonctions membres : **/
//===========================================================================
void Tree::makeTreeDFS(const Graph&, int node){
  tree(nbVertexes, "");
}
