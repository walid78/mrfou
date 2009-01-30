-- Vidage des tables --
DELETE FROM client;
DELETE FROM circuit;
DELETE FROM assoc_dest_circuit;
DELETE FROM destination;
DELETE FROM vol;
DELETE FROM assoc_prix_sejour_circuit;
DELETE FROM etape;
DELETE FROM reservation;
DELETE FROM sejour;
DELETE FROM hotel;
DELETE FROM classe_hotel;
DELETE FROM hotel;

-- Séquences --

-- Suppression de séquences --
DROP SEQUENCE  seq_client;
DROP SEQUENCE  seq_dest;
DROP SEQUENCE  seq_hotel;
DROP SEQUENCE  seq_circuit;
DROP SEQUENCE  seq_vol;
DROP SEQUENCE  seq_etape;
DROP SEQUENCE  seq_classe;
DROP SEQUENCE  seq_sejour;


-- Création de séquences --
CREATE SEQUENCE seq_client START WITH 1;
CREATE SEQUENCE seq_dest START WITH 1;
CREATE SEQUENCE seq_hotel START WITH 1;
CREATE SEQUENCE seq_circuit START WITH 1;
CREATE SEQUENCE seq_vol START WITH 1;
CREATE SEQUENCE seq_etape START WITH 1;
CREATE SEQUENCE seq_classe START WITH 1;
CREATE SEQUENCE seq_sejour START WITH 1;

begin

-- Remplissage de la table Destination --
ajout_dest('Bordeaux','France');			
ajout_dest('Valence','France');
ajout_dest('Valence','Espagne');
ajout_dest('Barcelone','Espagne');
ajout_dest('Paris','France');
ajout_dest('Copacabana','Brézil');
ajout_dest('Bombay','Inde');
ajout_dest('Tokyo','Japon');
ajout_dest('Montréal','Canada');

-- Remplissage de la table Hotel --
ajout_hotel(1,'California','Rue de LA',4, 20, 10);
ajout_hotel(4,'L hôte','Rue du serveur',2, 10, 10);
ajout_hotel(3,'Hérie','Rue de la blague',5, 40, 35);
ajout_hotel(3,'kuntz','Rue de la soif',3, 40, 35);
ajout_hotel(3,'monk','Rue du monastère',1, 40, 35);
ajout_hotel(3,'Grizzly','Rue de la poutine',1, 40, 35);
ajout_hotel(3,'Brazilio','avenue de la salsa',3,10,5);
ajout_hotel(2,'Le yéti','place de leverest',2,20,15);
ajout_hotel(5,'Le Sake','Rue du sushi',4,10,10);

--remplissage reservation:
--ajout_reservation(1,1,trunc(sysdate),trunc(sysdate),1,1);
--ajout_reservation(2,3,trunc(sysdate),trunc(sysdate),2,1);
--ajout_reservation(2,4,trunc(sysdate),trunc(sysdate),0,3);
--ajout_reservation(1,5,trunc(sysdate),trunc(sysdate),1,1);
--ajout_reservation(1,2,trunc(sysdate),trunc(sysdate),0,2);

-- Remplissage de la table Classe_Hotel --
ajout_classe(10.01, 20.01) ;
ajout_classe(25.02, 45.02) ;
ajout_classe(30.03, 60.03) ;
ajout_classe(45.04, 80.04) ;
ajout_classe(60.05, 80.05) ;
ajout_classe(26.00,50.00);

-- Remplissage de la table Circuit --

ajout_circuit('Mont_Fuji') ;
ajout_circuit('Catalogne') ;
ajout_circuit('Monaco') ;
ajout_circuit('Hockenheim') ;
ajout_circuit('Electronique');
ajout_circuit('Automobile');
ajout_circuit('Court');
ajout_circuit('Circuit du rhum');

-- Remplissage de la table Assoc_Dest_Circuit --

ajout_dest_circuit(1,1);
ajout_dest_circuit(3,4);
ajout_dest_circuit(2,1);
ajout_dest_circuit(4,7);
ajout_dest_circuit(6,3);

-- Remplissage de la table Séjour --
 
ajout_sejour(10,'Haute Saison',1.5) ;
ajout_sejour(21,'Basse Saison',1.0) ;
ajout_sejour(10,'Chaleur du brézil',2.5);
ajout_sejour(21,'Froid de leverest',0.5);
ajout_sejour(10,'Au Soleil',1.0);
ajout_sejour(21,'Mode Touriste',1.0);
ajout_sejour(21,'Eclate garantie',1.0);


-- Remplissage de la table Assoc_Prix_Séjour_Circuit --
  
ajout_circuit_sejour(1,2,100.00) ;
ajout_circuit_sejour(2,2,115.00) ;
ajout_circuit_sejour(2,4,50.00) ;
ajout_circuit_sejour(4,3,65.00) ;
ajout_circuit_sejour(2,1,51.00) ;
ajout_circuit_sejour(6,5,25.99);
 

-- Remplissage de la table Vol --

ajout_vol(1,10.00,20.00) ;
ajout_vol(1,15.00,40.00) ;
ajout_vol(2,9.00,21.00) ;
ajout_vol(4,12.00,24.00) ;
ajout_vol(5,12.05,19.05);
ajout_vol(3,40.00,60.00);
ajout_vol(6,35.00,70.00);

-- Remplissage de la table Client --

ajout_client('Rue de la plage', '0556654558', 'Burneau', 'Bruno',
		26, 'Burneau@laposte.net', 'Etudiant', 1, 400.00);
ajout_client('Rue du geek', '0679473302', 'Fou', 'Fabien', 23, 
		'Mrfou@hotmail.fr', 'Salarié', 2, 215.00);
ajout_client('Rue de la soif', '0557348875', 'Durand', 
		'Patrick', 52, 'Aucun', 'Salarié', 3, 1000.00);
ajout_client('rue du pin','0606060606','dutronc','michel',19,
		'dut.michel@pouet.fr','etudiant',null,null);
ajout_client('rue orange','0557575757','prudence','michel',38,
		'prudence.michel@wanadoo.fr','salarié',null,null);


AjoutFacture(1,2,1,1,1,2,2);
AjoutFacture(2,2,1,1,1,2,2);
AjoutFacture(3,2,1,1,1,2,2);




-- Remplissage de la table Etape --

ajout_etape(1,1,'etape 1 circuit 1');
ajout_etape(2,1,'etape 2 circuit 1');
ajout_etape(1,2,'etape 1 circuit 2');
ajout_etape(1,3,'etape 1 circuit 3');
ajout_etape(5,3,'etape 5 circuit 3');

commit;
end;
