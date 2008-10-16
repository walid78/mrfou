#include <Vector>

using namespace std;

class Graphe {

public:
	Graphe(int nb_nodes);
	~Graphe();
	void addEdges(int, int);
	Vector<int> getNeighbours(int);

private:
	Vector<int>[] graph;
	int nb_nodes;
};
