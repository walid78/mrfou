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
c11_Date_Res_debut date;
c11_Date_res_fin date;

--variable ID de facture
c12_Id_facture number;

--variables pour la dest preferée
c13_dest_pref varchar2(20);
c13_nb_dest_pref number;

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
cursor c11 is select Nom_Hotel,	Adresse,Hotel.ID_Classe,Capac_S,Capac_D,Prix_S,Prix_D,c11_Date_Res_debut,c11_Date_Res_fin
       	      	     from Hotel,Classe_Hotel 
       		     where (Hotel.ID_Hotel =c8_Tab_ID_Hotel and Hotel.ID_Classe = Classe_Hotel.ID_Classe) ;

cursor c12 is select max(ID_Facture) from facturation;
cursor c13 is SELECT nom_dest,COUNT(NOM_DEST) AS Total FROM facturation GROUP BY NOM_DEST ORDER BY Total desc;


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
	open c11;fetch c11 into c11_Nom_Hotel,c11_Adresse_Hotel,c11_Classe_Hotel,c11_Capac_S,c11_Capac_D,c11_Prix_S,c11_Prix_D,c11_Date_Res_debut,c11_Date_Res_fin;

	--calcul du total local et total
	Total_Hotel_Courant := c8_NB_S*c11_Prix_S + c8_NB_D*c11_Prix_D;
	dbms_output.put_line('Total_Hotel_Courant' || Total_Hotel_Courant);
	Total_Hotel := Total_Hotel + Total_Hotel_Courant;

	--insertion dans facturation des hotels
	insert into facturation values(c12_Id_facture,sysdate,'HOTEL',c1_adresse_client,c1_tel,c1_nom,c1_prenom,null,c4_Pays_Dest,
	       	    c11_nom_hotel,c11_adresse_hotel,c11_classe_hotel,c11_prix_s,c11_prix_d,c11_Date_Res_debut,c11_Date_Res_fin,null,c2_Duree_Sejour,null,null,null,
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


--delete from reservation where (ID_Client = client);


--estimation de la destination preferée
open c13;fetch c13 into c13_dest_pref,c13_nb_dest_pref;


--remplissage facture circuit.

insert into facturation values(c12_Id_facture,sysdate,'CIRCUIT',c1_adresse_client,c1_tel,c1_nom,c1_prenom,null,c4_Pays_Dest,
	       	    null,null,null,null,null,null,null,c3_Nom_Circuit,c2_Duree_Sejour,null,null,null,
		    nombre_adulte,nombre_enfant,c2_description_sejour,c2_coeff_sejour,null,null,Total_Circuit,null,
		    c1_age,c1_classe_sociale,c13_dest_pref,null);

--remplissage facture vol.

insert into facturation values(c12_Id_facture,sysdate,'VOL',c1_adresse_client,c1_tel,c1_nom,c1_prenom,null,c4_Pays_Dest,
	       	    null,null,null,null,null,null,null,c3_Nom_Circuit,c2_Duree_Sejour,c6_Prix_Circuit,c5_Prix_Vol_enfant,c5_Prix_Vol_adulte,
		    nombre_adulte,nombre_enfant,c2_Description_Sejour,c2_coeff_sejour,Total_Vol,null,null,null,
		    c1_age,c1_classe_sociale,c13_dest_pref,null);



--remplissage facture TOTAL.

insert into facturation values(c12_Id_facture,sysdate,'TOTAL',c1_adresse_client,c1_tel,c1_nom,c1_prenom,c4_nom_dest,c4_Pays_Dest,
	       	    null,null,null,null,null,null,null,c3_Nom_Circuit,c2_Duree_Sejour,null,null,null,
		    nombre_adulte,nombre_enfant,c2_description_Sejour,c2_coeff_sejour,Total_Vol,total_hotel,total_circuit,total_facture,
		    c1_age,c1_classe_sociale,c13_dest_pref,null);

commit;

end;
/

show errors;

SET SERVEROUTPUT ON

BEGIN
AjoutFacture(1,2,1,1,1,2,2);
commit;
END;

-- Fonctions stockees pour les ajouts
----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_client(
  adresse varchar,
  tel varchar,
  nom varchar,
  prenom varchar,
  age number,
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
show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_dest(
  nom_destination varchar,
  pays varchar)
as
-- Variables --
id_dest destination.id_dest%type;

-- Programme --
begin
  SELECT seq_dest.NEXTVAL INTO id_dest FROM dual;

  INSERT INTO destination
  VALUES (
  	 id_dest,
	 nom_destination,
	 pays
	 );

end;
/
show errors;

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
show errors;

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
show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_vol(
  id_dest number,
  prix_enfant float,
  prix_adulte float)
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
	 prix_enfant,
	 prix_adulte
	 );

end;
/
show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_classe(
  prix_s float,
  prix_d float)
as
-- Variables --
id_classe classe_hotel.id_classe%type;

-- Programme --
begin
  SELECT seq_classe.NEXTVAL INTO id_classe FROM dual;

  INSERT INTO classe_hotel
  VALUES (
  	 id_classe,
	 prix_s,
	 prix_d
	 );

end;
/
show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_sejour(
  duree number,
  description varchar,
  coeff float)
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
show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_dest_circuit(
  id_dest number,
  id_circuit number)
as
-- Variables --
id_d number;
id_c number;
plop varchar(10);
plop2 varchar(10);

cursor d is select id_dest from destination;
cursor c is select id_circuit from circuit;

-- Programme --
begin
open  d;
open  c;
plop := 'False';
plop2 := 'False';

loop
  fetch d into id_d;
  Exit  When d%NOTFOUND;
  if id_d = id_dest then plop :='Ok'; 
  end if;
end loop;

loop 
  fetch c into id_c;
   Exit  When c%NOTFOUND;
   if id_c = id_circuit then plop2 := 'Ok'; end if;       
end loop;

if plop = 'Ok' and  plop2 = 'Ok' then 
    INSERT INTO assoc_dest_circuit
         VALUES (
  	 id_dest,
	 id_circuit
	 );     
     
end if;

if plop2 = 'False' then dbms_output.put_line('Id_Circuit non existant');end if;
 if plop = 'False'then dbms_output.put_line('Id_Dest non existant');end if;         

end;
/

show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_circuit_sejour(
  id_circuit number,
  id_sejour number,
  prix number)
as
-- Variables --
id_j number;
id_c number;
plop varchar(10);
plop2 varchar(10);

cursor j is select id_sejour from sejour;
cursor c is select id_circuit from circuit;

-- Programme --
begin
open  j;
open  c;
plop := 'False';
plop2 := 'False';

loop
  fetch j into id_j;
  Exit  When j%NOTFOUND;
  if id_j = id_sejour then plop :='Ok'; 
  end if;
end loop;

loop 
  fetch c into id_c;
   Exit  When c%NOTFOUND;
   if id_c = id_circuit then plop2 := 'Ok'; end if;       
end loop;

if plop = 'Ok' and  plop2 = 'Ok' then 
    INSERT INTO Assoc_Prix_Sejour_Circuit
         VALUES (
	 id_circuit,
	 id_sejour,
	 prix
	 );     
     
end if;

if plop2 = 'False' then dbms_output.put_line('Id_Circuit non existant');end if;
 if plop = 'False'then dbms_output.put_line('Id_Sejour non existant');end if;         

end;
/

show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_reservation(
  id_client number,
  id_hotel number,
  date1 date,
  date2 date,
  NBS number,
  NBD number)
as

-- Variables --
id_h number;
id_c number;
plop varchar(10);
plop2 varchar(10);

cursor h is select id_hotel from hotel;
cursor c is select id_client from client

-- Programme --
begin
open  h;
open  c;
plop := 'False';
plop2 := 'False';

loop
  fetch h into id_h;
  Exit  When h%NOTFOUND;
  if id_h = id_hotel then plop :='Ok'; 
  end if;
end loop;

loop 
  fetch c into id_c;
   Exit  When c%NOTFOUND;
   if id_c = id_client then plop2 := 'Ok'; end if;       
end loop;

if plop = 'Ok' and  plop2 = 'Ok' then 
    INSERT INTO reservation
         VALUES (
	 id_client,
	 id_hotel,
	 date1,
         date2,
         NBS,
         NBD
	 );     
     
end if;

if plop2 = 'False' then dbms_output.put_line('Id_Client non existant');end if;
 if plop = 'False'then dbms_output.put_line('Id_Hotel non existant');end if;         

end;
/

show errors;

----------------------------------------
CREATE OR REPLACE PROCEDURE ajout_etape(
  no_etape number,
  id_circuit number,
  descriptif varchar)
as
-- Variables --
id_etape etape.id_etape%type;
id_c number;
plop varchar(10);
cursor c is select id_circuit from circuit;

-- Programme --
begin
open  c;
plop := 'False';
  SELECT seq_etape.NEXTVAL INTO id_etape FROM dual;

loop
  fetch c into id_c;
  Exit  When c%NOTFOUND;
  if id_c = id_circuit then INSERT INTO etape
  VALUES (
  	 id_etape,
	 no_etape,
	 id_circuit,
	 descriptif
	 );
   plop :='Ok'; 
  end if;
end loop;

if plop2 = 'False' then dbms_output.put_line('Id_Circuit non existant');end if;
  
end;
/
show errors;
