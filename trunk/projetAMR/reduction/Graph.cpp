#include "Graph.h"

Graph::Graph(int nodes){
	nb_nodes = nodes;
	//graph(vector<int>[nodes]);
	graph = new vector<int>[nodes];
	for(int i=0 ; i<nodes ; ++i)
	  graph[i] = new vector<int>;
}

Graph::~Graph(){
	
}

void Graph::addEdges(int originNode, int destNode)
{
	for(unsigned i=0 ; i<graph[originNode].size() ; ++i){
		if(graph[originNode][i] == destNode)
			return ;
	}
	
	graph[originNode].push_back(destNode);
	graph[destNode].push_back(originNode);
}

vector<int> Graph::getNeighbours(int originNode)
{
	return graph[originNode];
}
