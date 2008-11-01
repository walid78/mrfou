#ifndef MINISATBUILDER_HPP
#define MINISATBUILDER_HPP

using namespace std;

class MinisatBuilder {
  
public:
  MinisatBuilder(string inputPath, int nbVertexes, int nbClauses, string CNFFormula);
  bool* solve();

private:
  string fileName;
  int nbVertexes;
  int nbClauses;
  string CNFFormula;
  bool* readFromMinisat();
  void writeToMinisat();
};

#endif
