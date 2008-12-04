#include "Tree.hpp"

Tree::Tree(int nodes):graph(nodes, ""){

}

Graph Tree::getGraph(void){
  return graph;
}

//Calculer un arbre sans feuille (surement virer ça)
Tree Tree::getTree(){
  vector<int> vertexCover;
  int cpt = 0;
  int length = graph.getNbVertexes();
  for(int i = 0; i < length; ++i) {
    if(!(graph.getNbNeighbours(i) == 1 && i != 0)) { //Zero est toujours
						  //la racine
      vertexCover[cpt++] = i;
    }
  }
}


vector<int> Tree::vertexCover1() {
  vector<int> vertexCover();
  int last = 0;
  int length = graph.getNbVertexes();
  
  for(int i = 1; i < length; ++i) {
    if((graph.getNbNeighbours(i) != 1) || (i == 0)) { //Zero est
						    //toujours la racine
      vertexCover[last++] = i;
    }
  }
  
  return vertexCover;
}

//Algo du cours à regarder (oui, je l'ai préter)
vector<int> Tree::vertexCover2() {
  //Chercher une feuille v
  int leaf = findLeaf();

  //Retenir dans la couverture le sommet u voisin du sommet v
  vector<int> neighboors = graph.getNeighbours(leaf);
  int vertex = neighboors[0];
  index = 0;
  vector<int> vertexCover[index++] = vertex;

  //Eliminer toutes les aretes incidentes � u
  //FAUT TROUVER LE TRUC MAGIQUE

  //Travailler avec la foret restante
  //FAIRE L'APPEL RECURSIF
}

int Tree::findLeaf() { //V�rifier que les sommets sont toujours couvrable
  int length = graph.getNbVertexes();
  for(int i = 1; i < length; ++i) {
    if(graph.getNeighbours(i) == 1)
      return i;
  }
}
