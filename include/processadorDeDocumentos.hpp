//---------------------------------------------------------------------
// Arquivo      : processadorDeDocumentos.hpp
// Conteudo     : definicoes da classe ProcessadorDeDocumentos
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef PROCESSADORDEDOCUMENTOSH
#define PROCESSADORDEDOCUMENTOSH

#include <string>

using namespace std;

class ProcessadorDeDocumentos {
    public:
        int maiorIdDocumento;
        int numeroDeDocumentos;
        ProcessadorDeDocumentos();
        int contaNumeroDeTermos(string nomeDocumento);
        int processaCorpus(string nomePastaCorpus);
        int processaDocumento(string nomeDocumento);
};

#endif
