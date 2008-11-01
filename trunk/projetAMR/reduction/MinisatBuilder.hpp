#ifndef MINISATBUILDER_HPP
#define MINISATBUILDER_HPP

using namespace std;

class MinisatBuilder {
  
public:
  MinisatBuilder(char* inputPath, int nbVertexes, int nbClauses, string CNFFormula);
  bool* solve();

private:
  char* inputPath;
  char* outputPath;
  int nbVertexes;
  int nbClauses;
  string CNFFormula;
  bool* readFromMinisat();
  void writeToMinisat();
};

#endif
