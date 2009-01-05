SRC = sudoku.c
TARGET = sudoku
CFLAGS = -g -Wall -std=c99 
CC = gcc
LIBS = -lm

all: sudoku clean

$(TARGET): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

clean: 
	rm -f *.o *# *~

polish:
	rm -f $(TARGET)

