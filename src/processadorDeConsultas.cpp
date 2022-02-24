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
#include "memlog.hpp"
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
        escreveMemLog( (long int) (&pti), sizeof(CelulaListaTermoIndice *), 0);

        pti = indiceInvertido->indiceTabela[i].primeiro->prox;
        escreveMemLog( (long int) (&pti), sizeof(CelulaListaTermoIndice *), 0);
        leMemLog( (long int) (&indiceInvertido->indiceTabela[i].primeiro->prox), sizeof(CelulaListaTermoIndice *), 0);

        while (pti != NULL) {
            CelulaListaOcorrencia * po = new CelulaListaOcorrencia();
            escreveMemLog( (long int) (&po), sizeof(CelulaListaOcorrencia *), 0);

            po = pti->item.ocorrencias->primeiro->prox;
            escreveMemLog( (long int) (&po), sizeof(CelulaListaOcorrencia *), 0);
            leMemLog( (long int) (&pti->item.ocorrencias->primeiro->prox), sizeof(CelulaListaOcorrencia *), 0);

            while (po != NULL) {
                int documento = po->item.documento;
                escreveMemLog( (long int) (&documento), sizeof(int), 0);
                leMemLog( (long int) (&po->item.documento), sizeof(int), 0);

                // calcula tf x idf
                double tf = po->item.frequencia;
                escreveMemLog( (long int) (&tf), sizeof(double), 5);
                leMemLog( (long int) (&po->item.frequencia), sizeof(tf), 0);

                double idf = log(numeroDeDocumentos / pti->item.ocorrencias->getTamanho());
                escreveMemLog( (long int) (&idf), sizeof(double), 5);
                leMemLog( (long int) (&numeroDeDocumentos), sizeof(double), 5);
                leMemLog( (long int) (&pti->item.ocorrencias), sizeof(double), 5);

                double tfidf = tf * idf;
                escreveMemLog( (long int) (&tfidf), sizeof(double), 5);
                leMemLog( (long int) (&tf), sizeof(double), 5);
                leMemLog( (long int) (&idf), sizeof(double), 5);
        
                // soma tf x idf ao quadrado nas normas dos documentos 
                normasDocumentos[documento] += tfidf * tfidf;
                escreveMemLog( (long int) (&normasDocumentos[documento]), sizeof(double), 5);
                leMemLog( (long int) (&tfidf), sizeof(double), 5);

                po = po->prox;
                escreveMemLog( (long int) (&po), sizeof(CelulaListaOcorrencia *), 0);
                leMemLog( (long int) (&po->prox), sizeof(CelulaListaOcorrencia *), 0);

            }

            pti = pti->prox;
            escreveMemLog( (long int) (&po), sizeof(CelulaListaOcorrencia *), 0);
            leMemLog( (long int) (&pti->prox), sizeof(CelulaListaOcorrencia *), 0);

            delete po;
        }   

        delete pti;
    }

    // tira a raiz quadrada dos valores das normas de documentos
    for (unsigned int i = 0; i <= maiorIdDocumento; i++) {
        normasDocumentos[i] = sqrt(normasDocumentos[i]);
        escreveMemLog( (long int) (&normasDocumentos[i]), sizeof(double), 5);
        leMemLog( (long int) (&normasDocumentos[i]), sizeof(double), 5);
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
        escreveMemLog( (long int) (&documentos), sizeof(ListaEncadeadaOcorrencia *), 0);

        indiceInvertido->pesquisa(termo, documentos);   
        double idf;

        CelulaListaOcorrencia * p = new CelulaListaOcorrencia();
        escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia *), 0);
      
        p = documentos->primeiro->prox;
        escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia *), 0);
        leMemLog( (long int) (&documentos->primeiro->prox), sizeof(CelulaListaOcorrencia *), 0);

        // calcula tf x idf e soma no vetor de resultados
        if (documentos->getTamanho() > 0) {
            while (p != NULL) {
                Ocorrencia ocorrencia = p->item;
                escreveMemLog( (long int) (&ocorrencia), sizeof(Ocorrencia), 0);
                leMemLog( (long int) (&p->item), sizeof(Ocorrencia), 0);

                idf = log(numeroDeDocumentos/documentos->getTamanho());
                escreveMemLog( (long int) (&idf), sizeof(double), 5);
                leMemLog( (long int) (&numeroDeDocumentos), sizeof(double), 5);
                leMemLog( (long int) (&documentos), sizeof(double), 5);

                int tf;
                tf = p->item.frequencia;
                escreveMemLog( (long int) (&tf), sizeof(int), 0);
                leMemLog( (long int) (&p->item.frequencia), sizeof(int), 0);

                int idDocumento;
                idDocumento = ocorrencia.documento;
                escreveMemLog( (long int) (&idDocumento), sizeof(int), 0);
                leMemLog( (long int) (&ocorrencia.documento), sizeof(int), 0);

                resultados[idDocumento].resultado += tf * idf;
                escreveMemLog( (long int) (&resultados[idDocumento].resultado), sizeof(double), 5);
                leMemLog( (long int) (&tf), sizeof(double), 5);
                leMemLog( (long int) (&idf), sizeof(double), 5);

                resultados[idDocumento].id = idDocumento; 
                escreveMemLog( (long int) (&resultados[idDocumento].id), sizeof(int), 0);
                leMemLog( (long int) (&idDocumento), sizeof(int), 0);
                
                p = p->prox;
                escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia *), 0);
                leMemLog( (long int) (&p->prox), sizeof(CelulaListaOcorrencia *), 0);
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
        escreveMemLog( (long int) (&resultados[i].resultado), sizeof(double), 5);
        leMemLog( (long int) (&normasDocumentos[i]), sizeof(double), 5);
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
        leMemLog( (long int) (&resultados[i].id), sizeof(string), 0);

        numeroDeImpressoes--;
        if (numeroDeImpressoes == 0) {
            break;
        }        
    }
    arquivoSaida << endl;
    arquivoSaida.close();
}