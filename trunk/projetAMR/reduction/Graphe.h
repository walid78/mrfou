
class Graphe {

public:
	Graphe();
	~Graphe();
	int addVertex();
	void addEdges(int, int);
	int getNeighbour(int, int);
	Vector<int> getNeighbours(int);
	Vector<int> getEdges(int);
	Vector<int[2]> getEdges();
	Vector<int> getVertex();
	
private:
	Vector<int> vertex;
	Vector<int[2]> edges;
};
