#ifndef MINISATBUILDER_HPP
#define MINISATBUILDER_HPP

using namespace std;

class MinisatBuilder {
  
   /*-*-*-*-* PUBLIC *-*-*-*-*/
public:
  //===========================================================================
  /** Constructeur : **/
  MinisatBuilder(string inputPath, int nbVars, int nbClauses, string CNFFormula);

  //===========================================================================
  /** Fonctions membres : **/
  bool* solve();

  /*-*-*-*-* PRIVATE *-*-*-*-*/
private:
  //===========================================================================
  /** Attributs **/
  string fileName;
  int nbVars;
  int nbClauses;
  string CNFFormula;

  //===========================================================================
  /** Fonctions membres **/
  bool* readFromMinisat();
  void writeToMinisat();
};

#endif
