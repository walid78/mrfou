#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

#include "Tree.hpp"

using namespace std;

class Graph{
  
  friend ostream& operator<<(ostream& o, const Graph& g);
	
 public:
  //===========================================================================
  /** Constructeur : **/
  Graph(const int nb_nodes, string path); 
  Graph(const Graph& g); 

  //===========================================================================
  /** Destructeur : **/
  ~Graph();
  
  //===========================================================================
  /** Fonctions membres : **/
  void addEdges(const int originNode, const int destNode);
  
  vector<int> getNeighbours(const int originNode);
  
  vector<int> operator[](const int originNode);
  
  Graph complementary(void);
  int getMaxDegre(void);
  int getNbVertexes(void);
  int getNbEdges(void);
  int getNbNeighbours(int originNode);
  string getPathFile(void);

  Tree createTree(void);
  
 private:
  vector< vector<int> > graph;
  int nbVertexes;
  string pathFile;

  void depthCover(int u, Graph g, e[] color);
};

//===========================================================================
/** Opérateur : **/
ostream& operator<<(ostream& o, const Graph& g);

#endif /* GRAPH_H */
