#include "Tree.hpp"

Tree::Tree(int nodes):graph(nodes, ""){

}

Graph Tree::getGraph(void){
  return graph;
}

//Calculer un arbre sans feuille (surement virer ça)
Tree Tree::getTree(){
  int length = graph.getNbVertexes();
  for(int i = 0; i < length; ++i) {
    if(graph.getNbNeighbours() == 1 /*&& racine == i*/) {
      //Retirer le sommet i de la couverture
    }
  }
}


vector<int> Tree::vertexCover1() {
  vector<int> vector();
  int last = 0;
  int length = graph.getNbVertexes();
  
  for(int i = 0; i < length; ++i) {
    if(graph.getNbNeighbours() == 1 /*&& racine == i*/) { //vérifier qu'on ne prends pas la racine !!!!
      vector[last++] = i;
    }
  }
  
  return vector;
}

//Algo du cours à regarder (oui, je l'ai préter
vector<int> Tree::vertexCover2() {

}
