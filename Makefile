#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main
# Autor		: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
# Histórico	: 2021-11-23 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CXX = g++

BIN = bin
SRC = src
OBJ = obj
INC = include

OBJS = $(OBJ)/main.o $(OBJ)/vocabulario.o $(OBJ)/memlog.o
HDRS = $(INC)/vocabulario.hpp $(INC)/memlog.hpp

CXXFLAGS = -c -g -std=c++17 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE) 

$(BIN)/main: $(OBJS)
	$(CXX) -o $(BIN)/main $(OBJS) -lstdc++fs

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/vocabulario.o: $(HDRS) $(SRC)/vocabulario.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/vocabulario.o $(SRC)/vocabulario.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

clean:
	rm $(EXE) $(OBJS)