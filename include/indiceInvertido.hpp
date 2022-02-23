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
#include "listaEncadeadaTermoIndice.hpp"
#include "processadorDeDocumentos.hpp"
#include "vocabulario.hpp"
#include "termoIndice.hpp"
#include "ocorrencia.hpp"
#include "resultado.hpp"
using namespace std;

class IndiceInvertido {
    public:
        int tamanhoMaximoIndice;
        ListaEncadeadaTermoIndice * indiceTabela;
        IndiceInvertido(int tamanhoMaximoIndice);
        long long calculaHash(string termo);
        long long calculaHash2(string termo);
        void insere(string termo, Ocorrencia ocorrencia);
        void pesquisa(string termo, ListaEncadeadaOcorrencia * documentos);
        void criaIndice(string nomePastaCorpus, string nomeArquivoStopwords, ProcessadorDeDocumentos * processador, Resultado * resultados);
        void desaloca();
};

#endif
