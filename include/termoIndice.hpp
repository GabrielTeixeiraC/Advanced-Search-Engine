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
#include <listaEncadeada.hpp>
using namespace std;

// TermoIndice: guarda o documento de origem de um termo e sua frequencia
struct TermoIndice {
    string termo;
    int documento;
    int frequencia;

    TermoIndice(){
        termo = "";
        documento = 0;
        frequencia = 0;
    }
};

#endif
