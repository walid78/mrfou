#include "Tree.hpp"

// const enum e = {WHITE, GREY, BLACK};

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

/*vector<int> Tree::vertexCover2() {
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
  }*/

vector<int> Tree::vertexCover2() {
  vector<int> vertexCover = new vector();
  depthCover(vertexCover);
  return vertexCover;
}

void Tree::depthCover(vector<int> *vertexCover){
  int nbNodes = getNbVertexes();

  // INITIALISATION
  e[] color = new e[nbNodes];
  for(int i = 0; i < nbNodes; ++i)
    color[i] = e.WHITE;

  for(int i = 0; i < nbNodes; ++i)
    if(color[i] == e.WHITE){
      //g.addEdges(u, i);
      depthCover(i, vertexCover, color);
    }
}

bool Tree::depthCover(int u, vector<int> *vertexCover, e[] color){
  color[u] = e.GREY;

  int nbNodes = getNbNeighbours(u);
  if(nbNodes == 1){
    //Faire en sorte de marquer le père
    //vector<int> nodes = graph.getNeighboors(u);
    //int node = nodes[0];
    //Ne pas marquer le sommet node
    return false;
  }

  //C'est faux car on marque des trucs faux, 
  //Je pense qu'il faut vérifier la présence du sommet
  //dans le vecteur vertexCover
  //JE CROIS QUE C'EST CORRIGE
  if(depthCover(u, g, color) && !(vertexCover.at(u) > 0)){
    //Ne pas marquer u
    return false;
  } else {
    //Marquer u
    vertexCover.push_back(u);
    return true;
  }

  /*for(int i = 0; i < nbNodes; ++i)
    if(color[u[i] == e.WHITE){

	g.addEdges(u, graph.getNeighboors()[i]);
	depthCover(i, g, color);
      }

      color[u] = e.BLACK;*/
}


//C'est l'algo glouton
vector<int> Tree::vertexCover3() {
  
}
