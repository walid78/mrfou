#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

using namespace std;

class Graph{
  
  friend ostream& operator<<(ostream& o, const Graph& g);
	
 public:
  //===========================================================================
  /** Constructeur : **/
  Graph(const int nb_nodes, char* path); 
  Graph(const Graph& g); 

  //===========================================================================
  /** Destructeur : **/
  ~Graph();
  
  //===========================================================================
  /** Fonctions membres : **/
  void addEdges(const int originNode, const int destNode);
  
  vector<int> getNeighbours(const int originNode);
  
  vector<int> operator[](const int originNode);
  
  int getMaxDegre(void);
  int getNbVertexes(void);
  int getNbEdges(void);
  int getNbNeighbours(int originNode);
  char* getPathFile(void);
  
 private:
  vector< vector<int> > graph;
  int nbVertexes;
  char* pathFile;

};

//===========================================================================
/** Opérateur : **/
ostream& operator<<(ostream& o, const Graph& g);

#endif /* GRAPH_H */
