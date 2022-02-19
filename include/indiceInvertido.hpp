//---------------------------------------------------------------------
// Arquivo      : indiceInvertido.hpp
// Conteudo     : definicoes da classe IndiceInvertido
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef INDICEINVERTIDOH
#define INDICEINVERTIDOH

#include <string>
#include "termoIndice.hpp"
#include "listaEncadeada.hpp"

using namespace std;

class IndiceInvertido {
    public:
        int tamanhoIndiceInvertido;
        ListaEncadeada* indiceInvertido;
        IndiceInvertido(tamanho);
        long long calculaHash(string termo);
        void Insere(string termo, TermoIndice item);
        ListaEncadeada Pesquisa(string termo);
        void criaIndice(string nomePastaCorpus, string nomeArquivoStopwords);
};

#endif
