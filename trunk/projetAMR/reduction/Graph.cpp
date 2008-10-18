#include <cassert>

#include "Graph.h"

/** Constructeur : **/
//===========================================================================
Graph::Graph(const int nodes){
	for(int i=0 ; i<nodes ; ++i)
		//Initialisation d'une liste pour chaque sommet i où la première case 
		//contient le nombre de sommets en relation avec i dans le graphe
	  graph.push_back(vector<int>(1,0));
}

/** Destructeur : **/
//===========================================================================
Graph::~Graph(){
	
}

/** Fonctions membres : **/
//===========================================================================
void Graph::addEdges(const int originNode, const int destNode)
{
	for(unsigned i=1 ; i<graph[originNode].size() ; ++i){
		if(graph[originNode][i] == destNode)
			return ;
	}
	
	graph[originNode].push_back(destNode);
	graph[originNode][0]++;
	graph[destNode].push_back(originNode);
	graph[destNode][0]++;
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
