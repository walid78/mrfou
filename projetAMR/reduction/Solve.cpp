#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

int getNbVertex(char* path){
  ifstream file(path, ios::in);  // on ouvre le fichier en lecture
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
	  break;
	}
      }
    }
  }
  else  // sinon
    cerr << "Impossible d'ouvrir le fichier !" << endl;

  file.close();  // on ferme le fichier
  return max;
}

Graph
readGraph(char* path){
  int nbVertex = getNbVertex(path);
  Graph graph(nbVertex);
  ifstream file(path, ios::in);  // on ouvre le fichier en lecture

  if(file){  // si l'ouverture a reussi
    string line;

    while(getline(file, line)){  // tant que l'on peut mettre la ligne dans "line"
      int length = line.length();
      string number = "";
      int current, last=-1;

      for(int i = 0; i < length; i++){
	if(line[i] == '-'){
	  current = atoi(number.c_str());
	  if(last >= 0){
	    graph.addEdges(last,current);
	  }
	  last = current;
	  number = "";
	}
	else if(line[i] == ' '){
	  current = atoi(number.c_str());
	  graph.addEdges(last,current);
	  number = "";
	  last = -1;
	}
	else{
	  number += line[i];
	}
      }
    }
  }
  else  // sinon
    cerr << "Impossible d'ouvrir le fichier !" << endl;

  file.close();  // on ferme le fichier
  return graph;
}

int
main(int argc, char** argv){
  Graph graph = readGraph(argv[1]);
  cout << "test reussi";
  return 0;
}
