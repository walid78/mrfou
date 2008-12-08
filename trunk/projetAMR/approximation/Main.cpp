#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Graph.hpp"
#include "Tree.hpp"

using namespace std;

/** Fonction usage **/
//===========================================================================
void
usage(void){
  cerr << "main <graphe> <algorithme souhaité>" << endl;
  cerr << "\t Algorithme possible :" << endl;
  cerr << "\t\t 1 : Algorithme récursif par parcoours en profondeur." << endl;
  cerr << "\t\t 2 : Algorithme de retrait des feuilles." << endl;
  cerr << "\t\t 3 : Algorithme utilisant le couplage maximal." << endl;
  exit(EXIT_FAILURE);
}

/** Fonction donnant la taille du graphe(nombre de sommets) **/
//===========================================================================

int
getNbVertexes(string path){
  ifstream file(path.c_str(), ios::in);  // on ouvre le fichier en lecture
  int max = -1;

  if(file){  // si l'ouverture a reussi
    string line, number = "";
    int current, length;

    while(getline(file, line)){  // tant que l'on peut mettre la ligne dans "line"
      length = line.length();
      for(int i = 0; i<length ; i++){
	switch (line[i]){
	case '-':
	  current = atoi(number.c_str());
	  if(current > max)
	    max = current;
	  number = "";
	  break;
	case ' ':
	  current = atoi(number.c_str());
	  if(current > max)
	    max = current;
	  number = "";
	  break;
	default:
	  number += line[i];
	}
      }
      //Ici on traite le cas du dernier numero de la ligne!
      current = atoi(number.c_str());
      if(current > max)
	max = current;
      number = "";
    }
  }
  else{  // sinon
    cerr << "Impossible d'ouvrir le fichier !" << endl;
    exit(0);
  }
  
  file.close();  // on ferme le fichier
  return max+1;
}
/**Fonction qui crée le graphe**/
//===========================================================================

Graph
readGraph(string path){
  int nbVertexes = getNbVertexes(path);
  Graph graph(nbVertexes);
  ifstream file(path.c_str(), ios::in);  // on ouvre le fichier en lecture
  
  if(file){  // si l'ouverture a reussi
    string line;
    
    while(getline(file, line)){  // tant que l'on peut mettre la ligne dans "line"
      int length = line.length();
      string number = "";
      int current, last=-1;
      
      for(int i = 0; i < length; i++){
	switch(line[i]){
	case '-':
	  current = atoi(number.c_str());
	  if(last >= 0)
	    graph.addEdge(last,current);
       	  last = current;
	  number = "";
	  break;
	case ' ':
	  current = atoi(number.c_str());
	  if(last != -1)//si on ne rentre pas dans le if le sommet n'a pas d'aretes.
	    graph.addEdge(last,current);
	  number = "";
	  last = -1;
	  break;
	default:
	  number += line[i];
	}
      }
      //Ici on traite le cas du dernier numero de la ligne!
      current = atoi(number.c_str());
      if(last != -1)
      	graph.addEdge(last,current);
      number = "";
      last = -1;
    }
  }
  else{  // sinon
    cerr << "Impossible d'ouvrir le fichier !" << endl;
    exit(0);
  }
  
  file.close();  // on ferme le fichier
  return graph;
}

//===========================================================================
int
main(int argc, char** argv){

  if(argc < 3)
    usage();

  Graph graph = readGraph(argv[1]);

  if(graph.getNbVertexes() == 0){
    cerr << "Erreur : Le graphe n'a pas de sommets." << endl;
    exit(0);
  }

  
//   cout << "Graphe avant supp 1-2:" << endl << graph << endl;
  
//   graph.removeEdge(1,2);
  
//   cout << "Graphe après supp 1-2:" << endl << graph << endl;

  
  /* Algo perso */
//   bool* cover = tree.coverTree();

  /* Algo Projet */
//   Tree tree = Tree(graph, 0);
//   cout << "Arbre :" << endl << tree << endl;
//   bool* cover = tree.coverProject();

  bool* cover;  
  Tree tree(graph, 0);
 
  switch (atoi(argv[2])){
  case 1:
    cover = tree.coverTree();
    break;
  case 2:
    cover = tree.coverProject();
    break;
  default:
    cover = graph.coverCourses();
  }

  /* Algo Cours */
  //  bool* cover = graph.coverCourses();  

  cout << "Couverture de sommet : ";
  for(int i=0 ; i<graph.getNbVertexes() ; ++i)
    //cout << cover[i] << " ";
    if(cover[i])
      cout << i << " ";
  cout << endl;
  delete[]cover;
  
  return EXIT_SUCCESS;
}
