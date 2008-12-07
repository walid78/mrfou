#include <cassert>
#include <iostream>

#include "Graph.hpp"

/** Constructeur : **/
//===========================================================================
Graph::Graph(const int nodes, string path):nbVertexes(nodes),
					   pathFile(path){
  for(int i=0 ; i<nodes ; ++i)
    //Initialisation d'une liste pour chaque sommet i où la première case 
    //contient le nombre de sommets en relation avec i dans le graphe
    graph.push_back(vector<int>(1,0));
}

//===========================================================================
Graph::Graph(const Graph& g):nbVertexes(g.graph.size()),
			     pathFile(g.pathFile){
  for(unsigned i=0 ; i<g.graph.size() ; ++i){
    graph.push_back(vector<int>());
    for(int j=0 ; j<=g.graph[i][0] ; ++j)
      graph[i].push_back(g.graph[i][j]);
  }
}

Graph::Graph(){
  Graph(0,"");
}

/** Destructeur : **/
//===========================================================================
Graph::~Graph(){
}

/** Fonctions membres : **/
//===========================================================================
void Graph::addEdges(const int originNode, const int destNode){
  for(int i=1 ; i<=graph[originNode][0] ; ++i)
    if(graph[originNode][i] == destNode)
      return ;
	
  graph[originNode].push_back(destNode);
  graph[originNode][0]++;
  graph[destNode].push_back(originNode);
  graph[destNode][0]++;
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
  int nb_edges = 0;
  
  for(unsigned i=0 ; i<graph.size() ; ++i)
    nb_edges += graph[i][0];

  return nb_edges/2;
}

//===========================================================================
int Graph::getNbNeighbours(int originNode){
  return graph[originNode][0];
}

//===========================================================================
string Graph::getPathFile(void){
  return pathFile;
}

//===========================================================================
int Graph::getMaxDegre(void){
  int max=0;
  for(int i=0 ; i<nbVertexes ; ++i)
    if(graph[i][0] == nbVertexes-1)
      return nbVertexes-1;
    else if(graph[i][0] > max){
      max=graph[i][0];
    }
  
  return max;
}

//===========================================================================
Graph Graph::complementary(void){
  bool isNotInGraph[nbVertexes];

  Graph comp(nbVertexes, pathFile);
  
  for(int i=0 ; i<nbVertexes ; ++i){

    for(int j=0 ; j<nbVertexes ; ++j)
      isNotInGraph[j] = true;
    isNotInGraph[i] = false;
    
    for(int j=1 ; j<=graph[i][0] ; ++j)
      isNotInGraph[graph[i][j]] = false;

    for(int j=0 ; j<nbVertexes ; ++j)
      if(isNotInGraph[j])
	comp.addEdges(i, j);
  }
  return comp;
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
