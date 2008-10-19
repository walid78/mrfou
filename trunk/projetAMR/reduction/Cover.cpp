#include "Cover.h"

bool isCover(Graph graph, vector<int> vertexs){

  int nbVertex = graph.getNbVertex();
  bool isCov;
  for(int j=0; j<nbVertex; ++j){
    vector<int> temp = graph.getNeighbours(j);
    int nbNeighbours = temp.size();
    for(int k=0; k<nbNeighbours; ++k){
      for(unsigned i=0; i<vertexs.size();++i){
	if( j!=vertexs[i] && temp[k]!=vertexs[i])
	  isCov=false;
	else
	  isCov=true;
      }
      if(!isCov)
	return false;
    }
  }
  return isCov;
}
