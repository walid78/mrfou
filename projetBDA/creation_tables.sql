drop table Destination;
drop table Hotel;
drop table Classe_Hotel;
drop table Circuit;
drop table Assoc_Hotel_Circuit;
drop table Assoc_Dest_Circuit;
drop table Sejour;
drop table Assoc_Prix_Sejour_Circuit;
drop table Vol;
drop table Client;
drop table Facturation;





create table Destination(ID_Dest number,Nom_Destination varchar2(20),Pays varchar2(20));

create table Hotel(ID_Hotel number, ID_Dest number,Nom_Hotel varchar2(20),Addresse varchar2(50),
					ID_Classe number, capac_S number, capac_D number) ;		

create table Classe_Hotel(ID_Classe number, Prix_S float, Prix_D float) ;

create table Circuit(ID_Circuit number,Nom_Circuit varchar2(20)) ;

create table Assoc_Hotel_Circuit(ID_Hotel number, ID_Circuit number) ;

create table Assoc_Dest_Circuit(ID_Dest number, ID_Circuit number) ;

create table Sejour(ID_Sejour number, Duree number, Description varchar2(50), Coeff float) ;					

create table Assoc_Prix_Sejour_Circuit(ID_Circuit number, ID_Sejour number, Prix float) ;

create table Vol(ID_Vol number, ID_Dest number, Prix_Enfant float, Prix_Adulte float) ;

create table Client(ID_Client number,Addresse varchar2(50),Tel varchar2(10), Nom varchar2(20),Prenom varchar2(20), Age number, 
					Email varchar2(30),Classe_sociale varchar2(20), ID_Dest_Preferee number, Investissement_Moyen float) ;

create table Facturation(ID_Facture number, Date_Facture timestamp, 
						Addresse_Client varchar2(50), Tel varchar2(10), Nom varchar2(20), Prenom varchar2(20), 
						Nom_Dest varchar2(20), Pays_Dest varchar2(20), 
						Nom_Hotel varchar2(20), Address_Hotel varchar2(50),Classe_Hotel number, Prix_S float, Prix_D float,
						Nom_circuit varchar2(20), Duree_sejour number, Prix_Circuit float, 
						Prix_Vol_Enfant float,Prix_Vol_Adulte float, 
						Description_Sejour varchar2(50), Coeff_Sejour float,
						Total_Vol float, Total_Hotel float, Total_Circuit float, Total_Facture float,
						Age number, Classe_sociale varchar2(20), Dest_Pref varchar2(20), Invest_Moyen float ) ;
						
						
						
						
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

INSERT INTO Sejour VALUES (1,10,'Cool',1) ;
INSERT INTO Sejour VALUES (2,10,'Funny',1) ;
INSERT INTO Sejour VALUES (3,21,'Chiant',0.5) ;
INSERT INTO Sejour VALUES (4,21,'Fatiguant',0.4) ;

/* Remplissage de la table Assoc_Prix_Séjour_Circuit */

INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (1,2,100.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,2,115.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,4,50.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (4,3,65.00) ;

/* Remplissage de la table Vol */

INSERT INTO Vol VALUES (1,1,10.00,20.00) ;
INSERT INTO Vol VALUES (2,1,15.00,40.00) ;
INSERT INTO Vol VALUES (3,2,9.00,21.00) ;
INSERT INTO Vol VALUES (4,4,12.00,24.00) ;

/* Remplissage de la table Client */

INSERT INTO Client VALUES (1,'Rue de la plage', '0556654558', 'Burneau', 'Bruno', 26, 'Burneau@laposte.net', 'Etudiant', 1, 400.00);
INSERT INTO Client VALUES (2,'Rue du geek', '0679473302', 'Fou', 'Fabien', 23, 'Mrfou@hotmail.fr', 'Salarié', 2, 215.00);
INSERT INTO Client VALUES (3,'Rue de la soif', '0557348875', 'Durand', 'Patrick', 52, 'Aucun', 'Salarié', 3, 1000.00);

/* Remplissage de la table Facturation */
/* N'y a t-il pas un moyen plus malin de le faire? */
/* Noter que timestamp est soit le nombre de seconde depuis le 01 janv 1970 à 00H00M00S ou bien soit un binaire qui permet de synchroniser des tables pour faire des mises à jour */

INSERT INTO Facturation Values (1, sysdate, 'Rue de la plage', '0556654558', 'Burneau' ,'Bruno', 'Bruxelles', 'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 'Fatiguant', 0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Bordeaux', 400.00) ;

						