#include "Graphe.h"

Graphe::Graphe(int nb_nodes){
	this.nb_nodes = nb_nodes;
	//graph(Vector<int>[nb_nodes]);
	graph = new Vector<int>[nb_nodes];
}

Graphe::~Graphe(){
	
}

void Graphe::addEdges(int originNode, int destNode)
{
	for(int i=0 ; i<graph[originNode].size() ; ++i){
		if(graph[originNode][i] == destNode)
			return ;
	}
	
	graph[originNode].push_back(destNode);
	graph[destNode].push_back(originNode);
}

Vector<int> Graphe::getNeighbours(int originNode)
{
	return graph[originNode];
}
