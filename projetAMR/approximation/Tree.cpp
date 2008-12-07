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
  bool* mark = new bool(nbVertexes);
  bool* cover = new bool(nbVertexes);

  for(int i=0 ; i<nbVertexes ; ++i){
    cover[i] = false;
    mark[i] = false;
  }

  coverTree_aux(root, mark, cover);

  return cover;
}

//===========================================================================
bool Tree::coverTree_aux(int node, bool* mark, bool* cover){
  bool markFather = true;

  mark[node] = true;
  
  if(tree.getNbNeighbours(node) == 0)
    //Papa doit être marqué
    return true;

  vector<int> neighbours = tree.getNeighbours(node);
  for(unsigned i=0 ; i < neighbours.size() ; ++i){
    cout << "BBBBB :: " << node << endl;
    if(!(mark[neighbours[i]])){
      if(coverTree_aux(neighbours[i], mark, cover)){
	cout << "AAAAA :: " << node << endl;
	
	cover[node] = true;
	markFather = false;
      }
    }
  }
  return markFather;
}


/** Opérateurs : **/
//===========================================================================
ostream& operator<<(ostream& o, const Tree& t){
  return o << t.tree;
}

