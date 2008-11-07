#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Graph.hpp"
#include "Clique.hpp"
#include "Cover.hpp"
#include "CircuitHamiltonien.hpp"
#include "KCol.hpp"
#include "VertexCover.hpp"
#include "IndepSet.hpp"

using namespace std;

void
usage(void){
  cerr << "Usage : ./solve <fichier_du_graphe> <numéro_du_problème> [paramètres]" << endl;
  cerr << "\tProblème 1 : k-coloriabilité" << endl;
  cerr << "\t\tParamètre obligatoire : k" << endl;
  cerr << "\tProblème 2 : Circuit Hamiltonien" << endl;
  cerr << "\tProblème 3 : Couverture de sommet" << endl;
  cerr << "\t\tParamètre obligatoire : taille_de_la_couverture" << endl;
  cerr << "\tProblème 4 : Clique" << endl;
  cerr << "\t\tParamètre obligatoire : taille_de_la_clique" << endl;
  cerr << "\tProblème 5 : Ensemble indépendant" << endl;
  cerr << "\t\tParamètre obligatoire : taille_de_l_ensemble" << endl;
  exit(EXIT_FAILURE);
}

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

Graph
readGraph(string path){
  int nbVertex = getNbVertexes(path);
  Graph graph(nbVertex, path);
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
	    graph.addEdges(last,current);
       	  last = current;
	  number = "";
	  break;
	case ' ':
	  current = atoi(number.c_str());
	  if(last != -1)
	    graph.addEdges(last,current);
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
      	graph.addEdges(last,current);
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

int
main(int argc, char** argv){

  if(argc < 3)
    usage();

  Graph graph = readGraph(argv[1]);

  if(graph.getNbVertexes() == 0){
    cerr << "Erreur : Le graphe n'a pas de sommets.";
    exit(0);
  }
    
  //  cout << "Graph :" << endl << graph << endl; //JE VIENS DE COMMENTER
  //   vector<int> cover;
  //   cover.push_back(0);
  //   cover.push_back(2);
  
  //   bool test = isCover(graph, cover);
  //   cout <<"TEST COVER " << (test?"OK":"KO") <<endl;

  //   cout << graph.getNbVertexes() << " " << graph.getNbEdges() << endl;

  // Rajoute une arete
  //   graph.addEdges(3,4);

  //  cout << graph.getNbVertexes() << " " << graph.getNbEdges() << endl;
  
  int problemSelect = atoi(argv[2]);
  switch (problemSelect){
  case 1:
    {
      if(argc >= 4){
	KCol c(graph,atoi(argv[3]));
	cout << c.getSolution() << endl;
      }else
	usage();
      break;
    }

  case 2:
    {
      CircuitHamiltonien ch(graph);
      cout << ch.getSolution() << endl;
      break;
    }

  case 3:
    {
      if(argc > 3){
	VertexCover vc(graph, atoi(argv[3]));
	cout << vc.getSolution() << endl;
      }else
	usage();
      break;
    }

  case 4:
    {
      if(argc > 3){
	Clique c(graph, atoi(argv[3]));
	cout << c.getSolution() << endl;
      }else
	usage();
      break;
    }
  case 5:
    {
      if(argc > 3){
	IndepSet is(graph, atoi(argv[3]));
	cout << is.getSolution() << endl;
      }else
	usage();
      break;
    }
  default :
    {
      cerr << "Le numéro du problème est compris entre 1 et 5";
      usage();
      break; //Ne sert à rien mais je le mets
    }
  }

  //   cout << "Graph : " << endl << graph << endl;

//   cout << "Comp : " << endl << graph.complementary() << endl;
  //exit(1);
  return 1;
}