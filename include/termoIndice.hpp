//---------------------------------------------------------------------
// Arquivo	: termoIndice.h
// Conteudo	: definicao da struct termoIndice
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------
#ifndef TERMOINDICEH
#define TERMOINDICEH

#include <iostream>
#include <string>
using namespace std;

// TermoIndice: guarda o documento de origem de um termo e sua frequencia
struct TermoIndice {
    int documento;
    int frequencia;

    TermoIndice(){
        documento = 0;
        frequencia = 0;
    }
};

#endif
