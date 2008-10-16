#include "Graphe.h"

Graphe::Graphe()
{

}

Graphe::~Graphe()
{

}

int Graphe::addVertex()
{
	vertex.add();
	return vertex.last(); //PAS SURE DE CA
}

void Graphe::addEdges(int originVertex, int destVertex)
{
	edges.add({originVertex, destVertex});
}

int Graphe::getNeighbour(int vertex, int edge)
{
	//En gros retourner le voisin de vertex part l'arrête edge
	return 0;
}

Vector<int> Graphe::getNeighbours(int v)
{
	int lenght = edges.size();
	Vector vect();
	
	for(int i = 0; i < length; ++i)
		if(vertex[i][0] == v || vertex[i][1] == v)
			vect.add(i);
	
	return vect;
}

Vector<int> Graphe::getEdges(int vertex)
{
	int lenght = edges.size();
	Vector vect();
	
	for(int i = 0; i < length; ++i)
		if(vertex[i][0] == v || vertex[i][1] == v)
			vect.add(i);
	
	return vect; //PAS CA DU TOUT
}

Vector<int[2]> Graphe::getEdges()
{
	return edges;
}

Vector<int> Graphe::getVertex()
{
	return vertex;
}
	
	