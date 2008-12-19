
--pas de clusters car jointures sur plusieurs tables

--DESTRUCTION TABLES

drop table Destination;
drop table Hotel;
drop table Etape;
drop table Classe_Hotel;
drop table Circuit;
--drop table Assoc_Hotel_Circuit;
drop table Assoc_Dest_Circuit;
drop table Sejour;
drop table Assoc_Prix_Sejour_Circuit;
drop table Vol;
drop table Client;
drop table Facturation;
drop table Reservation;
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
drop tablespace ts11 including contents and datafiles;

--CREATION TABLESPACES

create tablespace ts0
datafile 'ts0.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts1
datafile 'ts1.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts2
datafile 'ts2.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts3
datafile 'ts3.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts4
datafile 'ts4.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts5
datafile 'ts5.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts6
datafile' ts6.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts7
datafile 'ts7.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts8
datafile 'ts8.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts9
datafile 'ts9.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;


create tablespace ts10
datafile 'ts10.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts11
datafile 'ts11.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;











--CREATION DES TABLES

create table Destination(
	ID_Dest number primary key,
	Nom_Destination varchar2(20) not null ,
	Pays varchar2(20) not null) tablespace ts0;


create table Circuit(	
	ID_Circuit number primary key,
	Nom_Circuit varchar2(20)not null)tablespace ts0 ;

create table Assoc_Dest_Circuit(
	ID_Dest number, 
	ID_Circuit number)tablespace ts0 ;

--passer les 2 clés en en une clé composée. 
create table Etape(	
	ID_Etape number ,
	ID_Circuit number ,
	Descriptif varchar(50) default ' ')  tablespace ts0  ;

create table Reservation ( 
	ID_Client number not null, 
	ID_Hotel number not null,
	Date_reservation date) tablespace ts0;

create table Hotel(	
	ID_Hotel number primary key, 
	ID_Etape number not null,
	Nom_Hotel varchar2(20) not null,
	Adresse varchar2(50) default('adresse inconnue') ,
	ID_Classe number default(1),
	Capac_S number default(0) CHECK (Capac_S >0), 
	Capac_D number default(0) CHECK (Capac_D >0)  )tablespace ts0 ;		

create table Classe_Hotel(		
	ID_Classe number primary key, 
	Prix_S float not null CHECK (Prix_S >0.0) , 
	Prix_D float not null CHECK (Prix_D >0.0) )tablespace ts0 ;

--create table Assoc_Hotel_Circuit(ID_Hotel number, ID_Circuit number)tablespace ts0 ;

create table Sejour(	
	ID_Sejour number primary key, 
	Duree number not null CHECK (Duree >0) , 
	Description varchar2(50) default(' '), 
	Coeff float default (1.0) CHECK (Coeff >0.0) )tablespace ts0 ;					

create table Assoc_Prix_Sejour_Circuit(	
	ID_Circuit number, 
	ID_Sejour number, 
	Prix float not null  CHECK (Prix >0.0)  )tablespace ts0 ;

--Prix aller/retour
create table Vol(	
	ID_Vol number primary key, ID_Dest number, 
	Prix_Enfant float CHECK (Prix_Enfant >0.0) , 
	Prix_Adulte float CHECK (Prix_Adulte >0.0) )tablespace ts0 ;

create table Client(	
	ID_Client number primary key ,
	Adresse varchar2(50),Tel varchar2(10), 
	Nom varchar2(20) not null,Prenom varchar2(20)not null, 
	Age number   CHECK (Age >0 and Age < 150) ,
	Email varchar2(30),
	Classe_Sociale varchar2(20),
	ID_Dest_Preferee number,
	Investissement_Moyen float CHECK (Investissement_Moyen > 0.0))tablespace ts0 ;
--un seul hotel pour le client
--rajouter le nombre passager enfant et adulte

create table Facturation(ID_Facture number not null,
			Date_Facture date default trunc(sysdate), 
       	     		Adresse_Client varchar2(50) not null, 
			Tel varchar2(10) not null, 
			Nom varchar2(20) not null, 
			Prenom varchar2(20) not null, 
			Nom_Dest varchar2(20)not null, 
			Pays_Dest varchar2(20) not null, 
			Nom_Hotel varchar2(20)not null,
			Address_Hotel varchar2(50) not null,
			Classe_Hotel number not null,
			Prix_S float not null , 
			Prix_D float not null,
			Nom_circuit varchar2(20)not null,
			Duree_sejour number not null, 
			Prix_Circuit float not null, 
			Prix_Vol_Enfant float not null ,
			Prix_Vol_Adulte float not null, 
			Nb_Adulte number check (Nb_Adulte>=0) , 
			Nb_Enfant number check (Nb_Enfant >=0),
			Description_Sejour varchar2(50) not null,
			Coeff_Sejour float not null,
			Total_Vol float not null ,
			Total_Hotel float not null, 
			Total_Circuit float not null, 
			Total_Facture float not null,
			Age number,
			Classe_sociale varchar2(20),
			Dest_Pref varchar2(20), 
			Invest_Moyen float )

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
INSERT INTO Hotel VALUES (3, 3,'Hérie','Rue de la blague',5, 40, 35);


--remplissage reservation:
INSERT INTO Reservation VALUES(1,1,trunc(sysdate));
INSERT INTO Reservation VALUES(2,3,trunc(sysdate));
INSERT INTO Reservation VALUES(2,4,trunc(sysdate));
INSERT INTO Reservation VALUES(1,5,trunc(sysdate));




-- Remplissage de la table Classe_Hotel --
INSERT INTO Classe_Hotel VALUES (1, 10.01, 20.01) ;
INSERT INTO Classe_Hotel VALUES (2, 25.02, 45.02) ;
INSERT INTO Classe_Hotel VALUES (3, 30.03, 60.03) ;
INSERT INTO Classe_Hotel VALUES (4, 45.04, 80.04) ;
INSERT INTO Classe_Hotel VALUES (5, 60.05, 80.05) ;

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

INSERT INTO Sejour VALUES (1,10,'Courte durée',1.5) ;
INSERT INTO Sejour VALUES (2,10,'Longue durée',1.0) ;


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


INSERT INTO Facturation Values (1, sysdate, 'Rue de la plage', '0556654558', 'Burneau' ,'Bruno', 'Bruxelles', 
       	    'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 2,1,'Fatiguant',
	     0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Bordeaux', 400.00) ;



INSERT INTO Etape Values(1,1,'etape 1 circuit 1');
INSERT INTO Etape Values(2,1,'etape 2 circuit 1');
INSERT INTO Etape Values(1,2,'etape 1 circuit 2');
INSERT INTO Etape Values(1,3,'etape 1 circuit 3');	



					

--Triggers

drop table LOG;
drop trigger trigger_log_client;
drop trigger trigger_log_circuit;
drop trigger trigger_log_hotel;
drop trigger trigger_log_destination;
				

create table LOG (
  madate timestamp,
  utilsateur varchar2(50),
  action varchar2(20),
  cible varchar2(50) )tablespace ts11;

	


create or replace trigger trigger_log_client
before delete or update or insert on Client
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Client');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Client');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Client');	
	  end if;
end if;


end;
/

create or replace trigger trigger_log_circuit
before delete or update or insert on Circuit
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Circuit');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Circuit');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Circuit');	
	  end if;
end if;


end;
/

create or replace trigger trigger_log_hotel
before delete or update or insert on Hotel
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Hotel');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Hotel');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Hotel');	
	  end if;
end if;


end;
/

create or replace trigger trigger_log_destination
before delete or update or insert on Destination
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Destination');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Destination');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Destination');	
	  end if;
end if;


end;
/



--Procédure stockée pour ajout de facture --
-- Avant d'appeler la proc, tester l'emcombrement de l'hotel
CREATE OR REPLACE PROCEDURE AjoutFacture(client in number,sejour in number,circuit in number,vol in number,nombre_adulte in number, nombre_enfant in number) 

as

Date_Facture date ;
c1_Adresse_Client varchar2(50);
c1_Tel varchar2(10) ;
c1_Nom varchar2(20) ;
c1_Prenom varchar2(20) ;
--c2_ID_Dest number;
c6_Nom_Dest varchar2(20);
c6_Pays_Dest varchar2(20);
--c2_Nom_Hotel varchar2(20);
--c2_Adresse_Hotel varchar2(50);
--c2_Classe_Hotel number;
--c3_Prix_S float;
--c3_Prix_D float;
c5_Nom_circuit varchar2(20);
c4_Duree_sejour number;
c8_Prix_Circuit float;
c7_Prix_Vol_Enfant float;
c7_Prix_Vol_Adulte float; 
c4_Description_Sejour varchar2(50);
c4_Coeff_Sejour float;
Total_Vol float;
Total_Hotel float;
Total_Circuit float;
Total_Facture float;
c1_Age number;
c1_Classe_sociale varchar2(20);
Dest_Pref varchar2(20);
Invest_Moyen float;
dest number;
cursor c1 is select Adresse,Tel,Nom,Prenom,Age,Classe_Sociale from Client where ID_Client = client;

--Decrementer les capacités S et D.


--lister les hotels réservés, leurs classes, prix, adresses .....

--cursor c2 is select Nom_Hotel,Adresse,ID_Classe,ID_Dest from Hotel where ID_Hotel = hotel;
--cursor c3 is select Prix_S,Prix_D from Classe_Hotel where ID_Classe =c2_Classe_Hotel ;

cursor c4 is select Duree,Description,Coeff from Sejour where ID_Sejour = sejour ;
cursor c5 is select Nom_Circuit from Circuit where ID_Circuit = circuit ;
		
cursor c6 is select Nom_Destination,Pays from Destination where ID_Dest = dest ;
cursor c7 is select Prix_Enfant,Prix_Adulte from Vol where ID_Vol = vol ;
cursor c8 is select c8_Prix_Circuit from  Assoc_Prix_Sejour_Circuit where (ID_Circuit=circuit and ID_Sejour=sejour);

begin

open c1;fetch c1 into c1_Adresse_Client,c1_Tel,c1_Nom,c1_Prenom,c1_Age,c1_Classe_sociale;
--open c2;fetch c2 into c2_Nom_Hotel,c2_Adresse_Hotel,c2_Classe_Hotel,c2_ID_Dest;
--open c3;fetch c3 into c3_Prix_S,c3_Prix_D;
open c4;fetch c4 into c4_Duree_sejour,c4_Description_Sejour,c4_Coeff_Sejour;
open c5;fetch c5 into c5_Nom_circuit;
select into dest from Assoc_Destination_Circuit where ID_Circuit = circuit;
open c6;fetch c6 into c6_Nom_Dest,c6_Pays_Dest;
open c7;fetch c7 into c7_Prix_Vol_Enfant,c7_Prix_Vol_Adulte;
open c8;fetch c8 into c8_Prix_Circuit;


dbms_output.put_line(c1_Adresse_Client || c1_Tel || c1_Nom || c1_Prenom || c1_Age || c1_Classe_sociale);
--dbms_output.put_line(c2_Nom_Hotel || ' ' || ' ' || c2_Adresse_Hotel || ' ' ||c2_Classe_Hotel|| ' '||c2_ID_Dest);
--dbms_output.put_line(c3_Prix_S || ' ' || c3_Prix_D);
dbms_output.put_line( c4_Duree_sejour|| ' ' ||c4_Description_Sejour  || ' ' ||c4_Coeff_Sejour);
dbms_output.put_line(c5_Nom_Circuit);
dbms_output.put_line(c6_Nom_Dest || ' ' || c6_Pays_Dest);
dbms_output.put_line(c7_Prix_Vol_Enfant || ' ' ||c7_Prix_Vol_Adulte);
--calculs
Total_Vol:= c7_Prix_Vol_Enfant*nombre_enfant + c7_Prix_Vol_Adulte*nombre_adulte;
dbms_output.put_line('total vol = ' || Total_Vol);


--calculer la somme de chaque hotels reservés par le client

--Total_Hotel:= c4_Duree_sejour*c4_Coeff_Sejour* ((nombre_adulte+nombre_enfant)/2   * c3_Prix_D +  MOD (nombre_adulte+nombre_enfant,2)   * c3_Prix_S) ;
dbms_output.put_line('total Hotel = ' || Total_Hotel     );

Total_Circuit:= (nombre_adulte+nombre_enfant)*c8_Prix_Circuit*c4_Coeff_Sejour;
dbms_output.put_line('total circuit =' || Total_Circuit);

Total_Facture:=Total_Hotel+Total_Vol+Total_Circuit;
dbms_output.put_line('total Facture ='  || Total_Facture );


end;
/

show errors;

SET SERVEROUTPUT ON

BEGIN
AjoutFacture(1,2,1,1,1,2,2);
commit;
END;