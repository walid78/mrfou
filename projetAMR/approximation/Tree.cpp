#include "Tree.hpp"

Tree::Tree(int nodes):graph(nodes, ""){

}

Graph Tree::getGraph(void){
  return graph;
}

//Calculer un arbre sans feuille (surement virer Ã§a)
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

vector<int> Tree::vertexCover2() {
  vector<int> vertexCover();
  vector<int> destroyVertex();
  vertexCover2(vertexCover, destroyVertex);
}

//Pour la récursion
vector<int> Tree::vertexCover2(vector<int> vertexCover, vector<int> destroyVertex) {
  //Chercher une feuille v
  int leaf = findLeaf(destroyVertex);
  if(leaf == -1)
    return vertexCover;

  //Retenir dans la couverture le sommet u voisin du sommet v
  vector<int> neighboors = graph.getNeighbours(leaf);
  int vertex = neighboors[0];
  vertexCover.push_back(vertex);

  //Eliminer toutes les aretes incidentes à u
  //FAUT TROUVER LE TRUC MAGIQUE
  destroyVertex.push_back(vertex); //On rajoute dans la liste des
  //sommets détruits


  //Travailler avec la foret restante
  //FAIRE L'APPEL RECURSIF
  return vertexCover2(vertexCover, destroyVertex);
}

int Tree::findLeaf(vector<int> destroyVertex) { //Vérifier que les sommets sont toujours couvrable
  int length = graph.getNbVertexes();
  for(int i = 1; i < length; ++i) {
    if(graph.getNeighbours(i) == 1 && !(destroyVertex.at(i) > 0)) //On vérifie que i n'est pas dans les sommets détruits
      return i;
  }
  return -1;
}

//C'est l'algo glouton
vector<int> Tree::vertexCover3() {

}
