#include "CircuitHamiltonien.h"

/** Constructeur : **/
//===========================================================================
CircuitHamiltonien::CircuitHamiltonien(Graph g):graph(g){
  nbVars = 0;

  int nbVertexes = g.getNbVertexes();

  //Initialisation du tableau vars à -1
  for(int i=0 ; i<nbVertexes ; ++i)
    vars.push_back(vector<int>(nbVertexes, -1));
  
  //Remplissage du tableau des variables en mettant une variable par arc
  for(int i=0 ; i<nbVertexes ; ++i){
    //cout << "test" << i << " :" << g.getNbNeighbours(i) << endl;
    for(int j=0 ; j<g.getNbNeighbours(i) ; ++j){
      //cout << "aa : " << g[i][j] << endl;
      vars[i][g[i][j]] = ++nbVars;
    }
  }
  
}

/** Destructeur : **/
//===========================================================================
CircuitHamiltonien::~CircuitHamiltonien(){
	
}

/** Fonctions membres : **/
//===========================================================================
string CircuitHamiltonien::generateFormule(){
  stringstream formule;
  
  int nbVertexes = graph.getNbVertexes();

  /* Au moins un arc sortant */
  formule << "c Au moins un arc sortant" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      formule << vars[i][graph[i][j]] << " ";
    }
    formule << "0" << endl;
  }

  /* Pas deux arcs sortants */
  formule << "c Pas deux arcs sortants" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      for (int k=0 ; k<graph.getNbNeighbours(i); ++k)
	if(graph[i][j] < graph[i][k])
	  formule << "-" << vars[i][graph[i][j]] << " " << 
	    "-" << vars[i][graph[i][k]] << " 0" <<endl;

  /* Au moins un arc entrant */
  formule << "c Au moins un arc entrant" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      formule << vars[graph[i][j]][i] << " ";
    }
    formule << "0" << endl;
  }

  /* Pas deux arcs entrants */
  formule << "c Pas deux arcs entrants" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      for (int k=0 ; k<graph.getNbNeighbours(i); ++k)
	if(graph[i][j] < graph[i][k])
	  formule << "-" << vars[graph[i][j]][i] << " " << 
	    "-" << vars[graph[i][k]][i] << " 0" <<endl;

  /* Pas de double arcs */
  formule << "c Pas de double arcs" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      if(i<graph[i][j])
	formule << "-" << vars[i][graph[i][j]] << " " << 
	  "-" << vars[graph[i][j]][i] << " 0" << endl;

  return formule.str();
}

//===========================================================================
vector<bool> CircuitHamiltonien::getSolution(){
  return vector<bool>();
}

//===========================================================================
ostream& operator<<(ostream& o, const CircuitHamiltonien& ch){
  return o << ch.graph;
}
