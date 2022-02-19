//---------------------------------------------------------------------
// Arquivo	: termoVocabulario.h
// Conteudo	: definicao da struct termoVocabulario
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------
#ifndef TERMOVOCABULARIOH
#define TERMOVOCABULARIOH

#include <iostream>
#include <string>
using namespace std;

// TermoVocabulario: guarda um termo e sua frequencia
struct TermoVocabulario {
    string termo = "";
    int frequencia = 0;
};

#endif
