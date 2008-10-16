#include <Vector>

using namespace std;

class Graphe {

public:
	Graphe(int nb_nodes);
	~Graphe();
	int addVertex();
	void addEdges(int, int);
	int getNeighbour(int, int);
	Vector<int> getNeighbours(int);

private:
	Vector<int>[] graph;
	int nb_nodes
};
