
--pas de clusters car jointures sur plusieurs tables

--DESTRUCTION TABLES

drop table Destination;
drop table Hotel;
drop table Classe_Hotel;
drop table Circuit;
--drop table Assoc_Hotel_Circuit;
drop table Assoc_Dest_Circuit;
drop table Sejour;
drop table Assoc_Prix_Sejour_Circuit;
drop table Vol;
drop table Client;
drop table Facturation;

--DESTRUCTION TABLESPACES+FILES

drop tablespace ts0 including contents and datafiles;
drop tablespace ts1 including contents and datafiles;
drop tablespace ts2 including contents and datafiles;
drop tablespace ts3 including contents and datafiles;
drop tablespace ts4 including contents and datafiles;
drop tablespace ts5 including contents and datafiles;
drop tablespace ts6 including contents and datafiles;
drop tablespace ts7 including contents and datafiles;
drop tablespace ts8 including contents and datafiles;
drop tablespace ts9 including contents and datafiles;
drop tablespace ts10 including contents and datafiles;

--CREATION TABLESPACES

create tablespace ts0
datafile 'ts0.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts1
datafile 'ts1.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts2
datafile 'ts2.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts3
datafile 'ts3.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts4
datafile 'ts4.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts5
datafile 'ts5.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts6
datafile' ts6.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts7
datafile 'ts7.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts8
datafile 'ts8.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts9
datafile 'ts9.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;


create tablespace ts10
datafile 'ts10.dbf' size 10M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;




--CREATION DES TABLES

create table Destination(ID_Dest number primary key,Nom_Destination varchar2(20) not null ,Pays varchar2(20) not null) tablespace ts0;
create table Circuit(ID_Circuit number primary key,Nom_Circuit varchar2(20)not null)tablespace ts0 ;
create table Assoc_Dest_Circuit(ID_Dest number, ID_Circuit number)tablespace ts0 ;


create table Hotel(ID_Hotel number primary key, ID_Dest number not null,Nom_Hotel varchar2(20) not null,Addresse varchar2(50) default('adresse inconnue') ,
					ID_Classe number default(1), Capac_S number default(0) CHECK (Capac_S >0), Capac_D number default(0) CHECK (Capac_D >0)  )tablespace ts0 ;		

create table Classe_Hotel(ID_Classe number primary key, Prix_S float not null CHECK (Prix_S >0.0) , Prix_D float not null CHECK (Prix_D >0.0) )tablespace ts0 ;

--create table Assoc_Hotel_Circuit(ID_Hotel number, ID_Circuit number)tablespace ts0 ;

create table Sejour(ID_Sejour number primary key, Duree number not null CHECK (Duree >0) , Description varchar2(50) default(' '), Coeff float default (1.0) CHECK (Coeff >0.0)     )tablespace ts0 ;					

create table Assoc_Prix_Sejour_Circuit(ID_Circuit number, ID_Sejour number, Prix float not null  CHECK (Prix >0.0)  )tablespace ts0 ;

create table Vol(ID_Vol number primary key, ID_Dest number, Prix_Enfant float CHECK (Prix_Enfant >0.0) , Prix_Adulte float CHECK (Prix_Adulte >0.0) )tablespace ts0 ;

create table Client(ID_Client number primary key ,Addresse varchar2(50),Tel varchar2(10), Nom varchar2(20) not null,Prenom varchar2(20)not null, Age number   CHECK (Age >0 and Age < 150) , 
					Email varchar2(30),Classe_sociale varchar2(20), ID_Dest_Preferee number, Investissement_Moyen float CHECK (Investissement_Moyen > 0.0))tablespace ts0 ;

create table Facturation(ID_Facture number primary key, Date_Facture date default trunc(sysdate), 
       	     			    	   	
						Addresse_Client varchar2(50) not null, Tel varchar2(10) not null, Nom varchar2(20) not null, Prenom varchar2(20) not null, 
						Nom_Dest varchar2(20)not null, Pays_Dest varchar2(20) not null, 
						Nom_Hotel varchar2(20)not null, Address_Hotel varchar2(50) not null,Classe_Hotel number not null,
						Prix_S float not null , Prix_D float not null,
						Nom_circuit varchar2(20)not null, Duree_sejour number not null, Prix_Circuit float not null, 
						Prix_Vol_Enfant float not null ,Prix_Vol_Adulte float not null, 
						Description_Sejour varchar2(50) not null, Coeff_Sejour float not null,
						Total_Vol float not null , Total_Hotel float not null, Total_Circuit float not null, Total_Facture float not null,
						Age number, Classe_sociale varchar2(20), Dest_Pref varchar2(20), Invest_Moyen float )


--storage (initial 10M next 10M)
partition by range(Date_Facture)
(
	  
	  partition part1 values less than(to_date('01-01-2009','DD-MM-YYYY'))  tablespace ts1,
	  partition part2 values less than(to_date('01-01-2010','DD-MM-YYYY'))  tablespace ts2,
	  partition part3 values less than(to_date('01-01-2011','DD-MM-YYYY'))  tablespace ts3,
	  partition part4 values less than(to_date('01-01-2012','DD-MM-YYYY'))  tablespace ts4,
	  partition part5 values less than(to_date('01-01-2013','DD-MM-YYYY'))  tablespace ts5,
	  partition part6 values less than(to_date('01-01-2014','DD-MM-YYYY'))  tablespace ts6,
	  partition part7 values less than(to_date('01-01-2015','DD-MM-YYYY'))  tablespace ts7,
	  partition part8 values less than(to_date('01-01-2016','DD-MM-YYYY'))  tablespace ts8,
	  partition part9 values less than(to_date('01-01-2017','DD-MM-YYYY'))  tablespace ts9,
	  partition part10 values less than(to_date('01-01-2018','DD-MM-YYYY'))  tablespace ts10
)
 ;
						





						
						
						
-- Remplissage de la table Destination --
INSERT INTO Destination VALUES(1,'Bordeaux','France');				
INSERT INTO Destination VALUES(2,'Valence','France');
INSERT INTO Destination VALUES(3,'Valence','Espagne');
INSERT INTO Destination VALUES(4,'Barcelone','Espagne');
INSERT INTO Destination VALUES(5,'Paris','France');

-- Remplissage de la table Hotel --
INSERT INTO Hotel VALUES (1, 1,'California','Rue de LA',4, 20, 10);
INSERT INTO Hotel VALUES (2, 4,'L hôte','Rue du serveur',2, 10, 10);
INSERT INTO Hotel VALUES (3, 3,'Hérie','Reu de la blague',5, 40, 35);

-- Remplissage de la table Classe_Hotel --
INSERT INTO Classe_Hotel VALUES (1, 10.00, 20.00) ;
INSERT INTO Classe_Hotel VALUES (2, 25.00, 45.00) ;
INSERT INTO Classe_Hotel VALUES (3, 30.00, 60.00) ;
INSERT INTO Classe_Hotel VALUES (4, 45.00, 80.00) ;
INSERT INTO Classe_Hotel VALUES (5, 60.00, 80.00) ;

-- Remplissage de la table Circuit --

INSERT INTO Circuit VALUES (1,'Mont_Fuji') ;
INSERT INTO Circuit VALUES (2,'Catalogne') ;
INSERT INTO Circuit VALUES (3,'Monaco') ;
INSERT INTO Circuit VALUES (4,'Hockenheim') ;

-- Remplissage de la table Assoc_Hotel_Circuit --

--INSERT INTO Assoc_Hotel_Circuit VALUES (1,2);
--INSERT INTO Assoc_Hotel_Circuit VALUES (1,2);
--INSERT INTO Assoc_Hotel_Circuit VALUES (3,3);
--INSERT INTO Assoc_Hotel_Circuit VALUES (4,1);

-- Remplissage de la table Assoc_Dest_Circuit --

INSERT INTO Assoc_Dest_Circuit VALUES (1,4);
INSERT INTO Assoc_Dest_Circuit VALUES (2,3);
INSERT INTO Assoc_Dest_Circuit VALUES (2,1);

-- Remplissage de la table Séjour --

INSERT INTO Sejour VALUES (1,10,'Cool',1) ;
INSERT INTO Sejour VALUES (2,10,'Funny',1) ;
INSERT INTO Sejour VALUES (3,21,'Chiant',0.5) ;
INSERT INTO Sejour VALUES (4,21,'Fatiguant',0.4) ;

-- Remplissage de la table Assoc_Prix_Séjour_Circuit --

INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (1,2,100.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,2,115.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,4,50.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (4,3,65.00) ;

-- Remplissage de la table Vol --

INSERT INTO Vol VALUES (1,1,10.00,20.00) ;
INSERT INTO Vol VALUES (2,1,15.00,40.00) ;
INSERT INTO Vol VALUES (3,2,9.00,21.00) ;
INSERT INTO Vol VALUES (4,4,12.00,24.00) ;

-- Remplissage de la table Client --

INSERT INTO Client VALUES (1,'Rue de la plage', '0556654558', 'Burneau', 'Bruno', 26, 'Burneau@laposte.net', 'Etudiant', 1, 400.00);
INSERT INTO Client VALUES (2,'Rue du geek', '0679473302', 'Fou', 'Fabien', 23, 'Mrfou@hotmail.fr', 'Salarié', 2, 215.00);
INSERT INTO Client VALUES (3,'Rue de la soif', '0557348875', 'Durand', 'Patrick', 52, 'Aucun', 'Salarié', 3, 1000.00);

-- Remplissage de la table Facturation --


INSERT INTO Facturation Values (1, sysdate, 'Rue de la plage', '0556654558', 'Burneau' ,'Bruno', 'Bruxelles', 'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 'Fatiguant', 0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Bordeaux', 400.00) ;

						