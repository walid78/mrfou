# Projet compter et afficher les lignes d'un fichier

CC = gcc
CC_OPTIONS = -g -Wall
LUS_FILE = train.lus

all :
	echo "Entrer le nom d'un noeud"

cpt_reset :
	lus2ec $(LUS_FILE) $@
	ec2c $@.ec -v
	ec2c $@.ec -loop -v
	gcc $@.c $@_loop.c -o $@

vitesse :
	lus2ec $(LUS_FILE) $@
	ec2c $@.ec -v
	ec2c $@.ec -loop -v
	gcc $@.c $@_loop.c -o $@

clean :
	rm -f *.ec *.h *.c *.oc \#* cpt_reset vitesse



