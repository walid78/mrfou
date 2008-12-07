#ifndef TREE_HPP
#define TREE_HPP

#include "Graph.hpp"

using namespace std;

class Tree{
  
public:
  //===========================================================================
  /** Constructeur : **/
  Tree(Graph& g, int node); 

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
  void makeTreeDFS(Graph& g, int node);
 //  void makeTreeDFS_aux(const Graph& g, int node);
  
};

#endif
