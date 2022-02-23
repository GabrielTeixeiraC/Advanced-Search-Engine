//---------------------------------------------------------------------
// Arquivo	: processadorDeConsultas.cpp
// Conteudo	: implementacao do ProcessadorDeConsultas
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "processadorDeConsultas.hpp"
#include "processadorDeDocumentos.hpp"
#include "indiceInvertido.hpp"
#include "vocabulario.hpp"
#include "msgassert.hpp"
#include "ocorrencia.hpp"

ProcessadorDeConsultas::ProcessadorDeConsultas(int numeroDeDocumentos, IndiceInvertido * indiceInvertido, ProcessadorDeDocumentos * processador, Resultado * resultados) {
    this->indiceInvertido = indiceInvertido;
    this->processador = processador;
    maiorIdDocumento = processador->maiorIdDocumento;
    this->numeroDeDocumentos = numeroDeDocumentos;
    normasDocumentos = new double[maiorIdDocumento] {};
    this->resultados = resultados;
}

ProcessadorDeConsultas::~ProcessadorDeConsultas() {
    delete normasDocumentos;
}

void ProcessadorDeConsultas::calculaNormaDocumentos() {
    for (int i = 0; i < indiceInvertido->tamanhoMaximoIndice; i++) {
        CelulaListaTermoIndice * pti = new CelulaListaTermoIndice();
        pti = indiceInvertido->indiceTabela[i].primeiro->prox;
        while (pti != NULL) {
            CelulaListaOcorrencia * po = new CelulaListaOcorrencia();
            po = pti->item.ocorrencias->primeiro->prox;
            while (po != NULL) {
                double tf = po->item.frequencia;
                int documento = po->item.documento;
                double idf = log(numeroDeDocumentos / pti->item.ocorrencias->getTamanho());
                double tfidf = tf * idf;
                normasDocumentos[documento] += tfidf * tfidf;
                po = po->prox;
            }
            pti = pti->prox;
            delete po;
        }   
        delete pti;
    }

    for (unsigned int i = 0; i <= maiorIdDocumento; i++) {
        normasDocumentos[i] = sqrt(normasDocumentos[i]);
    }

}

void ProcessadorDeConsultas::processaConsulta(string nomeArquivoConsulta, string nomeArquivoStopwords) {
    ifstream arquivoConsultas;
    arquivoConsultas.open(nomeArquivoConsulta);
    erroAssert(arquivoConsultas.is_open(), "Documento não foi aberto.");

    bool somou = false;

    while (!arquivoConsultas.eof()){
        string termo;
        arquivoConsultas >> termo;

        if (!arquivoConsultas.good()) {
            break;
        }

        ListaEncadeadaOcorrencia * documentos = new ListaEncadeadaOcorrencia();
        indiceInvertido->pesquisa(termo, documentos);   
        double idf;

        CelulaListaOcorrencia * p = new CelulaListaOcorrencia();
        p = documentos->primeiro->prox;

        if (documentos->getTamanho() > 0) {
            while (p != NULL) {
                Ocorrencia ocorrencia = p->item;
                idf = log(numeroDeDocumentos/documentos->getTamanho());
                int tf;
                tf = p->item.frequencia;
                
                int idDocumento;
                idDocumento = ocorrencia.documento;

                resultados[idDocumento].resultado += tf * idf;
                resultados[idDocumento].id = idDocumento; 
                p = p->prox;
            }
            somou = true;
        }
        else {
            continue;
        }
        
        documentos->limpa();
        delete p;
        
    }

    for (unsigned int i = 0; i <= maiorIdDocumento; i++) {
        if(normasDocumentos[i] == 0) {
            continue;
        }
        resultados[i].resultado /= normasDocumentos[i];
    }

    if(!somou) {
        avisoAssert(somou, "Nenhum termo foi achado.");
    }

    arquivoConsultas.close();
}

void ProcessadorDeConsultas::ordenaResultados() {
    QuickSort quicksort = QuickSort(processador->maiorIdDocumento);
    quicksort.OrdenaQuickSort(this->resultados);
}

void ProcessadorDeConsultas::imprimeResultados(string nomeArquivoSaida) {
    ofstream arquivoSaida;
    arquivoSaida.open(nomeArquivoSaida);
    erroAssert(arquivoSaida.is_open(), "Arquivo de saída não foi aberto.");
    
    int numeroDeImpressoes = 10;
    if (numeroDeDocumentos < 10) {
        numeroDeImpressoes = numeroDeDocumentos;
    }

    for (unsigned long i = 0; i <= maiorIdDocumento; i++) {
        if (resultados[i].resultado == 0) {
            continue;
        }        
        cout.precision(30);
        arquivoSaida << resultados[i].id << " ";
        numeroDeImpressoes--;
        if (numeroDeImpressoes == 0) {
            break;
        }        
    }
    arquivoSaida << endl;
    arquivoSaida.close();
}