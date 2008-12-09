drop table Destination;
drop table Hotel;
drop table Classe_Hotel;
drop table Circuit;
drop table Assoc_Hotel_Circuit;
drop table Assoc_Dest_Circuit;
drop table Sejour;
drop table Assoc_Prix_Sejour_Prix;
drop table Vol;
drop table Client;
drop table Facturation;



/* Création des tables */

create table Destination(ID_Dest integer,Nom_Destination varchar2,Pays varchar2);

create table Hotel(ID_Hotel integer, ID_Dest integer,Nom_Hotel varchar2,Addresse varchar2,ID_Classe integer, capac_S integer, capac_D integer) ;		

create table Classe_Hotel(ID_Classe integer, Prix_S float, Prix_D float) ;

create table Circuit(ID_Circuit integer,Nom_Circuit varchar2) ;

create table Assoc_Hotel_Circuit(ID_Hotel integer, ID_Circuit integer) ;

create table Assoc_Dest_Circuit(ID_Dest integer, ID_Circuit integer) ;

create table Sejour(ID_Sejour integer, Duree integer, Description varchar2, Coeff float) ;					

create table Assoc_Prix_Sejour_Circuit(ID_Circuit integer, ID_Sejour integer, Prix float) ;

create table Vol(ID_Vol integer, ID_Dest integer, Prix_Enfant float, Prix_Adulte float) ;

create table Client(ID_Client integer,Addresse varchar2,Tel number(10), Nom varchar2,Prenom varchar2, Age integer, Email varchar2,Classe_sociale varchar2, ID Dest_Preferee integer, Investissement_Moyen float) ;

create table Facturation(ID Facture integer, Date Facture timestamp, Addresse Client varchar2, Tel number(10), Nom varchar2, Prenom varchar2, Nom_Dest varchar2, Pays Dest varchar2, Nom_Hotel varchar2, Address_Hotel varchar2, Classe_Hotel integer, Prix_S float, Prix_D float, Nom_circuit varchar2, Duree_sejour integer, Prix_Circuit float, Prix_Vol_Enfant float,Prix_Vol_Adulte float, Description_Sejour varchar2, Coeff_Sejour float, Total_Vol float, Total_Hotel float, Total_Circuit float, Total_Facture float, Age integer, Classe_sociale varchar2, Dest_Pref varchar2, Invest_Moyen float ) ;
						
						
						
/* Remplissage de la table Destination */
INSERT INTO Destination VALUES(1,'Bordeaux','France');				
INSERT INTO Destination VALUES(2,'Valence','France');
INSERT INTO Destination VALUES(3,'Valence','Espagne');
INSERT INTO Destination VALUES(4,'Barcelone','Espagne');
INSERT INTO Destination VALUES(5,'Paris','France');

/* Remplissage de la table Hotel */
INSERT INTO Hotel VALUES (1, 1,'California','Rue de LA',4, 20, 10);
INSERT INTO Hotel VALUES (2, 4,'L hôte','Rue du serveur',2, 10, 10);
INSERT INTO Hotel VALUES (3, 3,'Hérie','Reu de la blague',5, 40, 35);

/* Remplissage de la table Classe_Hotel */
INSERT INTO Classe_Hotel VALUES (1, 10.00, 20.00) ;
INSERT INTO Classe_Hotel VALUES (2, 25.00, 45.00) ;
INSERT INTO Classe_Hotel VALUES (3, 30.00, 60.00) ;
INSERT INTO Classe_Hotel VALUES (4, 45.00, 80.00) ;
INSERT INTO Classe_Hotel VALUES (5, 60.00, 80.00) ;

/* Remplissage de la table Circuit */

INSERT INTO Circuit VALUES (1,'Mont_Fuji') ;
INSERT INTO Circuit VALUES (2,'Catalogne') ;
INSERT INTO Circuit VALUES (3,'Monaco') ;
INSERT INTO Circuit VALUES (4,'Hockenheim') ;

/* Remplissage de la table Assoc_Hotel_Circuit */

INSERT INTO Assoc_Hotel_Circuit VALUES (1,2);
INSERT INTO Assoc_Hotel_Circuit VALUES (1,2);
INSERT INTO Assoc_Hotel_Circuit VALUES (3,3);
INSERT INTO Assoc_Hotel_Circuit VALUES (4,1);

/* Remplissage de la table Assoc_Dest_Circuit */

INSERT INTO Assoc_Hotel_Circuit VALUES (1,4);
INSERT INTO Assoc_Hotel_Circuit VALUES (2,3);
INSERT INTO Assoc_Hotel_Circuit VALUES (2,1);

/* Remplissage de la table Séjour */

INSERT INTO Séjour VALUES (1,10,'Cool',1) ;
INSERT INTO Séjour VALUES (2,10,'Funny',1) ;
INSERT INTO Séjour VALUES (3,21,'Chiant',0.5) ;
INSERT INTO Séjour VALUES (4,21,'Fatiguant',0.4) ;

/* Remplissage de la table Assoc_Prix_Séjour_Circuit */

INSERT INTO Assoc_Prix_Séjour_Circuit VALUES (1,2,100.00) ;
INSERT INTO Assoc_Prix_Séjour_Circuit VALUES (2,2,115.00) ;
INSERT INTO Assoc_Prix_Séjour_Circuit VALUES (2,4,50.00) ;
INSERT INTO Assoc_Prix_Séjour_Circuit VALUES (4,3,65.00) ;

/* Remplissage de la table Vol */

INSERT INTO Vol VALUES (1,1,10.00,20.00) ;
INSERT INTO Vol VALUES (2,1,15.00,40.00) ;
INSERT INTO Vol VALUES (3,2,9.00,21.00) ;
INSERT INTO Vol VALUES (4,4,12.00,24.00) ;

/* Remplissage de la table Client */

INSERT INTO Client VALUES (1,'Rue de la plage', 0556654558, 'Burneau', 'Bruno', 26, 'Burneau@laposte.net', 'Etudiant', 'Toronto', 400.00);
INSERT INTO Client VALUES (2,'Rue du geek', 0679473302, 'Fou', 'Fabien', 23, 'Mrfou@hotmail.fr', 'Salarié', 'Grenobles', 215.00);
INSERT INTO Client VALUES (3,'Rue de la soif', 0557348875, 'Durand', 'Patrick', 52, 'Aucun', 'Salarié', 'Tokyo', 1000.00);

/* Remplissage de la table Facturation */
/* N'y a t-il pas un moyen plus malin de le faire? */
/* Noter que timestamp est soit le nombre de seconde depuis le 01 janv 1970 à 00H00M00S ou bien soit un binaire qui permet de synchroniser des tables pour faire des mises à jour */

INSERT INTO Facturation Values (1, 2007-01-27, 'Rue de la plage', 0556654558, 'Burneau' ,'Bruno', 'Bruxelles', 'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 'Fatiguant', 0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Toronto', 400.00) ;


