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

  // Remplissage du tableau des variables en mettant cliqueSize variables k par 
  // sommet pour exprimer le fait que le sommet est en k^ième position
  for(int i=0 ; i<nbVertexes ; ++i){
    vars.push_back(vector<int>(nbVertexes, -1));
    for(int j=0 ; j<nbVertexes ; ++j)
      vars[i][j] = ++nbVars;
  }
  
  // //Initialisation du tableau vars à -1
//   for(int i=0 ; i<nbVertexes ; ++i)
//     vars.push_back(vector<int>(nbVertexes, -1));
  
//   //Remplissage du tableau des variables en mettant une variable par arc
//   for(int i=0 ; i<nbVertexes ; ++i){
//     for(int j=0 ; j<g.getNbNeighbours(i) ; ++j){
//       vars[i][g[i][j]] = ++nbVars;
//     }
//   }
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


  /* Chaque noeud est dans la clique <=>
     Au moins un noeud est le jième sommet de la clique */
  CNFFormula << "c Chaque noeud est dans la clique <=>" << endl;
  CNFFormula << "c Au moins un noeud est le jième sommet de la clique" << endl;
  for(int j=0 ; j<nbVertexes ; ++j){
    for(int i=0 ; i<nbVertexes ; ++i){
      CNFFormula << vars[i][j] << " ";
    }
    CNFFormula << "0" << endl;
    nbClauses++;
  }
 
  /* Un noeud a exactement une position dans la clique <=>
     Aucun noeud n'est le jième et le lième sommet de la clique */
  CNFFormula << "c Un noeud a exactement une position dans la clique <=>" << endl;
  CNFFormula << "c Aucun noeud n'est le jième et le kième sommet de la clique" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<nbVertexes ; ++j)
      for(int k=j+1 ; k<nbVertexes ; ++k){
	CNFFormula << "-" << vars[i][j] << " -" << vars[i][k] << " 0" << endl;
	nbClauses++;
      }

  /* Deux sommets non voisins ne peuvent pas être ensemble dans la clique */
  CNFFormula << "c Deux sommets non voisins ne peuvent pas être ensemble " << 
    "dans la clique" << endl;

  for(int i=0 ; i<nbVertexes ; ++i){
    vector<bool> noEdge(nbVertexes, true);
    noEdge[i] = false;
    // On enlève les sommets reliés à i
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      noEdge[graph[i][j]] = false;
    }

    for(int i2=i+1 ; i2<nbVertexes ; ++i2)
      if(noEdge[i2])
		  for(int j=0 ; j<nbVertexes ; ++j){
			 //			 for(int k=0 ; k<cliqueSize ; ++k)
			 //if(j != k){
			 CNFFormula << "-" << vars[i][j] << " -" << vars[i2][j+1] << " 0" << endl;
			 nbClauses++;
		  }
  }
   
  /* Deux sommets n'ont pas la même position dans la clique
   */
  CNFFormula << "c Deux sommets n'ont pas la même position dans la clique" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int i2=i+1; i2<nbVertexes ; ++i2)
      for(int j=0 ; j<nbVertexes ; ++j){
		  CNFFormula << "-" << vars[i][j] << " -" << vars[i2][j] << " 0" << endl;
		  nbClauses++;
      }

//   /* Au moins un arc sortant */
//   CNFFormula << "c Au moins un arc sortant" << endl;
//   for(int i=0 ; i<nbVertexes ; ++i){
//     for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
//       CNFFormula << vars[i][graph[i][j]] << " ";
//     }
//     CNFFormula << "0" << endl;
//     nbClauses++;
//   }

//   /* Pas deux arcs sortants */
//   CNFFormula << "c Pas deux arcs sortants" << endl;
//   for(int i=0 ; i<nbVertexes ; ++i)
//     for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
//       for (int k=0 ; k<graph.getNbNeighbours(i); ++k)
// 	if(graph[i][j] < graph[i][k]){
// 	  CNFFormula << "-" << vars[i][graph[i][j]] << " " << 
// 	    "-" << vars[i][graph[i][k]] << " 0" <<endl;
// 	  nbClauses++;
// 	}

//   /* Au moins un arc entrant */
//   CNFFormula << "c Au moins un arc entrant" << endl;
//   for(int i=0 ; i<nbVertexes ; ++i){
//     for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
//       CNFFormula << vars[graph[i][j]][i] << " ";
//     }
//     CNFFormula << "0" << endl;
//     nbClauses++;
//   }

//   /* Pas deux arcs entrants */
//   CNFFormula << "c Pas deux arcs entrants" << endl;
//   for(int i=0 ; i<nbVertexes ; ++i)
//     for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
//       for (int k=0 ; k<graph.getNbNeighbours(i); ++k)
// 	if(graph[i][j] < graph[i][k]){
// 	  CNFFormula << "-" << vars[graph[i][j]][i] << " " << 
// 	    "-" << vars[graph[i][k]][i] << " 0" <<endl;
// 	  nbClauses++;
// 	}
  
//   /* Pas de double arcs */
//   CNFFormula << "c Pas de double arcs" << endl;
//   for(int i=0 ; i<nbVertexes ; ++i)
//     for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
//       if(i<graph[i][j]){
// 	CNFFormula << "-" << vars[i][graph[i][j]] << " " << 
// 	  "-" << vars[graph[i][j]][i] << " 0" << endl;
// 	nbClauses++;
//       }
  
  return CNFFormula.str();
}

//===========================================================================
int* CircuitHamiltonien::getEdgeFromVar(int var){
  int* edge = new int[2];
  int nbVertexes = graph.getNbVertexes();

  // cout << var << endl;
  
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<nbVertexes ; ++j)
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
  int nbVertexes = graph.getNbVertexes();  
  /* Cas facile */
  if(graph.getNbEdges() <= graph.getNbVertexes()){
    answer << "Le graphe n'admet pas de circuit Hamiltonien car il y a moins " <<
      "d'arêtes que de sommets.";
    return answer.str();
  }

  /* Calcul */
  MinisatBuilder mb(pathFile,
		    nbVars,
		    nbClauses,
		    generateCNFFormula()
		    );
  
  string s;
  bool* varAssign = mb.solve();
  
	 for(int i=0 ; i < nbVertexes ; ++i){
		for(int j=0 ; j < nbVertexes ; ++j)
		  cout <<vars[i][j]<<" | ";
		cout << endl;
	 }

	 exit(1);
  //solve renvoie NULL lorsque c'est non sat
  if(varAssign == NULL){
    answer << "Le graphe n'admet pas de circuit Hamiltonien.";
    s = answer.str();
  }else{

    answer << "Le graphe admet un circuit Hamiltonien." << 

      endl << "Il suffit de considérer les arêtes suivantes :" << 
      endl << "{ ";
    
    for(int i=0 ; i<nbVars ; ++i){
      if(varAssign[i])
		  answer << (i/nbVertexes) << ", ";
    }
    
    s = answer.str();
    int size = s.size();
    s[size-2]= ' ';
    s[size-1]= '}';
  }

 //  bool* varAssign = mb.solve();
//   int* edge;
  
//   //solve renvoie NULL lorsque c'est non sat
//   if(varAssign == NULL)
//     return "Le graphe n'admet pas de circuit Hamiltonien.";
//   else{
//     answer << "Le graphe admet un circuit Hamiltonien." << endl <<
//       "Il suffit de considérer l'ensemble d'arêtes suivant :" << endl <<
//       "{ ";
    
//     for(int i=0 ; i<nbVars ; ++i){
//       if(varAssign[i]){
// 	if((edge = getEdgeFromVar(i+1)) != NULL)
// 	  answer << edge[0] << "-" << edge[1] << ", ";
// 	else{
// 	  cerr << "Problème dans le programme." << endl;
// 	  exit(0);
// 	}
//       }
//     }

//     s = answer.str();
//     int size = s.size();
//     s[size-2]= ' ';
//     s[size-1]= '}';
//   }

  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const CircuitHamiltonien& ch){
  return o << ch.graph;
}
