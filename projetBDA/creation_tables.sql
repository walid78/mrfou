
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
	ID_Etape number primary key,
	No_Etape number default(1) check (No_Etape > 0),
	ID_Circuit number ,
	Descriptif varchar(50) default ' ')  tablespace ts0  ;

create table Reservation ( 
	ID_Client number not null, 
	ID_Hotel number not null,
	Date_reservation date,
        NB_Chambre_S number default(0) CHECK (NB_Chambre_S >=0) ,
        NB_Chambre_D number default(0) CHECK (NB_Chambre_D >=0)   ) tablespace ts0;

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

create table Facturation(ID_Facture number not null,
			Date_Facture date default trunc(sysdate), 
			Categorie varchar2(20),
       	     		Adresse_Client varchar2(50) , 
			Tel varchar2(10) , 
			Nom varchar2(20) , 
			Prenom varchar2(20) , 
			Nom_Dest varchar2(20), 
			Pays_Dest varchar2(20), 
			Nom_Hotel varchar2(20),
			Address_Hotel varchar2(50),
			Classe_Hotel number,
			Prix_S float , 
			Prix_D float ,
			Nom_circuit varchar2(20),
			Duree_sejour number , 
			Prix_Circuit float , 
			Prix_Vol_Enfant float ,
			Prix_Vol_Adulte float , 
			Nb_Adulte number check (Nb_Adulte>=0) , 
			Nb_Enfant number check (Nb_Enfant >=0),
			Description_Sejour varchar2(50) ,
			Coeff_Sejour float ,
			Total_Vol float ,
			Total_Hotel float , 
			Total_Circuit float , 
			Total_Facture float ,
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
INSERT INTO Hotel VALUES (4, 3,'kuntz','Rue de la soif',3, 40, 35);
INSERT INTO Hotel VALUES (5, 3,'monk','Rue du monastère',1, 40, 35);
INSERT INTO Hotel VALUES (6, 3,'Grizzly','Rue de la poutine',1, 40, 35);



--remplissage reservation:
INSERT INTO Reservation VALUES(1,1,trunc(sysdate),1,1);
INSERT INTO Reservation VALUES(2,3,trunc(sysdate),2,1);
INSERT INTO Reservation VALUES(2,4,trunc(sysdate),0,3);
INSERT INTO Reservation VALUES(1,5,trunc(sysdate),1,1);
INSERT INTO Reservation VALUES(1,2,trunc(sysdate),0,2);


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

-- Remplissage de la table Assoc_Dest_Circuit --

INSERT INTO Assoc_Dest_Circuit VALUES (1,4);
INSERT INTO Assoc_Dest_Circuit VALUES (2,3);
INSERT INTO Assoc_Dest_Circuit VALUES (2,1);

-- Remplissage de la table Séjour --

INSERT INTO Sejour VALUES (1,10,'Courte durée',1.5) ;
INSERT INTO Sejour VALUES (2,21,'Longue durée',1.0) ;


-- Remplissage de la table Assoc_Prix_Séjour_Circuit --

INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (1,2,100.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,2,115.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,4,50.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (4,3,65.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,1,51.00) ;
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


INSERT INTO Facturation Values (1, sysdate,'TOTAL' 'Rue de la plage', '0556654558', 'Burneau' ,'Bruno', 'Bruxelles', 
       	    'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 2,1,'Fatiguant',
	     0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Bordeaux', 400.00) ;



INSERT INTO Etape Values(1,1,1,'etape 1 circuit 1');
INSERT INTO Etape Values(2,2,1,'etape 2 circuit 1');
INSERT INTO Etape Values(3,1,2,'etape 1 circuit 2');
INSERT INTO Etape Values(4,1,3,'etape 1 circuit 3');	



					

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

CREATE OR REPLACE PROCEDURE AjoutFacture(client in number,sejour in number,circuit in number,dest in number, vol in number,nombre_adulte in number, nombre_enfant in number) 

as

Date_Facture date ;


--données client
c1_Adresse_Client varchar2(50);
c1_Tel varchar2(10) ;
c1_Nom varchar2(20) ;
c1_Prenom varchar2(20) ;
c1_Age number;
c1_Classe_sociale varchar2(20);


--données sejour
c2_Duree_Sejour number;
c2_Coeff_Sejour float;
c2_Description_Sejour varchar2(50);

--données circuit
c3_Nom_circuit varchar2(20);

--données destination
c4_Nom_Dest varchar2(20);
c4_Pays_Dest varchar2(20);

--données vol
c5_Prix_Vol_Enfant float;
c5_Prix_Vol_Adulte float; 

--données prix circuit
c6_Prix_Circuit float;

--données réservations 
--Type tab_number is table of number;
c8_Tab_ID_Hotel number;
c8_NB_S number;
c8_NB_D number;

--variables données hotels réservés
c11_Nom_Hotel varchar2(20);
c11_Adresse_Hotel varchar2(50);
c11_Classe_Hotel number;
c11_Capac_S number;
c11_Capac_D number;
c11_Prix_S float;
c11_Prix_D float;

--variable ID de facture
c12_Id_facture number;


--variables des totaux
Total_Vol float;
Total_Hotel_Courant float;
Total_Hotel float;
Total_Circuit float;
Total_Facture float;

Dest_Pref varchar2(20);
Invest_Moyen float;

cursor c1 is select Adresse,Tel,Nom,Prenom,Age,Classe_Sociale from Client where ID_Client = client;
cursor c2 is select Duree,Description,Coeff from Sejour where ID_Sejour = sejour ;
cursor c3 is select Nom_Circuit from Circuit where ID_Circuit = circuit ;
cursor c4 is select Nom_Destination,Pays from Destination where ID_Dest = dest ;
cursor c5 is select Prix_Enfant,Prix_Adulte from Vol where ID_Vol = vol ;
cursor c6 is select Prix from  Assoc_Prix_Sejour_Circuit where (ID_Circuit = circuit and ID_Sejour = sejour);
--
cursor c8 is select ID_Hotel,NB_Chambre_S,NB_Chambre_D from  Reservation where ID_Client = client;
--
cursor c11 is select Nom_Hotel,	Adresse,Hotel.ID_Classe,Capac_S,Capac_D,Prix_S,Prix_D 
       	      	     from Hotel,Classe_Hotel 
       		     where (Hotel.ID_Hotel =c8_Tab_ID_Hotel and Hotel.ID_Classe = Classe_Hotel.ID_Classe) ;

cursor c12 is select max(ID_Facture) from facturation;
--Pour FABIEN
--Decrementer les capacités S et D avant l'appel a facturation

--Debut procedure
begin

open c1;fetch c1 into c1_Adresse_Client,c1_Tel,c1_Nom,c1_Prenom,c1_Age,c1_Classe_sociale;
open c2;fetch c2 into c2_Duree_Sejour,c2_Description_Sejour,c2_Coeff_Sejour;
open c3;fetch c3 into c3_Nom_circuit;
open c4;fetch c4 into c4_Nom_Dest,c4_Pays_Dest;
open c5;fetch c5 into c5_Prix_Vol_Enfant,c5_Prix_Vol_Adulte;
open c6;fetch c6 into c6_Prix_Circuit;
open c8;
open c12;fetch c12 into c12_Id_facture;c12_Id_facture := c12_Id_facture + 1;

--Boucle sur tous les hotel réservés

Total_Hotel_Courant := 0;
Total_Hotel := 0;
Loop
	fetch c8 into c8_Tab_ID_Hotel,c8_NB_S,c8_NB_D;
        Exit When c8%NOTFOUND ;
	open c11;fetch c11 into c11_Nom_Hotel,c11_Adresse_Hotel,c11_Classe_Hotel,c11_Capac_S,c11_Capac_D,c11_Prix_S,c11_Prix_D;
	Total_Hotel_Courant := c8_NB_S*c11_Prix_S + c8_NB_D*c11_Prix_D;
	dbms_output.put_line('Total_Hotel_Courant' || Total_Hotel_Courant);
	Total_Hotel := Total_Hotel + Total_Hotel_Courant;

	--insertion dans facturation des hotels
	insert into facturation values(c12_Id_facture,sysdate,'HOTEL',c1_adresse_client,c1_tel,c1_nom,c1_prenom,c4_nom_dest,c4_Pays_Dest,
	       	    c11_nom_hotel,c11_adresse_hotel,c11_classe_hotel,c11_prix_s,c11_prix_d,null,c2_Duree_Sejour,null,null,null,
		    nombre_adulte,nombre_enfant,c2_description_sejour,null,null,total_hotel_courant,null,null,
		    c1_age,c1_classe_sociale,null,null);


	close c11;
End loop ;

--Affichage des données
dbms_output.put_line(c1_Adresse_Client || ' ' || c1_Tel || ' ' || c1_Nom ||' '|| c1_Prenom || ' ' || c1_Age || ' ' || c1_Classe_sociale);
dbms_output.put_line(c2_Duree_Sejour || ' ' || c2_Description_Sejour || ' ' || c2_Coeff_Sejour);
dbms_output.put_line(c3_Nom_Circuit);
dbms_output.put_line(c4_Nom_Dest || ' ' || c4_Pays_Dest);
dbms_output.put_line(c5_Prix_Vol_Enfant || ' ' || c5_Prix_Vol_Adulte);
dbms_output.put_line(c6_Prix_Circuit);

--calcul du total_vol
Total_Vol:= c5_Prix_Vol_Enfant*nombre_enfant + c5_Prix_Vol_Adulte*nombre_adulte;
dbms_output.put_line('Total vol = ' || Total_Vol);

--calcul du total_circuit
Total_Circuit:= c6_Prix_Circuit*c2_Coeff_Sejour*(nombre_enfant + nombre_adulte);
dbms_output.put_line('Total circuit = ' || Total_Circuit);

--calcul prix_hotel
dbms_output.put_line('Total hotel = ' || Total_Hotel);

Total_Facture := Total_Vol + Total_Circuit + Total_Hotel;
--calcul prix total
dbms_output.put_line('Total Facture= ' || Total_Facture);


--Effacer enregistrement réservation_Client

--ajouter un champs 'intitulé' dans facturation avec HOTEL,VOL,CIRCUIT ou TOTAL


--remplissage facture circuit.

insert into facturation values(c12_Id_facture,'CIRCUIT',sysdate,c1_adresse_client,c1_tel,c1_nom,c1_prenom,c4_nom_dest,c4_Pays_Dest,
	       	    null,null,null,null,null,c3_Nom_Circuit,c2_Duree_Sejour,null,null,null,
		    nombre_adulte,nombre_enfant,c2_description_sejour,c2_coeff_sejour,null,null,Total_Circuit,null,
		    c1_age,c1_classe_sociale,null,null);

--remplissage facture vol.

insert into facturation values(c12_Id_facture,sysdate,'VOL',c1_adresse_client,c1_tel,c1_nom,c1_prenom,c4_nom_dest,c4_Pays_Dest,
	       	    null,null,null,null,null,c3_Nom_Circuit,c2_Duree_Sejour,c6_Prix_Circuit,c5_Prix_Vol_enfant,c5_Prix_Vol_adulte,
		    nombre_adulte,nombre_enfant,null,null,Total_Vol,null,null,null,
		    c1_age,c1_classe_sociale,null,null);



--remplissage facture TOTAL.

insert into facturation values(c12_Id_facture,sysdate,'TOTAL',c1_adresse_client,c1_tel,c1_nom,c1_prenom,c4_nom_dest,c4_Pays_Dest,
	       	    null,null,null,null,null,c3_Nom_Circuit,null,null,null,null,
		    nombre_adulte,nombre_enfant,null,null,Total_Vol,total_hotel,total_circuit,total_facture,
		    c1_age,c1_classe_sociale,null,null);



end;
/

show errors;

SET SERVEROUTPUT ON

BEGIN
AjoutFacture(1,2,1,1,1,2,2);
commit;
END;

-- Sequences
CREATE SEQUENCE seq_client START WITH 1;
CREATE SEQUENCE seq_dest START WITH 1;
CREATE SEQUENCE seq_hotel START WITH 1;
CREATE SEQUENCE seq_circuit START WITH 1;
CREATE SEQUENCE seq_vol START WITH 1;
CREATE SEQUENCE seq_etape START WITH 1;
CREATE SEQUENCE seq_classe START WITH 1;
CREATE SEQUENCE seq_sejour START WITH 1;

-- Fonctions stockees pour les ajouts
----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_client(
  adresse varchar,
  tel number(10),
  nom varchar,
  prenom varchar,
  age number(3),
  email varchar,
  classe_sociale varchar,
  id_dest_preferee number,
  investissement_moyen number)
as
-- Variables --
id_client client.id_client%type;

-- Programme --
begin
  SELECT seq_client.NEXTVAL INTO id_client FROM dual;

  INSERT INTO client
  VALUES (
  	 id_client,
	 adresse,
	 tel,
	 nom,
	 prenom,
	 age,
	 email,
	 classe_sociale,
	 id_dest_preferee,
	 investissement_moyen
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_dest(
  nom_destination varchar,
  pays varchar)
as
-- Variables --
id_dest dest.id_dest%type;

-- Programme --
begin
  SELECT seq_dest.NEXTVAL INTO id_dest FROM dual;

  INSERT INTO dest
  VALUES (
  	 id_dest,
	 nom_destination,
	 pays
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_hotel(
  id_etape number,
  nom_hotel varchar,
  adresse varchar,
  id_classe number,
  capa_s number,
  capa_d number)
as
-- Variables --
id_hotel hotel.id_hotel%type;

-- Programme --
begin
  SELECT seq_hotel.NEXTVAL INTO id_hotel FROM dual;

  INSERT INTO hotel
  VALUES (
  	 id_hotel,
	 id_etape,
	 nom_hotel,
	 adresse,
	 id_classe,
	 capa_s,
	 capa_d
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_circuit(
  nom_circuit varchar)
as
-- Variables --
id_circuit circuit.id_circuit%type;

-- Programme --
begin
  SELECT seq_circuit.NEXTVAL INTO id_circuit FROM dual;

  INSERT INTO circuit
  VALUES (
  	 id_circuit,
	 nom_circuit
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_vol(
  id_dest number,
  prix_enfant number,
  prix_adulte number)
as
-- Variables --
id_vol vol.id_vol%type;

-- Programme --
begin
  SELECT seq_vol.NEXTVAL INTO id_vol FROM dual;

  INSERT INTO vol
  VALUES (
  	 id_vol,
	 id_dest,
	 prix_enfant,bordeaux1
	 prix_adulte
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_etape(
  no_etape number,
  id_circuit number,
  descriptif varchar)
as
-- Variables --
id_etape etape.id_etape%type;

-- Programme --
begin
  SELECT seq_etape.NEXTVAL INTO id_etape FROM dual;

  INSERT INTO etape
  VALUES (
  	 id_etape,
	 no_etape,
	 id_circuit,
	 descriptif
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_classe(
  prix_s number,
  prix_d number)
as
-- Variables --
id_classe classe.id_classe%type;

-- Programme --
begin
  SELECT seq_classe.NEXTVAL INTO id_classe FROM dual;

  INSERT INTO classe
  VALUES (
  	 id_classe,
	 prix_s,
	 prix_d
	 );

end;
/

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_sejour(
  duree number,
  description varchar,
  coeff number)
as
-- Variables --
id_sejour sejour.id_sejour%type;

-- Programme --
begin
  SELECT seq_sejour.NEXTVAL INTO id_sejour FROM dual;

  INSERT INTO sejour
  VALUES (
  	 id_sejour,
	 duree,
	 description,
	 coeff
	 );

end;
/

