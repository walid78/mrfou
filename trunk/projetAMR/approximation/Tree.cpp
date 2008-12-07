#include "Tree.hpp"

/** Constructeur : **/
//===========================================================================
Tree::Tree(const Graph& g, int node):nbVertexes(g.getNbVertexes()),
				     root(node){
  makeTreeDFS(g, node);
}


Tree::Tree(const Graph& g):root(0){
  Tree(g, 0);
}

/** Fonctions membres : **/
//===========================================================================
void Tree::makeTreeDFS(const Graph&, int node){
  tree(nbVertexes, "");
}
