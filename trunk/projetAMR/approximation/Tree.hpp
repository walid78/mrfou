#ifndef TREE_HPP
#define TREE_HPP

#include "Graph.hpp"

class Tree{

public:
  /*  Constructeur  */
  Tree(int node);

  Graph getGraph(void);

  //Sous quelle forme doit être la couverture ???

  //PARTIE UN
  //Couverture à calculer

  //PARTIE DEUX
  Tree getTree();  //Il nous faut récupérer un arbre sans feuille
  //Calcule de couverture
  vector<int> vertexCover1();
  //Regarder le cours pour le couplage maximal
  vector<int> vertexCover2();

private:
  Graph graph; //delegate
}

#endif //TREE_HPP
 
