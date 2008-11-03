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
     Au moins un noeud est le jième sommet de la clique */
  CNFFormula << "c Chaque noeud est dans la clique <=>" << endl;
  CNFFormula << "c Au moins un noeud est le jième sommet de la clique" << endl;
  for(int j=0 ; j<cliqueSize ; ++j){
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
    
  return CNFFormula.str();
}

//===========================================================================
bool* Clique::transmitSolution(){
  MinisatBuilder mb(pathFile,
		    nbVars,
		    nbClauses,
		    generateCNFFormula()
		    );
  return mb.solve();
}

//===========================================================================
int Clique::getMinNbEdgesInClique(int size){
  if(size <= 1)
    return 0;
  else 
    return getMinNbEdgesInClique(size-1) + (size-1);
}

//===========================================================================
int Clique::getMinNbEdgesWhichObligesClique(int nbVert){
  //int nbVertexes = graph.getNbVertexes();
  if(cliqueSize == nbVert)
    return getMinNbEdgesInClique(nbVert);
  else 
    return getMinNbEdgesWhichObligesClique(nbVert-1) + (nbVert + cliqueSize - 3) / 2;
}


//===========================================================================
string Clique::getSolution(){

  stringstream answer;
  int nbVertexes = graph.getNbVertexes();

  /* Cas faciles */

  //Clique de taille < 1 => Entrée incorrecte
  if(cliqueSize < 1){
    answer << "Le nombre entré n'est pas une taille de clique correcte.";
    return answer.str();
  }

  //Clique de taille 1 => 1 sommet
  else if(cliqueSize == 1){
    answer << "Une clique de taille 1 ne nécessite que d'avoir un sommet.";
    return answer.str();
  }

  //Clique de taille 2 => 1 arête
  else if(cliqueSize == 2){
    if(graph.getNbEdges() > 0){
      answer << "Le graphe admet une clique de taille 2, il suffit de choisir " << 
	"n'importe quelle arête.";
      return answer.str();
    }else{
      answer << "Le graphe n'admet pas de clique de taille 2, car il n'a pas d'arête.";
      return answer.str();
    }
  }

  //Clique de taille supérieure au nombre de sommets => impossible
  else if(cliqueSize > nbVertexes){
    answer << "Le graphe n'admet pas de clique de taille " << cliqueSize <<
      " car le nombre de sommets du graphe (" << nbVertexes << ") est " <<
      "inférieur à cette taille (" << cliqueSize << ").";
    return answer.str();
  }else{
    int nbEdges = graph.getNbEdges();
    
    //A partir d'un certain nombre d'arêtes par rapport à un nombre de sommets,
    //Il est obligatoire d'obtenir une clique d'une certaine taille
    if(getMinNbEdgesWhichObligesClique(nbVertexes) <= graph.getNbEdges()){
      answer << "Le graphe admet forcément une clique de taille " << cliqueSize <<
	" car le nombre d'arêtes du graphe (" << nbEdges << ") oblige le graphe " <<
	"à contenir une clique de taille (" << cliqueSize << ").";
      return answer.str();
      
    }else{
      int minNbEdgesInClique = getMinNbEdgesInClique(cliqueSize);
      
      //Il faut un nombre d'arêtes minimum pour former une clique d'une certaine taille
      //Exemple : clique 3 -> 3 arêtes min, clique 4 -> 6 arêtes min.
      if(nbEdges < minNbEdgesInClique){
	answer << "Le graphe n'admet pas de clique de taille " << cliqueSize <<
	  " car le nombre d'arêtes du graphe (" << nbEdges << ") est " <<
	  "insuffisant (il en faudrait " << minNbEdgesInClique << ") pour former " <<
	  "une clique de taille " << cliqueSize << ".";
	return answer.str();
      }
    }
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
    answer << "Le graphe n'admet pas de clique de taille " << cliqueSize << ".";
    s = answer.str();
  }else{
    answer << "Le graphe admet une clique de taille " << cliqueSize << "." << 
      endl << "Il suffit de considérer les sommets suivants :" << 
      endl << "{ ";
    
    for(int i=0 ; i<nbVars ; ++i){
      if(varAssign[i])
	answer << (i/cliqueSize) << ", ";
    }
    
    s = answer.str();
    int size = s.size();
    s[size-2]= ' ';
    s[size-1]= '}';
  }
  
  return s;
}

//===========================================================================
ostream& operator<<(ostream& o, const Clique& ch){
  return o << ch.graph;
}
