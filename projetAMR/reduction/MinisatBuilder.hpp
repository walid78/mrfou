#ifndef MINISATBUILDER_HPP
#define MINISATBUILDER_HPP

using namespace std;

class MinisatBuilder {
  
public:
  MinisatBuilder(string inputPath, int nbVars, int nbClauses, string CNFFormula);
  bool* solve();

private:
  string fileName;
  int nbVars;
  int nbClauses;
  string CNFFormula;
  bool* readFromMinisat();
  void writeToMinisat();
};

#endif
