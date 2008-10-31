#include "KCol.hpp"

#define N NB_COLORS

/** Constructeur : **/
//===========================================================================
KCol::KCol(Graph g, int nbColors):graph(g),
				  NB_COLORS(nbColors){
  nbVars = g.getNbVertexes()*3;
  nbClauses = 0;
}

/** Destructeur : **/
//===========================================================================
KCol::~KCol(){
	
}

/** Fonctions membres : **/
//===========================================================================
string KCol::generateCNFFormula(){
  stringstream CNFFormula;
  
  int nbVertexes = graph.getNbVertexes();
  
  /* Chaque sommet est colorié */
  CNFFormula << "c Chaque sommet est colorié" << endl;
  for(int i=0 ; i<nbVertexes ; ++i){
    for(int j=1 ; j<=N ; ++j)
      CNFFormula << (N*i+j) << " ";
    CNFFormula << "0" << endl;
    ++nbClauses;
  }

  /* Une seule couleur par sommet */
  CNFFormula << "c Une seule couleur par sommet" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=1 ; j<=N ; ++j)
      for(int k=1 ; k<=N ; ++k)
	if(j < k){
	  CNFFormula << "-" << (N*i+j) << " -" << (N*i+k) << " 0" << endl;
	  nbClauses++;
	  
	}


  /* Deux sommets qui se suivent n'ont pas la même couleur */
  CNFFormula << "c Deux sommets qui se suivent n'ont pas la même couleur" << endl;
  for(int i=0 ; i<nbVertexes ; ++i)
    for(int j=0 ; j<graph.getNbNeighbours(i) ; ++j)
      for(int k=1 ; k<=N ; ++k)
	if(i < graph[i][j]){
	  CNFFormula << "-" << (N*i+k) << " -" << (N*graph[i][j]+k) << " 0" << endl;
	  nbClauses++;
	}

  
  return CNFFormula.str();
}

//===========================================================================
string KCol::getSolution(){
  if(N >= graph.getNbVertexes()){
    cout << "Coloration évidente des sommets en prenant pour chacun" <<
      " une couleur différente" << endl;
    exit(1);
  }else{
    int maxDegre = graph.getMaxDegre();
    if(N < maxDegre){
      cout << "Le graphe n'admet pas de " << N << "-Coloration car le degré maximal"<<
	" d'un sommet du graphe est " << maxDegre << endl;
      exit(1);
    }
  }
  
//   stringstream answer;
//   MinisatBuilder mb(pathFile,
// 		    graph.getNbVertexes(),
// 		    nbClauses,
// 		    generateCNFFormula()
// 		    );

//   bool* varAssign = mb.solve();
//   int nbVertexes = graph.getNbVertexes();
      
//   if(varAssign == NULL)
//     answer << "Le graphe n'admet pas de " << N << "-Coloration.";
//   else{
//     answer << "Le graphe admet une " << N << "-Coloration." << endl <<
//       "Il suffit de considérer la coloration des sommets suivante :" << endl <<
//       "{ ";
    
//     for(int i=0 ; i<nbVertexes ; ++i){
//       for(int j=1 ; j<=N ; ++j){
// 	if(varAssign[N*i+j]){
// 	  answer << i << " -> C" << j << ", ";
// 	  if(((i%20) == 0) && (i!=0) && (i!=nbVertexes-1))
// 	    answer << endl;
// 	}
//       }
//     }

//     int size = answer.str().size();
//     answer.str()[size-2]= ' ';
//     answer.str()[size-1]= '}';
//   }

//   return answer.str();
  return generateCNFFormula();
}

//===========================================================================
ostream& operator<<(ostream& o, const KCol& ch){
  return o << ch.graph;
}
