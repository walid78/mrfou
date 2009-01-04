CFLAGS = -g -Wall -std=c99 
CC = gcc
LIBS = -lm

sudoku: sudoku.o
	$(CC) sudoku.o -o sudoku $(CFLAGS) $(LIBS)

sudoku.o:
	$(CC) sudoku.c -c $(CFLAGS) $(LIBS)
clean: 
	\rm -f sudoku sudoku.o *# *~

