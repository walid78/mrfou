#include <wait.h>
#include <unistd.h>
#include <signal.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Graph.h"
#include "MinisatBuilder.hpp"

MinisatBuilder::MinisatBuilder(char* inputPath,
			       int nbVertexes,
			       int nbClauses,
			       string CNFFormula):inputPath(inputPath), 
						  nbVertexes(nbVertexes), 
						  nbClauses(nbClauses), 
						  CNFFormula(CNFFormula){
  ;
}

bool* MinisatBuilder::readFromMinisat(){
  
  char* path = "";
  for(int i = 0; inputPath[i] != '\0' && inputPath[i] != '.'; ++i){
    char* tmp = inputPath[i]; //ça ne marche pas, problème de type
    strcat(path, tmp);
  } //strncat aurait peut-être était mieux, à voir
  
  strcat(path, ".gout");
  outputPath = path;
  
  ifstream file(path, ios::in);
  bool* tab(nbVertexes);
    
    if(file){
      
      string line;
      int SATFind = 0;
      
      while(getline(file, line)){
	if(SATFind == 0 && line.find("SAT") >= 0)
	  SATFind = 1;
	
	if(SATFind == 1){
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
	      if(line[i] = '0' && i = length - 1) //Ceci ne doit en
		//theorie ne jamais arriver
 	      break;
	      else
		number += line[i];
	    }
	  }	
	}
      }
    }
  file.close();
  return tab;
}

void MinisatBuilder::writeToMinisat(){

  ofstream file(inputPath, ios::out);
  
  if(file){
    string s;
    s = "c "; //Si on veut mettre un commentaire
    s += "\n";
    file.write(s, s.length);
    
    s = "p cnf ";
    s += nbVertexes;
    s += " ";
    s += nbClauses;
    s += "\n";
    file.write(s, s.length);
    
    file.write(CNFFormula, CNFFormula.length);
  }
  file.close();
}

bool* MinisatBuilder::solve(){
  //a faire, c'est lui qui fait tout, alors au boulot
  //Penser aussi à regarder le execvp
  writeToMinisat();
  
  //faire le execvp, ET RAJOUTER LES BONNES LIB
  if(fork()){
    char* args[2];
    args[0] = inputPath;
    args[1] = outputPath;
    execvp("./minisat", args);
  }
  wait(2); //TODO Trouver un temps plus adéquate
  
  return readFromMinisat();
}
