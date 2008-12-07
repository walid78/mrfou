#include <string>
#include <iostream>

#include "Tree.hpp"

using namespace std;

/** Constructeur : **/
//===========================================================================
Tree::Tree(Graph& g, int r):nbVertexes(g.getNbVertexes()){
  root = r;
  makeTreeDFS(g, root);
}

/** Destructeur : **/
Tree::~Tree(){
  
}

/** Fonctions membres : **/
//===========================================================================
void Tree::makeTreeDFS(Graph& g, int r){
  tree = Graph(nbVertexes, "");
  
  bool* mark = new bool(nbVertexes);
  
  for(int i=0 ; i<nbVertexes ; ++i){
    mark[i] = false;
  }

  makeTreeDFS_aux(g, r, mark);
}

//==========================================================================
void Tree::makeTreeDFS_aux(Graph& g, int node, bool* mark){
  mark[node] = true;
  vector<int> neighbours = g.getNeighbours(node);
  for(unsigned i=0 ; i < neighbours.size() ; ++i){
    if(!(mark[neighbours[i]])){
      tree.addArc(node, neighbours[i]);
      makeTreeDFS_aux(g, neighbours[i], mark);
    }
  }
}

