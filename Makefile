# Project: Trabalho 4 de INF390
# Makefile para gerar o executavel para o teste das classes
# PontoGrafo, Sudoku, Main, Lista, Nodo
#Criado por Lucas Victor es71512
# Criado em 22/03/2015

all: PontoGrafo.o Main.o Sudoku.o
	g++ -o Sudoku.exe PontoGrafo.o Main.o Sudoku.o

PontoGrafo.o: PontoGrafo.h PontoGrafo.cpp
	g++ -c PontoGrafo.cpp

Sudoku.o: Sudoku.h Sudoku.cpp
	g++ -c Sudoku.cpp

Main.o: PontoGrafo.o Sudoku.o Main.cpp
	g++ -c Main.cpp

clean:
	rm *.o *.exe
