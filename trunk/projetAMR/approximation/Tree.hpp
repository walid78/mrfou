#ifndef TREE_HPP
#define TREE_HPP

#include "Graph.hpp"

class Tree{

public:
  /*  Constructeur  */
  Tree(int node);

  Graph getGraph(void);

private:
  Graph graph; //delegate
}

#endif //TREE_HPP
