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

OBJS = $(OBJ)/main.o $(OBJ)/opcoesMain.o  $(OBJ)/vocabulario.o $(OBJ)/processadorDeDocumentos.o $(OBJ)/indiceInvertido.o $(OBJ)/listaEncadeada.o $(OBJ)/memlog.o
HDRS = $(INC)/opcoesMain.hpp $(INC)/vocabulario.hpp $(INC)/processadorDeDocumentos.hpp $(INC)/termoVocabulario.hpp $(INC)/termoIndice.hpp $(INC)/indiceInvertido.hpp $(INC)/listaEncadeada.hpp $(INC)/memlog.hpp

CXXFLAGS = -c -g -std=c++17 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE) 

$(BIN)/main: $(OBJS)
	$(CXX) -o $(BIN)/main $(OBJS) -lstdc++fs

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/opcoesMain.o: $(HDRS) $(SRC)/opcoesMain.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/opcoesMain.o $(SRC)/opcoesMain.cpp

$(OBJ)/vocabulario.o: $(HDRS) $(SRC)/vocabulario.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/vocabulario.o $(SRC)/vocabulario.cpp

$(OBJ)/processadorDeDocumentos.o: $(HDRS) $(SRC)/processadorDeDocumentos.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/processadorDeDocumentos.o $(SRC)/processadorDeDocumentos.cpp

$(OBJ)/indiceInvertido.o: $(HDRS) $(SRC)/indiceInvertido.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/indiceInvertido.o $(SRC)/indiceInvertido.cpp

$(OBJ)/listaEncadeada.o: $(HDRS) $(SRC)/listaEncadeada.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/listaEncadeada.o $(SRC)/listaEncadeada.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

clean:
	rm $(EXE) $(OBJS)