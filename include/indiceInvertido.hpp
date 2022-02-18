//---------------------------------------------------------------------
// Arquivo      : indiceInvertido.hpp
// Conteudo     : definicoes da classe IndiceInvertido
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef INDICEINVERTIDOH
#define INDICEINVERTIDOH

#include <string>

using namespace std;

class IndiceInvertido {
    public:
        IndiceInvertido() = default;
        long long calculaHash(string termo);
        void criaIndice(string nomePastaCorpus, string nomeArquivoStopwords);
};

#endif
