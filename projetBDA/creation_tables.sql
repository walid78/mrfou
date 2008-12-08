drop table Destination;
drop table Hotel;
drop table Classe-Hotel;
drop table Circuit;
drop table Assoc_Hotel_Circuit;
drop table Assoc_Dest_Circuit;
drop table Sejour;
drop table Assoc_Prix_Sejour_Prix;
drop table Vol;
drop table Client;
drop table Facturation;




create table Destination(ID_Dest integer,Nom_Destination varchar2,Pays varchar2);
create table Hotel(	ID_Hotel integer, ID_Dest integer,Nom_Hotel varchar2,Addresse varchar2,
					ID Classe integer, capac_S integer, capac_D integer) ;		
create table Classe_Hotel(ID_Classe integer, Prix_S integer, Prix_D integer) ;
create table Circuit(ID_Circuit integer,Nom_Circuit varchar2) ;
create table Assoc_Hotel_Circuit(ID_Hotel integer, ID_Circuit integer) ;
create table Assoc_Dest_Circuit(ID_Dest integer, ID_Circuit integer) ;
create table Sejour(ID_Sejour integer, Duree integer, Texte Description varchar2, Coeff float) ;					
create table Assoc_Prix_Sejour_Circuit(ID_Circuit integer, ID_Sejour integer, Prix float) ;
create table Vol(ID_Vol integer, ID_Dest integer, Prix_Enfant float, Prix_Adulte float) ;
create table Client(ID_Client integer,Addresse varchar2,Tel number, Nom varchar2,Prenom varchar2, Age integer, 
					Email varchar2,Classe sociale varchar2, ID Dest_Preferee integer, Investissement Moyen float) ;

create table Facturation(ID Facture integer, Date Facture timestamp, 
						Addresse Client varchar2, Tel number, Nom varchar2, Prenom varchar2, 
						Nom_Dest Varchar2, Pays Dest varchar2, 
						Nom_Hotel varchar2, Address_Hotel varchar2,Classe_Hotel integer, Prix_S integer, Prix_D integer,
						Nom circuit varchar2, Duree_sejour integer, Prix_Circuit float, 
						Prix_Vol_Enfant float,Prix_Vol_Adulte float, 
						Texte Description Sejour varchar2, Coeff_ Sejour float,
						Total_Vol float, Total_Hotel float, Total_Circuit float, Total_Facture float,
						Age integer, Classe_sociale varchar2, Dest_Pref varchar2, Invest_Moyen float ) ;
						
						
						
						