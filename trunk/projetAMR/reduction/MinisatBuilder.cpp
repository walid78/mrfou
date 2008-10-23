#include <iostream>
#include <fstream>
#include <string>

#include "Graph.h"
#include "MinisatBuilder.hpp"

MinisatBuilder::readFromMinisat(char* path){
  ifstream file(path, ios::in);
  
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
	    int valeur = atoi(number);
	    number = "";
	    //TRAITER CETTE VALEUR, JE NE SAIS PAS COMMENT
	  }
	  else{
	    if(line[i] = '0' && i = length - 1) //Ceci ne doit en
						//theorie ne jamais arriver
	      break;
	    else
	      number += line[i];
	  }
	}
	
	
    //NE PAS LIRE CA, C'EST POURRI MAIS JE LE GARDE. BEN
    /*string line;
      int pFind = 0; //Savoir si p a deja etait lu
      
      while(getline(file, line)){
      if(!(line.find("c") == 1)){ //Si la ligne n'est pas un commentaire
      if(pFind == 0 && line.find("p") == 1){ //Ligne d'indication
      int pos = line.find("cnf") + 2;
      string = "";
      int length = line.length() + pos;*/
      }
    }
  }
  file.close();
}
MinisatBuilder::writeToMinisat(char* path){ //Surement des arguments a
					    //ajouter ?
  ofstream file(path, ios::out);
  
  if(file){
    string s;
    s = "c "; //Si on veut mettre un commentaire
    file.write(s, s.length);

    s = "p cnf "; //Plus les autres trucs que je ne sais pas
    file.write(s, s.length);

    //Faire une boucle qui se termine par un 0. Je ne sais pas non
    //plus quoi mettre dedans
  }
  file.close();
}
