#include <cassert>

#include "Graph.h"

/** Constructeur : **/
//===========================================================================
Graph::Graph(const int nodes){
	for(int i=0 ; i<nodes ; ++i)
	  graph.push_back(vector<int>());
}

/** Destructeur : **/
//===========================================================================
Graph::~Graph(){
	
}

/** Fonctions membres : **/
//===========================================================================
void Graph::addEdges(const int originNode, const int destNode)
{
	for(unsigned i=0 ; i<graph[originNode].size() ; ++i){
		if(graph[originNode][i] == destNode)
			return ;
	}
	
	graph[originNode].push_back(destNode);
	graph[destNode].push_back(originNode);
}

//===========================================================================
vector<int>& Graph::getNeighbours(const int originNode)
{
	return graph[originNode];
}

/** Opérateurs : **/
//===========================================================================
/*** Condamné, parait inutile
vector<int>& Graph::operator[](const int originNode){
  assert((unsigned)originNode>=0 && (unsigned)originNode<graph.size());
  return graph[originNode];
}
*/
ostream& operator<<(ostream& o, const Graph& g){
	for(unsigned i=0 ; i<g.graph.size() ; ++i){
		o << i << ": ";
		for(unsigned j=0 ; j<g.graph[i].size() ; ++j){
			o << " " << g.graph[i][j];
		}
		o << endl;
	}
	
	return o;
}


