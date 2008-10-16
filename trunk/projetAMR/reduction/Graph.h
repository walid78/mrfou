#include <Vector>

using namespace std;

class Graph {

public:
	Graph(int nb_nodes);
	~Graph();
	void addEdges(int, int);
	Vector<int> getNeighbours(int);

private:
	Vector<int>[] graph;
	int nb_nodes;
};
