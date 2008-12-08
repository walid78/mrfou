#include <cassert>
#include <iostream>

#include "Graph.hpp"

/** Constructeur : **/
//===========================================================================
Graph::Graph(const int nodes):nbVertexes(nodes){
  for(int i=0 ; i<nodes ; ++i)
    //Initialisation d'une liste pour chaque sommet i où la première case 
    //contient le nombre de sommets en relation avec i dans le graphe
    graph.push_back(vector<int>(1,0));
}

//===========================================================================
Graph::Graph(const Graph* g):nbVertexes(g->graph.size()){
  for(unsigned i=0 ; i<g->graph.size() ; ++i){
    graph.push_back(vector<int>());
    for(int j=0 ; j<=g->graph[i][0] ; ++j)
      graph[i].push_back(g->graph[i][j]);
  }
}

//===========================================================================
Graph::Graph(){
  Graph(0);
}

/** Destructeur : **/
//===========================================================================
Graph::~Graph(){
}

/** Fonctions membres : **/
//===========================================================================
void Graph::addEdge(const int originNode, const int destNode){
  addArc(originNode, destNode);
  addArc(destNode, originNode);
}

//==========================================================================
void Graph::addArc(int originNode, int destNode){
  for(int i=1 ; i<=graph[originNode][0] ; ++i)
    if(graph[originNode][i] == destNode)
      return ;
	
  graph[originNode].push_back(destNode);
  graph[originNode][0]++;
}

//===========================================================================
void Graph::removeEdge(const int originNode, const int destNode){
  removeArc(originNode, destNode);
  removeArc(destNode, originNode);
}

//==========================================================================
void Graph::removeArc(int originNode, int destNode){
  for(int i=1 ; i<=graph[originNode][0] ; ++i){
    if(graph[originNode][i] == destNode){
      graph[originNode].erase(graph[originNode].begin()+i);
      graph[originNode][0]--;
      return ;
    }
  }
}

//===========================================================================
int* Graph::getRandomArc(){
  if(getNbArcs() == 0)
    return NULL;

  for(int i=0 ; i<nbVertexes ; ++i){
    if(graph[i][0] != 0){
      int* arc = new int[2];
      arc[0] = i;
      arc[1] = graph[i][1];
      return arc;
    }
  }

  return NULL;
}

//===========================================================================
vector<int> Graph::getNeighbours(const int originNode){
  assert((unsigned)originNode>=0 && (unsigned)originNode<graph.size());

  vector<int> tmp(graph[originNode].begin()+1, graph[originNode].end());
  return tmp;
}

//===========================================================================
int Graph::getNbVertexes(void){
  return nbVertexes;
}

//===========================================================================
int Graph::getNbEdges(void){
  return getNbArcs()/2;
}

//===========================================================================
int Graph::getNbArcs(void){
  int nb_arcs = 0;
  
  for(unsigned i=0 ; i<graph.size() ; ++i)
    nb_arcs += graph[i][0];

  return nb_arcs;
}

//===========================================================================
int Graph::getNbNeighbours(int originNode){
  return graph[originNode][0];
}

//===========================================================================
bool* Graph::coverCourses(){
  bool* cover = new bool(nbVertexes);
  int* arc = new int[2];
  Graph copy = Graph(this);
  
  for(int i=0 ; i<nbVertexes ; ++i)
    cover[i] = false;
  
  while((arc = copy.getRandomArc()) != NULL){
    cover[arc[0]] = true;
    cover[arc[1]] = true;
    for(int j=0 ; j<nbVertexes ; ++j){
      copy.removeEdge(arc[0], j);
      copy.removeEdge(arc[1], j);
    }
  }

  return cover;
}


/** Opérateurs : **/
//===========================================================================
vector<int> Graph::operator[](const int originNode){
  return getNeighbours(originNode);
}

//===========================================================================
ostream& operator<<(ostream& o, const Graph& g){
  for(unsigned i=0 ; i<g.graph.size() ; ++i){
    o << i << ":";
    for(unsigned j=1 ; j<g.graph[i].size() ; ++j){
      o << " " << g.graph[i][j];
    }
    o << endl;
  }
	
  return o;
}
