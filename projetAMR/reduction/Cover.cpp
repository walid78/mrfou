#include "Cover.hpp"

bool isCover(Graph graph, vector<int> vertexes){

  int nbVertexes = graph.getNbVertexes();
  bool isCov;
  for(int j=0; j<nbVertexes; ++j){
    vector<int> temp = graph.getNeighbours(j);
    int nbNeighbours = temp.size();
    for(int k=0; k<nbNeighbours; ++k){
      for(unsigned i=0; i<vertexes.size();++i){
	if( j!=vertexes[i] && temp[k]!=vertexes[i])
	  isCov=false;
	else{
	  isCov=true;
	  break;
	}
      }
      if(!isCov)
	return false;
    }
  }
  return isCov;
}
