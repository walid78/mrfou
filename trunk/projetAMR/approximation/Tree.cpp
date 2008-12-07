#include <string>

#include "Tree.hpp"

/** Constructeur : **/
//===========================================================================
Tree::Tree(Graph& g, int node = 0):nbVertexes(g.getNbVertexes()){
  root = node;
  makeTreeDFS(g, node);
}

/** Fonctions membres : **/
//===========================================================================
void Tree::makeTreeDFS(Graph& g, int node){
  tree = Graph(nbVertexes, "");
}

