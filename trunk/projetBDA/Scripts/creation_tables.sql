
--pas de clusters car jointures sur plusieurs tables

--DESTRUCTION TABLES

drop table Destination;
drop table Hotel;
drop table Etape;
drop table Classe_Hotel;
drop table Circuit;
drop table Assoc_Dest_Circuit;
drop table Sejour;
drop table Assoc_Prix_Sejour_Circuit;
drop table Vol;
drop table Client;
drop table Facturation;
drop table Reservation;
drop table LOG;
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

--tablespace des tables
create tablespace ts0
datafile 'ts0.dbf' size 20M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;


--de t1 a t10 : TS pour facturation
create tablespace ts1
datafile 'ts1.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts2
datafile 'ts2.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts3
datafile 'ts3.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts4
datafile 'ts4.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts5
datafile 'ts5.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts6
datafile' ts6.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts7
datafile 'ts7.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts8
datafile 'ts8.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

create tablespace ts9
datafile 'ts9.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;


create tablespace ts10
datafile 'ts10.dbf' size 200M
EXTENT MANAGEMENT LOCAL AUTOALLOCATE ;

--TS pour la table de LOG
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
	ID_Vol number primary key, 
	ID_Dest number, 
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

create table LOG (
  madate timestamp,
  utilsateur varchar2(50),
  action varchar2(20),
  cible varchar2(50) )tablespace ts11;

	

