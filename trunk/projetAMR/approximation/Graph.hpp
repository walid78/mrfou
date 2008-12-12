#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

using namespace std;

class Graph{
  
  friend ostream& operator<<(ostream& o, const Graph& g);
	
 public:
  //===========================================================================
  /** Constructeur : **/
  Graph(const int nb_nodes); 
  Graph(const Graph* g); 
  Graph();

  //===========================================================================
  /** Destructeur : **/
  ~Graph();
  
  //===========================================================================
  /** Fonctions membres : **/
  void addEdge(const int originNode, const int destNode);
  void addArc(const int originNode, const int destNode);
  void removeEdge(const int originNode, const int destNode);
  void removeArc(const int originNode, const int destNode);
 
  vector<int> getNeighbours(const int originNode);
  vector<int> operator[](const int originNode);
  
  int getNbVertexes(void);
  int getNbEdges(void);
  int getNbArcs(void);
  int getNbNeighbours(int originNode);
  
  bool* coverCourses();
  bool* coverCourses2();
  bool* coverProject();

 private:
  int* getOneArc();
  vector< vector<int> > graph;
  int nbVertexes;
};

//===========================================================================
/** Opérateur : **/
ostream& operator<<(ostream& o, const Graph& g);

#endif /* GRAPH_H */
