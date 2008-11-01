#include <iostream>
#include <sstream>
#include <vector>

#include "CircuitHamiltonien.hpp"
#include "MinisatBuilder.hpp"

/** Constructeur : **/
//===========================================================================
CircuitHamiltonien::CircuitHamiltonien(Graph g):graph(g),
						pathFile(g.getPathFile()){
  int nbVertexes = g.getNbVertexes();

  nbVars = 0;
  nbClauses = 0;

  //Initialisation du tableau vars à -1
  for(int i=0 ; i<nbVertexes ; ++i)
    vars.push_back(vector<int>(nbVertexes, -1));
  
  //Remplissage du tableau des variables en mettant une variable par arc
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=0 ; j<g.getNbNeighbours(i) ; ++j){
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
string CircuitHamiltonien::generateCNFFormula(){
  stringstream CNFFormula;
  
  int nbVertexes = graph.getNbVertexes();

  /* Au moins un arc sortant */
  CNFFormula << "c Au moins un arc sortant" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      CNFFormula << vars[i][graph[i][j]] << " ";
    }
    CNFFormula << "0" << endl;
    nbClauses++;
  }

  /* Pas deux arcs sortants */
  CNFFormula << "c Pas deux arcs sortants" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      for (int k=0 ; k<graph.getNbNeighbours(i); ++k)
	if(graph[i][j] < graph[i][k]){
	  CNFFormula << "-" << vars[i][graph[i][j]] << " " << 
	    "-" << vars[i][graph[i][k]] << " 0" <<endl;
	  nbClauses++;
	}

  /* Au moins un arc entrant */
  CNFFormula << "c Au moins un arc entrant" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      CNFFormula << vars[graph[i][j]][i] << " ";
    }
    CNFFormula << "0" << endl;
    nbClauses++;
  }

  /* Pas deux arcs entrants */
  CNFFormula << "c Pas deux arcs entrants" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      for (int k=0 ; k<graph.getNbNeighbours(i); ++k)
	if(graph[i][j] < graph[i][k]){
	  CNFFormula << "-" << vars[graph[i][j]][i] << " " << 
	    "-" << vars[graph[i][k]][i] << " 0" <<endl;
	  nbClauses++;
	}
  
  /* Pas de double arcs */
  CNFFormula << "c Pas de double arcs" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      if(i<graph[i][j]){
	CNFFormula << "-" << vars[i][graph[i][j]] << " " << 
	  "-" << vars[graph[i][j]][i] << " 0" << endl;
	nbClauses++;
      }
  
  return CNFFormula.str();
}

//===========================================================================
int* CircuitHamiltonien::getEdgeFromVar(int var){
  int* edge = new int[2];
  for(int i=0 ; i<nbVars ; ++i)
    for(int j=0 ; j<nbVars ; ++j)
      if(vars[i][j] == var){
	edge[0] = i;
	edge[1] = j;
	return edge;
      }

  return NULL;
}

//===========================================================================
string CircuitHamiltonien::getSolution(){
  stringstream answer;
  MinisatBuilder mb(pathFile,
		    graph.getNbVertexes(),
		    nbClauses,
		    generateCNFFormula()
		    );

   bool* varAssign = mb.solve();
  
  //cout << varAssign[0];
  /*
  for(unsigned i=0 ; i<sizeof(varAssign)/sizeof(bool) ; ++i)
    cout << i << ":" << (varAssign[i]?"true":"false") << ", ";
  cout << endl;
  */
  int* edge;
  
  cout << "TESTTSJKMHFMKJDSQHFDLKJHLDJKHLSFKJ" << endl;
  //solve renvoie -1 lorsque c'est non sat
  if(varAssign == NULL)
    answer << "Le graphe n'admet pas de circuit Hamiltonien.";
  else{
    answer << "Le graphe admet un circuit Hamiltonien." << endl <<
      "Il suffit de considérer l'ensemble d'arêtes suivant :" << endl <<
      "{ ";
    
    for(int i=0 ; i<nbVars ; ++i){
      if(varAssign[i]){
	if((edge = getEdgeFromVar(i)) != NULL)
	  answer << edge[0] << "-" << edge[1] << ", ";
	else{
	  cerr << "Problème dans le programme." << endl;
	  exit(0);
	}
      }
    }

    int size = answer.str().size();
    answer.str()[size-2]= ' ';
    answer.str()[size-1]= '}';
  }

  delete edge;
  delete varAssign;
  return answer.str();
  //return generateCNFFormula();
}

//===========================================================================
ostream& operator<<(ostream& o, const CircuitHamiltonien& ch){
  return o << ch.graph;
}
