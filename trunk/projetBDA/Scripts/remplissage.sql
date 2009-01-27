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


INSERT INTO Facturation Values (1, sysdate,'TOTAL', 'Rue de la plage', '0556654558', 'Burneau' ,'Bruno', 'Bruxelles', 
       	    'Belgique', 'California', 'Rue de LA', 4, 45.00, 80.00, 'Hockeinem', 21, 50.00, 12.00 , 24.00, 2,1,'Fatiguant',
	     0.4, 24.00, 90.00, 50.00, 164.00, 26, 'Etudiant', 'Bordeaux', 400.00) ;



INSERT INTO Etape Values(1,1,1,'etape 1 circuit 1');
INSERT INTO Etape Values(2,2,1,'etape 2 circuit 1');
INSERT INTO Etape Values(3,1,2,'etape 1 circuit 2');
INSERT INTO Etape Values(4,1,3,'etape 1 circuit 3');