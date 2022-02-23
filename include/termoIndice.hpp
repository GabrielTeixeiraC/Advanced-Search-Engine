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
#include <listaEncadeadaOcorrencia.hpp>
using namespace std;

// TermoIndice: guarda o documento de origem de um termo e sua frequencia
struct TermoIndice {
    string termo;
    ListaEncadeadaOcorrencia * ocorrencias;

    TermoIndice(){
        termo = "";
        ocorrencias = new ListaEncadeadaOcorrencia();
    }
};

#endif
