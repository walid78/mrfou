#include <wait.h>
#include <unistd.h>
#include <signal.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Graph.hpp"
#include "MinisatBuilder.hpp"

MinisatBuilder::MinisatBuilder(string inputPath,
			       int nbVertexes,
			       int nbClauses,
			       string CNFFormula):nbVertexes(nbVertexes), 
						  nbClauses(nbClauses), 
						  CNFFormula(CNFFormula){
  fileName = inputPath.substr(0,inputPath.size()-4);
  cout << fileName;
}

bool* MinisatBuilder::readFromMinisat(){
  
  ifstream file((fileName+".sol").c_str(), ios::in);
  
  bool* tab = new bool[nbVertexes];
  if(file){
    string line;
    
    // On récupère la première ligne
    getline(file, line);
    
    int unsatFind = line.find("UNSAT");
    if(unsatFind >= 0 && unsatFind < line.length())
      return NULL;
    
      if(line.find("SAT") < 0){
	cerr << "ERROR";
	exit(0);
      }
      
      while(getline(file, line)){
	int length = line.length();
	string number = "";
	
	for(int i = 0; i < length - 1; i++){
	  if(line[i] == ' '){
	    int valeur = atoi(number.c_str());
	    number = "";
	    //Traitement des variables
	    tab[valeur] = (valeur > 0);
	  }
	  else{
	    if(line[i] == '0' && i == length - 1) //Ceci ne doit en
	      //theorie ne jamais arriver
	      break;
	    else
	      number += line[i];
	  }
	}	
      }
    }

    file.close();
    return tab;
}

void MinisatBuilder::writeToMinisat(){

  ofstream file((fileName+".sat").c_str(), ios::out);

  if(file){
    string s;
    s = "c "; //Si on veut mettre un commentaire
    s += "\n";
    file << s;
    
    file << "p cnf " << nbVertexes << " " << nbClauses << endl;
    
    file << CNFFormula;
  }
  file.close();
}

bool* MinisatBuilder::solve(){

  writeToMinisat();
  
  if (system(NULL)) puts ("Ok");
  else exit (1);
  
  system(("./minisat/simp/minisat " + fileName + ".sat " + fileName + ".sol").c_str());

  bool* tab = readFromMinisat();

  return tab;
}
