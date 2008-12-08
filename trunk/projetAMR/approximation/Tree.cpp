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
//===========================================================================
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

//===========================================================================
bool* Tree::coverTree(){
  bool* cover = new bool(nbVertexes);

  for(int i=0 ; i<nbVertexes ; ++i)
    cover[i] = false;

  coverTree_aux(root, cover);

  return cover;
}

//===========================================================================
bool Tree::coverTree_aux(int node, bool* cover){
  bool markFather = true;
  int nbNeighbours = tree.getNbNeighbours(node);

  if(nbNeighbours == 0)
    //Papa doit être marqué
    return true;

//   vector<int> neighbours = tree.getNeighbours(node);
//   for(unsigned i=0 ; i < neighbours.size() ; ++i){
//     if(coverTree_aux(neighbours[i], cover)){
//       cover[node] = true;
//       markFather = false;
//     }
//   }
//   return markFather;

  for(int i=0 ; i < nbNeighbours ; ++i){
    if(coverTree_aux(tree[node][i], cover)){
      cover[node] = true;
      markFather = false;
    }
  }
  return markFather;

}

//===========================================================================
bool* Tree::coverProject(){
  bool* cover = new bool(nbVertexes);

  for(int i=0 ; i<nbVertexes ; ++i)
    cover[i] = true;

  coverProject_aux(root, cover);

  return cover;
}

//===========================================================================
void Tree::coverProject_aux(int node, bool* cover){
  int nbNeighbours = tree.getNbNeighbours(node);

  if(nbNeighbours == 0){
    //Papa doit être marqué
    cover[node] = false;
    return ;
  }else{
    for(int i=0 ; i < nbNeighbours ; ++i)
      coverProject_aux(tree[node][i], cover);
  }
}


/** Opérateurs : **/
//===========================================================================
ostream& operator<<(ostream& o, const Tree& t){
  return o << t.tree;
}

