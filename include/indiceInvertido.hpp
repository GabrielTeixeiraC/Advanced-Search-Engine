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
#include "processadorDeDocumentos.hpp"
#include "vocabulario.hpp"
using namespace std;

class IndiceInvertido {
    public:
        int tamanhoMaximoIndice;
        ListaEncadeada * indiceTabela;
        IndiceInvertido(int tamanhoMaximoIndice);
        long long calculaHash(string termo);
        long long calculaHash2(string termo);
        void insere(string termo, TermoIndice item);
        void pesquisa(string termo, ListaEncadeada * documentos);
        void criaIndice(string nomePastaCorpus, string nomeArquivoStopwords, ProcessadorDeDocumentos * processador);
        void desaloca();
};

#endif
