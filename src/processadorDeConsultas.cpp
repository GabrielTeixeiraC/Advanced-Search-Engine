//---------------------------------------------------------------------
// Arquivo	: processadorDeConsultas.cpp
// Conteudo	: implementacao do ProcessadorDeConsultas
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <experimental/filesystem>
#include <regex>
#include "processadorDeConsultas.hpp"
#include "processadorDeDocumentos.hpp"
#include "indiceInvertido.hpp"
#include "vocabulario.hpp"
#include "msgassert.hpp"

namespace fs = experimental::filesystem;
using namespace fs;

struct Resultado
{
    double resultado = 1;
    int id;
};

ProcessadorDeConsultas::ProcessadorDeConsultas(int numeroDeDocumentos, IndiceInvertido * indiceInvertido, ProcessadorDeDocumentos * processador) {
    this->indiceInvertido = indiceInvertido;
    this->processador = processador;
    this->numeroDeDocumentos = numeroDeDocumentos;
    normasDocumentos = new double[numeroDeDocumentos];
    maiorIdDocumento = 0;
}


void ProcessadorDeConsultas::calculaNormaDocumentos() {
    for (int i = 0; i < indiceInvertido->tamanhoMaximoIndice; i++) {
        ListaEncadeada aux = indiceInvertido->indiceTabela[i];
        TermoIndice tmp = aux.getItem(j);
        for (int j = 1; j <= aux.getTamanho(); j++) {
            if ()
            {
                /* code */
            }
            
            int contador = 0;
            

        }
        
        
    }
    

        if (idDocumento > maiorIdDocumento) {
            maiorIdDocumento = idDocumento;
        }

        double idf = 0;
        for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++) {
            int tf;

            ListaEncadeada * documentos = new ListaEncadeada();
            string termo = vocabulario.vetorDeTermos[i].termo;
            indiceInvertido->pesquisa(termo, documentos);   
            if (documentos->getTamanho() == 0) {
                continue;
            }
            

            idf = log(numeroDeDocumentos/documentos->getTamanho());
            tf = vocabulario.vetorDeTermos[i].frequencia;

            double tfidf = tf * idf;
            
            normasDocumentos[idDocumento] = sqrt(tfidf * tfidf);

        }
    }
}

bool compara(Resultado a, Resultado b) {
    return a.resultado > b.resultado;
}

bool compara2(Resultado a, Resultado b) {
    return a.id < b.id;
}


void ProcessadorDeConsultas::processaConsulta(string nomeArquivoConsulta, string nomeArquivoStopwords) {
    ifstream arquivoConsultas;
    arquivoConsultas.open(nomeArquivoConsulta);
    erroAssert(arquivoConsultas.is_open(), "Documento não foi aberto.");

    Resultado resultado[maiorIdDocumento] = {};

    bool somou = false;

    while (!arquivoConsultas.eof()){
        string termo;
        arquivoConsultas >> termo;

        if (!arquivoConsultas.good()) {
            break;
        }
        
        ListaEncadeada * documentos = new ListaEncadeada();
        indiceInvertido->pesquisa(termo, documentos);   

        double idf;

        if (documentos->getTamanho() > 0) {
            idf = log(numeroDeDocumentos/documentos->getTamanho());
            for (int i = 1; i <= documentos->getTamanho(); i++) {
                int tf;
                tf = documentos->getItem(i).frequencia;
                
                int idDocumento;
                idDocumento = documentos->getItem(i).documento;

                resultado[idDocumento].resultado += tf * idf;
                resultado[idDocumento].id = idDocumento; 
            }
            somou = true;
        }
        else {
            continue;
        }

        for (int i = 0; i < numeroDeDocumentos; i++) {
            resultado[i].resultado /= normasDocumentos[i];
        }
        
    }

    sort(resultado, resultado + maiorIdDocumento, compara);

    if(somou) {
        for (int i = 0; i < 10; i++) {
            cout << "ID: "<< resultado[i].id << " " << "Resultado: " << resultado[i].resultado << endl;
        }
        cout << endl;
    }
    else {
        avisoAssert(somou, "Nenhum termo foi somado.");
    }

    arquivoConsultas.close();
}
