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
  Graph(const int nb_nodes); 
  Graph(const Graph& g); 

  //===========================================================================
  /** Destructeur : **/
  ~Graph();
  
  //===========================================================================
  /** Fonctions membres : **/
  void addEdges(const int originNode, const int destNode);
  
  vector<int> getNeighbours(const int originNode);
  
  vector<int> operator[](const int originNode);
  
  int getNbVertexes(void);
  int getNbEdges(void);
  int getNbNeighbours(int originNode);

 private:
  vector< vector<int> > graph;
  int nbVertexes;

};

//===========================================================================
/** Opérateur : **/
ostream& operator<<(ostream& o, const Graph& g);

#endif /* GRAPH_H */
