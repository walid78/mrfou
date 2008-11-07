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
    vars.push_back(vector<int>(nbVertexes+1, -1));
    for(int j=0 ; j<nbVertexes+1 ; ++j)
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


  /* Chaque noeud est dans le circuit <=>
     Au moins un noeud est le jième sommet du circuit */
  CNFFormula << "c Chaque noeud est dans le circuit <=>" << endl;
  CNFFormula << "c Au moins un noeud est le jième sommet du circuit" << endl;
  for(int j=0 ; j<nbVertexes+1 ; ++j){
      for(int i=0 ; i<nbVertexes ; ++i){
      CNFFormula << vars[i][j] << " ";
    }
    CNFFormula << "0" << endl;
    nbClauses++;
  }
 
  /* Un noeud a exactement une position dans le circuit sauf pour le premier/dernier <=>
     Aucun noeud n'est le jième et le kième sommet du circuit (!(j==0 && k==nbVertexes)) */
  CNFFormula << "c Un noeud a exactement une position dans le circuit " << 
    "sauf pour le premier/dernier <=>" << endl;
  CNFFormula << "c Aucun noeud n'est le jième et le kième sommet du circuit " << 
    "(!(j==0 && k==nbVertexes))" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<nbVertexes-1 ; ++j)
      for(int k=j+1 ; k<nbVertexes+1 ; ++k){
	if(!(j==0 && k==nbVertexes)){
	  CNFFormula << "-" << vars[i][j] << " -" << vars[i][k] << " 0" << endl;
	  nbClauses++;
	}
      }

  /* Deux sommets non voisins ne peuvent pas se suivre dans le circuit */
  CNFFormula << "c Deux sommets non voisins ne peuvent pas se suivre " << 
    "dans le circuit" << endl;

  for(int i=0 ; i<nbVertexes ; ++i){
    vector<bool> noEdge(nbVertexes, true);
    noEdge[i] = false;
    // On enlève les sommets reliés à i
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j){
      noEdge[graph[i][j]] = false;
    }

    for(int i2=0 ; i2<nbVertexes ; ++i2)
      if(noEdge[i2])
	for(int j=0 ; j<nbVertexes ; ++j){
	  CNFFormula << "-" << vars[i][j] << " -" << vars[i2][j+1] << " 0" << endl;
	  nbClauses++;
	}
  }
   
  /* Deux sommets n'ont pas la même position dans le circuit */
  CNFFormula << "c Deux sommets n'ont pas la même position dans le circuit" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<nbVertexes+1 ; ++j)
      for(int i2=i+1; i2<nbVertexes ; ++i2){
	CNFFormula << "-" << vars[i][j] << " -" << vars[i2][j] << " 0" << endl;
	nbClauses++;
      }

  /* Le dernier sommet doit etre le premier du circuit*/
  CNFFormula << "c Le dernier sommet du circuit doit être le premier de la" << 
    "couverture" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    //     for(int j=1 ; j<nbVertexes ; ++j){
    // 	CNFFormula << "-" << vars[i][j] << " -" << vars[i][nbVertexes] << " 0" << endl;
    // 	nbClauses++;
    //     }
    CNFFormula << "-" << vars[i][0] << " " << vars[i][nbVertexes] << " 0" << endl;
    CNFFormula << vars[i][0] << " -" << vars[i][nbVertexes] << " 0" << endl;
  }

  return CNFFormula.str();
}

//===========================================================================
string CircuitHamiltonien::getSolution(){
  stringstream answer;
  int nbVertexes = graph.getNbVertexes();  
  /* Cas facile */
  if(graph.getNbEdges() < graph.getNbVertexes()){
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

  //solve renvoie NULL lorsque c'est non sat
  if(varAssign == NULL){
    answer << "Le graphe n'admet pas de circuit Hamiltonien.";
    s = answer.str();
  }else{

    answer << "Le graphe admet un circuit Hamiltonien." << 
      endl << "Il suffit de considérer les arêtes suivantes :" << 
      endl << "{ ";
    
    int pos[nbVertexes+1];
    
    for(int i=0 ; i<nbVars ; ++i)
      if(varAssign[i])
	pos[i%(nbVertexes+1)] = i/(nbVertexes+1);

    for(int i=0 ; i<nbVertexes ; ++i)
      answer << pos[i] << "-" << pos[i+1] << ", ";
    
    
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
