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

// construtor do Processador de Consultas
ProcessadorDeConsultas::ProcessadorDeConsultas(int numeroDeDocumentos, IndiceInvertido * indiceInvertido, ProcessadorDeDocumentos * processador, Resultado * resultados) {
    this->indiceInvertido = indiceInvertido;
    this->processador = processador;
    maiorIdDocumento = processador->maiorIdDocumento;
    this->numeroDeDocumentos = numeroDeDocumentos;
    normasDocumentos = new double[maiorIdDocumento] {};
    this->resultados = resultados;
}

ProcessadorDeConsultas::~ProcessadorDeConsultas() 
// Descricao: limpa o Processador de Consultas 
// Entrada: -
// Saida: -
{
    delete normasDocumentos;
}

void ProcessadorDeConsultas::calculaNormaDocumentos() 
// Descricao: calcula a norma dos documentos para normalizar as similaridades
// Entrada: -
// Saida: -
{
    // percorre o indice invertido, calculando a norma dos documentos para normalizar os resultados
    for (int i = 0; i < indiceInvertido->tamanhoMaximoIndice; i++) {
        CelulaListaTermoIndice * pti = new CelulaListaTermoIndice();
        pti = indiceInvertido->indiceTabela[i].primeiro->prox;

        while (pti != NULL) {
            CelulaListaOcorrencia * po = new CelulaListaOcorrencia();
            po = pti->item.ocorrencias->primeiro->prox;

            while (po != NULL) {
                int documento = po->item.documento;
                
                // calcula tf x idf
                double tf = po->item.frequencia;
                double idf = log(numeroDeDocumentos / pti->item.ocorrencias->getTamanho());
                double tfidf = tf * idf;
                
                // soma tf x idf ao quadrado nas normas dos documentos 
                normasDocumentos[documento] += tfidf * tfidf;
                po = po->prox;
            }

            pti = pti->prox;
            delete po;
        }   

        delete pti;
    }

    // tira a raiz quadrada dos valores das normas de documentos
    for (unsigned int i = 0; i <= maiorIdDocumento; i++) {
        normasDocumentos[i] = sqrt(normasDocumentos[i]);
    }

}

void ProcessadorDeConsultas::processaConsulta(string nomeArquivoConsulta, string nomeArquivoStopwords) 
// Descricao: processa uma consulta, somando e normalizando as similaridades 
// Entrada: nomeArquivoConsulta, nomeArquivoStopwords
// Saida: -
{
    // abre o arquivo de consultas
    ifstream arquivoConsultas;
    arquivoConsultas.open(nomeArquivoConsulta);
    erroAssert(arquivoConsultas.is_open(), "Documento não foi aberto.");

    // variavel para saber se alguma palavra foi achada
    bool somou = false;

    // itera sobre o arquivo de consultas, somando os valores no vetor de resultados
    while (!arquivoConsultas.eof()){
        string termo;
        arquivoConsultas >> termo;

        // se o termo consultado for stopword, pula a palavra
        if (eStopword(termo, nomeArquivoStopwords)) {
            continue;
        }
        
        // se o arquivo já tiver terminado de ser lido, sai do loop
        if (!arquivoConsultas.good()) {
            break;
        }

        // pesquisa as ocorrencias do termo
        ListaEncadeadaOcorrencia * documentos = new ListaEncadeadaOcorrencia();
        indiceInvertido->pesquisa(termo, documentos);   
        double idf;

        CelulaListaOcorrencia * p = new CelulaListaOcorrencia();
        p = documentos->primeiro->prox;

        // calcula tf x idf e soma no vetor de resultados
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

    // normaliza o vetor de resultados
    for (unsigned int i = 0; i <= maiorIdDocumento; i++) {
        if(normasDocumentos[i] == 0) {
            continue;
        }
        resultados[i].resultado /= normasDocumentos[i];
    }
    
    avisoAssert(somou, "Nenhum termo foi achado.");

    arquivoConsultas.close();
}


bool ProcessadorDeConsultas::eStopword(string palavra, string nomeArquivoStopwords)
// Descricao: retorna se palavra é stopword ou não
// Entrada: palavra
// Saida: bool
{
    // abre arquivo de stopwords
    ifstream arquivoDeStopwords;
    arquivoDeStopwords.open(nomeArquivoStopwords);
    erroAssert(arquivoDeStopwords.is_open(), "Arquivo de stopwords não foi aberto.");
    
    // checa se a palavra passada como parametro é uma stopword
    while (!arquivoDeStopwords.eof()) {
        string stopword;

        arquivoDeStopwords >> stopword;

        // se achar, retorna true
        if (stopword == palavra){
            return true;
        }
        else {
            continue;
        }
    }
    arquivoDeStopwords.close();

    // se não achou, retorna false
    return false;
}

void ProcessadorDeConsultas::ordenaResultados() 
// Descricao: ordena os resultados 
// Entrada: -
// Saida: -
{
    QuickSort quicksort = QuickSort(processador->maiorIdDocumento);
    quicksort.OrdenaQuickSort(this->resultados);
}

void ProcessadorDeConsultas::imprimeResultados(string nomeArquivoSaida) 
// Descricao: imprime os indices dos 10 ou menos documentos mais similares 
// Entrada: nomeArquivoSaida
// Saida: -
{
    // abre arquivo de saida
    ofstream arquivoSaida;
    arquivoSaida.open(nomeArquivoSaida);
    erroAssert(arquivoSaida.is_open(), "Arquivo de saída não foi aberto.");
    
    // se tem menos de 10 documentos, o numero de impressoes maximo é atualizado
    int numeroDeImpressoes = 10;
    if (numeroDeDocumentos < 10) {
        numeroDeImpressoes = numeroDeDocumentos;
    }

    // imprime os resultados ordenados maiores que 0
    for (unsigned long i = 0; i <= maiorIdDocumento; i++) {
        if (resultados[i].resultado == 0) {
            continue;
        }        
        arquivoSaida << resultados[i].id << " ";
        numeroDeImpressoes--;
        if (numeroDeImpressoes == 0) {
            break;
        }        
    }
    arquivoSaida << endl;
    arquivoSaida.close();
}