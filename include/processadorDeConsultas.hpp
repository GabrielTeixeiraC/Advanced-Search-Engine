//---------------------------------------------------------------------
// Arquivo	: processadorDeConsultas.h
// Conteudo	: definicao da struct processadorDeConsultas
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------
#ifndef PROCESSADORDECONSULTASH
#define PROCESSADORDECONSULTASH

#include <iostream>
#include <string>
#include "indiceInvertido.hpp"
#include "quicksort.hpp"

using namespace std;

class ProcessadorDeConsultas {
    private:
        double * normasDocumentos;
        int numeroDeDocumentos;
        IndiceInvertido * indiceInvertido;
        ProcessadorDeDocumentos * processador;
        unsigned long maiorIdDocumento;
        Resultado * resultados;
    public:
        ProcessadorDeConsultas(int numeroDeDocumentos, IndiceInvertido * indiceInvertido, ProcessadorDeDocumentos * processador, Resultado * resultados);
        void calculaNormaDocumentos();
        void processaConsulta(string nomeArquivoConsulta, string nomeArquivoStopwords);
        void ordenaResultados();
        void imprimeResultados(string nomeArquivoSaida);
        ~ProcessadorDeConsultas();
};

#endif
