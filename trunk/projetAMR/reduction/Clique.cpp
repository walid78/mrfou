#include <iostream>
#include <sstream>
#include <vector>

#include "Clique.hpp"

/** Constructeur : **/
//===========================================================================
Clique::Clique(Graph g, int size):graph(g),
				  cliqueSize(size),
				  pathFile(g.getPathFile()){
  
  int nbVertexes = g.getNbVertexes();

  nbVars = 0;
  nbClauses = 0;

  // Remplissage du tableau des variables en mettant cliqueSize variables k par 
  // sommet pour exprimer le fait que le sommet est en k^ième position
  for(int i=0 ; i<nbVertexes ; ++i){
    vars.push_back(vector<int>(size, -1));
    for(int j=0 ; j<size ; ++j)
      vars[i][j] = ++nbVars;
  }
		
  cout << "Vars : "<< endl;
   for(int i=0 ; i<nbVertexes ; ++i){
     for(int j=0 ; j<cliqueSize ; ++j)
       cout << vars[i][j] << ", ";
     cout << endl;
   }
  
}

/** Destructeur : **/
//===========================================================================
Clique::~Clique(){
	
}

/** Fonctions membres : **/
//===========================================================================
string Clique::generateCNFFormula(){
  stringstream CNFFormula;
  
  int nbVertexes = graph.getNbVertexes();

  /* Chaque noeud est dans la clique <=>
     Au moins un noeud est le j^ième sommet de la clique */
  CNFFormula << "c Chaque noeud est dans la clique <=>" << endl;
  CNFFormula << "c Au moins un noeud est le j^ième sommet de la clique" << endl;
  for(int j=0 ; j<cliqueSize ; ++j){
    for(int i=0 ; i<nbVertexes ; ++i){
      CNFFormula << vars[i][j] << " ";
    }
    CNFFormula << "0" << endl;
    nbClauses++;
  }
 
  /* Un noeud a exactement une position dans la clique <=>
     Aucun noeud n'est le j^ième et le l^ième sommet de la clique */
  CNFFormula << "c Un noeud a exactement une position dans la clique <=>" << endl;
  CNFFormula << "c Aucun noeud n'est le j^ième et le k^ième sommet de la clique" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<cliqueSize ; ++j)
      for(int k=j+1 ; k<cliqueSize ; ++k){
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
	for(int j=0 ; j<cliqueSize ; ++j)
	  for(int k=0 ; k<cliqueSize ; ++k)
	    if(j != k){
	      CNFFormula << "-" << vars[i][j] << " -" << vars[i2][k] << " 0" << endl;
	      nbClauses++;
	    }
  }
   
  /* Deux sommets n'ont pas la même position dans la clique
   */
  CNFFormula << "c Deux sommets n'ont pas la même position dans la clique" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int i2=i+1; i2<nbVertexes ; ++i2)
      for(int j=0 ; j<cliqueSize ; ++j){
	CNFFormula << "-" << vars[i][j] << " -" << vars[i2][j] << " 0" << endl;
	nbClauses++;
      }
    
  CNFFormula << nbClauses;

  return CNFFormula.str();
}

//===========================================================================
string Clique::getSolution(){
  stringstream answer;
//   MinisatBuilder mb(pathFile,
// 		    graph.getNbVertexes(),
// 		    nbClauses,
// 		    generateCNFFormula()
// 		    );

//   bool* varAssign = mb.solve();
//   int* edge;
  
//   //solve renvoie -1 lorsque c'est non sat
//   if(varAssign == NULL)
//     return << "Le graphe n'admet pas de circuit Hamiltonien.";
//   else{
//     answer << "Le graphe admet un circuit Hamiltonien." << endl <<
//       "Il suffit de considérer l'ensemble d'arêtes suivant :" << endl <<
//       "{ ";
    
//     for(int i=0 ; i<nbVars ; ++i){
//       if((edge = getEdgeFromVar(i)) != NULL)
// 	answer << edge[0] << "-" << edge[1] << ", ";
//       else{
// 	cerr << "Problème dans le programme." << endl;
// 	exit(0);
//       }
//     }

//     int size = answer.str().size();
//     answer.str()[size-2]= ' ';
//     answer.str()[size-1]= '}';
//   }

  return answer.str();
}

//===========================================================================
ostream& operator<<(ostream& o, const Clique& ch){
  return o << ch.graph;
}
