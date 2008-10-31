#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Graph.h"
#include "MinisatBuilder.hpp"

MinisatBuilder::MinisatBuilder(char* inputPath,
			       int nbVertexes,
			       int nbClauses,
			       string CNFFormula){
  cout << "Construction de MinisatBuilder";
}

bool* MinisatBuilder::readFromMinisat(){
//   ifstream file(path, ios::in);
//   bool* tab(/*valeur à récupérer grace à writetoMinisat*/)
  
//   if(file){

//     string line;
//     int SATFind = 0;
    
//     while(getline(file, line)){
//       if(SATFind == 0 && line.find("SAT") >= 0)
// 	SATFind = 1;
      
//       if(SATFind == 1){
// 	int length = line.length();
// 	string number = "";
	
// 	for(int i = 0; i < length - 1; i++){
// 	  if(line[i] == ' '){
// 	    int valeur = atoi(number);
// 	    number = "";
// 	    //Traitement des variables
// 	    tab[valeur] = (valeur > 0);
// 	  }
// 	  else{
// 	    if(line[i] = '0' && i = length - 1) //Ceci ne doit en
// 						//theorie ne jamais arriver
// 	      break;
// 	    else
// 	      number += line[i];
// 	  }
// 	}	
//       }
//     }
//   }
//   file.close();
//   return tab;
  return NULL;
}

void MinisatBuilder::writeToMinisat(){ //Surement des arguments a
//   //ajouter ?
//   //A revoir puisqu'on récupère déjà un ostream donc juste écrire dans le fichier
//   //penser à récupérer le nombre de variable
//   ofstream file(path, ios::out);
  
//   if(file){
//     string s;
//     s = "c "; //Si on veut mettre un commentaire
//     file.write(s, s.length);

//     s = "p cnf "; //Plus les autres trucs que je ne sais pas
//     file.write(s, s.length);

//     //Faire une boucle qui se termine par un 0. Je ne sais pas non
//     //plus quoi mettre dedans
//   }
//   file.close();
}

//Rajouter une fonction askMinisat qui prend en parametre une string et 
//retourne tab booléen qui ecrit dans minisat, lance minisat et récupère le solution

bool* solve(){
  return NULL;
}
