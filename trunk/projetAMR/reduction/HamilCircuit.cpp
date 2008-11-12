#include <iostream>
#include <sstream>
#include <vector>

#include "HamilCircuit.hpp"
#include "MinisatBuilder.hpp"

/** Constructeur : **/
//===========================================================================
HamilCircuit::HamilCircuit(Graph g):graph(g),
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
}

/** Destructeur : **/
//===========================================================================
HamilCircuit::~HamilCircuit(){
	
}

/** Fonctions membres : **/
//===========================================================================
string HamilCircuit::generateCNFFormula(){
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

  /* Le dernier sommet du circuit doit aussi être le premier */
  CNFFormula << "c Le dernier sommet du circuit doit aussi être le premier" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    CNFFormula << "-" << vars[i][0] << " " << vars[i][nbVertexes] << " 0" << endl;
    CNFFormula << vars[i][0] << " -" << vars[i][nbVertexes] << " 0" << endl;
  }

  return CNFFormula.str();
}

//===========================================================================
int HamilCircuit::easyCases(){

  int nbEdges = graph.getNbEdges();
  int nbVertexes = graph.getNbVertexes();  
  int NB_MAX_EDGES = nbVertexes * (nbVertexes-1) / 2;

  /* Cas faciles */

  //Le nombre d'arêtes du graphe est strictement inférieur au nombre de sommets
  if(nbEdges < graph.getNbVertexes())
    return 1;

  //Le graphe est un graphe complet => Toujours vrai
  else if(nbEdges == NB_MAX_EDGES)
    return 2;

  else 
    return 0;
}

//===========================================================================
string HamilCircuit::getSolution(){
  stringstream answer;
  int easyCase = easyCases();

  /* Cas faciles 
   * 
   * 1) Le nombre d'arêtes du graphe est strictement inférieur au nombre de sommets
   * 2) Le graphe est un graphe complet => Toujours vrai
   *
   */

  switch(easyCase){
    
  case 0:
    break;

  case 1:
    // 1) Le nombre d'arêtes du graphe est strictement inférieur au nombre de sommets
    answer << "Le graphe n'admet pas de circuit Hamiltonien car il y a moins " <<
      "d'arêtes que de sommets.";
    break;

  case 2:
    // 2) Le graphe est un graphe complet => Toujours vrai
    answer << "Le graphe admet un circuit Hamiltonien évident car c'est un graphe " <<
      "complet. Il suffit de prendre une arête sortante pour chaque sommet qui mène " << 
      "à un sommet non déjà visité et finir par le sommet de départ.";
    break;

  default:
    cerr << "Résultat inattendu" << endl;
    exit(0);
  }
    
  if((easyCase > 0) && (easyCase < 3))
    return answer.str();

 /* Calcul */
  MinisatBuilder mb(pathFile,
		    nbVars,
		    nbClauses,
		    generateCNFFormula()
		    );
  
  string s;
  bool* varAssign = mb.solve();
  int nbVertexes = graph.getNbVertexes();  

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

  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const HamilCircuit& ch){
  return o << ch.graph;
}
