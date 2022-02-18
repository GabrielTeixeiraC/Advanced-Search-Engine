//---------------------------------------------------------------------
// Arquivo      : opcoesMain.hpp
// Conteudo     : definicoes da classe opcoesMain
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef OPCOESMAINH
#define OPCOESMAINH

#include <string>

using namespace std;

class OpcoesMain {

    public:
        string nomeArquivoConsultas, nomeArquivoSaida, nomePastaCorpus, nomeArquivoStopwords, nomeArquivoLog;
        int regmem;
        OpcoesMain() = default;
        void uso();
        void parse_args(int argc, char ** argv);
};

#endif
