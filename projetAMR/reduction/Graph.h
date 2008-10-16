#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Graph {

public:
	Graph(int nodes);
	~Graph();
	void addEdges(int, int);
	vector<int> getNeighbours(int);

private:
	int nb_nodes;
	vector< vector<int> > graph;
};

#endif /* GRAPH_H */
