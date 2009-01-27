begin

-- Remplissage de la table Destination --
ajout_dest('Bordeaux','France');				
ajout_dest('Valence','France');
ajout_dest('Valence','Espagne');
ajout_dest('Barcelone','Espagne');
ajout_dest('Paris','France');

-- Remplissage de la table Hotel --
ajout_hotel(1,'California','Rue de LA',4, 20, 10);
ajout_hotel(4,'L hôte','Rue du serveur',2, 10, 10);
ajout_hotel(3,'Hérie','Rue de la blague',5, 40, 35);
ajout_hotel(3,'kuntz','Rue de la soif',3, 40, 35);
ajout_hotel(3,'monk','Rue du monastère',1, 40, 35);
ajout_hotel(3,'Grizzly','Rue de la poutine',1, 40, 35);

--remplissage reservation:
INSERT INTO Reservation VALUES(1,1,trunc(sysdate),1,1);
INSERT INTO Reservation VALUES(2,3,trunc(sysdate),2,1);
INSERT INTO Reservation VALUES(2,4,trunc(sysdate),0,3);
INSERT INTO Reservation VALUES(1,5,trunc(sysdate),1,1);
INSERT INTO Reservation VALUES(1,2,trunc(sysdate),0,2);


-- Remplissage de la table Classe_Hotel --
ajout_classe(10.01, 20.01) ;
ajout_classe(25.02, 45.02) ;
ajout_classe(30.03, 60.03) ;
ajout_classe(45.04, 80.04) ;
ajout_classe(60.05, 80.05) ;

-- Remplissage de la table Circuit --

ajout_circuit('Mont_Fuji') ;
ajout_circuit('Catalogne') ;
ajout_circuit('Monaco') ;
ajout_circuit('Hockenheim') ;

-- Remplissage de la table Assoc_Dest_Circuit --

ajout_dest_circuit(1,4);
ajout_dest_circuit(2,3);
ajout_dest_circuit(2,1);

-- Remplissage de la table Séjour --

ajout_sejour(10,'Courte durée',1.5) ;
ajout_sejour(21,'Longue durée',1.0) ;


-- Remplissage de la table Assoc_Prix_Séjour_Circuit --

INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (1,2,100.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,2,115.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,4,50.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (4,3,65.00) ;
INSERT INTO Assoc_Prix_Sejour_Circuit VALUES (2,1,51.00) ;
-- Remplissage de la table Vol --

ajout_vol(1,10.00,20.00) ;
ajout_vol(1,15.00,40.00) ;
ajout_vol(2,9.00,21.00) ;
ajout_vol(4,12.00,24.00) ;

-- Remplissage de la table Client --

ajout_client('Rue de la plage', '0556654558', 'Burneau', 'Bruno', 26, 'Burneau@laposte.net', 'Etudiant', 1, 400.00);
ajout_client('Rue du geek', '0679473302', 'Fou', 'Fabien', 23, 'Mrfou@hotmail.fr', 'Salarié', 2, 215.00);
ajout_client('Rue de la soif', '0557348875', 'Durand', 'Patrick', 52, 'Aucun', 'Salarié', 3, 1000.00);

-- Remplissage de la table Facturation --

INSERT INTO Facturation Values (1, sysdate,'TOTAL', 'Rue de la plage', '0556654558', 'Burneau' ,'Bruno', 'Bruxelles', 
       	    'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 2,1,'Fatiguant',
	     0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Bordeaux', 400.00) ;



-- Remplissage de la table Etape --

ajout_etape(1,1,'etape 1 circuit 1');
ajout_etape(2,1,'etape 2 circuit 1');
ajout_etape(1,2,'etape 1 circuit 2');
ajout_etape(1,3,'etape 1 circuit 3');

commit;
end;