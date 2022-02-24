//---------------------------------------------------------------------
// Arquivo	: processadorDeDocumentos.cpp
// Conteudo	: implementacao do processadorDeDocumentos
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <regex>
#include <fstream>
#include <experimental/filesystem>
#include <stdio.h>
#include <cstdio>
#include "msgassert.hpp"
#include "processadorDeDocumentos.hpp"
#include "memlog.hpp"

namespace fs = experimental::filesystem;
using namespace fs;

// construtor do Processador de Documentos
ProcessadorDeDocumentos::ProcessadorDeDocumentos() 
{
    numeroDeDocumentos = 0;
    maiorIdDocumento = 0;
}

int ProcessadorDeDocumentos::contaNumeroDeTermos(string nomeDocumento)
// Descricao: conta o numero de termos em um documento e retorna para criar um vocabulario com espaço suficiente 
// Entrada: nomeDocumento
// Saida: numeroDeTermos
{
    // abre um documento
    ifstream documento;
    documento.open(nomeDocumento);
    erroAssert(documento.is_open(), "Documento não foi aberto.");
    
    // inicia um numero de termos como 5 para ter espaço garantido 
    int numeroDeTermos = 5;

    // soma o número de termos no documento
    while (!documento.eof()) {
        string termo;
        documento >> termo;

        numeroDeTermos++; 
    }

    documento.close();

    return numeroDeTermos;
}

int ProcessadorDeDocumentos::processaCorpus(string nomePastaCorpus)
// Descricao: processa o corpus, tratando as palavras, e retorna o tamanho maximo para o indice
// Entrada: nomePastaCorpus
// Saida: tamanhoMaximoIndice
{
    int tamanhoMaximoIndice = 0;
    int numeroDeDocumentosCorpus = 0;

    // itera sobre os documentos processando-os
    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        // pega o id do documento
        fs::path caminho = arquivo;
        int idDocumento = stoul(caminho.stem());
        
        // acha o maior id do documento, necessario para iterar sobre os vetores
        if (idDocumento > maiorIdDocumento) {
            maiorIdDocumento = idDocumento;
        }
        
        // processa o documento e aumenta o tamanho maximo do indice
        int tamanhoMaximoVocabulario = processaDocumento(arquivo.path());
        escreveMemLog( (long int) (&tamanhoMaximoVocabulario), sizeof(int), 0);

        tamanhoMaximoIndice += tamanhoMaximoVocabulario;
        numeroDeDocumentosCorpus++;
    }
    
    // atualiza o numero de documentos
    numeroDeDocumentos = numeroDeDocumentosCorpus;

    return tamanhoMaximoIndice; 
}

int ProcessadorDeDocumentos::processaDocumento(string nomeDocumento) 
// Descricao: processa um documento, tratando as strings e retornando o numero de termos
// Entrada: nomeDocumento
// Saida: contadorDeTermos
{
    // abre o documento
    ifstream documento;
    documento.open(nomeDocumento);
    erroAssert(documento.is_open(), "Documento não foi aberto.");

    int contadorDeTermos = 0;

    // regex para identificar nome do arquivo 
    // matches: [0] = nome do arquivo inteiro, [1] = .. ou ., [2] = /xxxx/xxxx (caminho), [3] = .xxx (extensão)
    smatch matches;
    regex regexNomeDoArquivo("(\\.*)([-\\/A-Za-z0-9]*)(.[a-z]*)");
    regex_match(nomeDocumento, matches, regexNomeDoArquivo);
    
    string pontos = matches[1];
    string nomeDoArquivoSemExtensao = matches[2];
    string extensaoDoArquivo = matches[3];

    string nomeDocumentoProcessado = "";

    // adiciona o sufixo PROCESSADO ao nome do arquivo passado como parametro 
    nomeDocumentoProcessado.append(pontos).append(nomeDoArquivoSemExtensao).append("PROCESSADO").append(extensaoDoArquivo);
    
    // abre arquivo de saída
    ofstream documentoProcessado;
    documentoProcessado.open(nomeDocumentoProcessado);
    erroAssert(documentoProcessado.is_open(), "Documento Processado não foi aberto.");

    // processa o documento e copia para o documento aberto
    while(!documento.eof()){
        string termo;
        documento >> termo;
        
        for (long unsigned int i = 0; i < termo.size(); i++){
            if(!isalpha(termo[i])) {
                if(termo[i] == '\\' and termo[i + 1] == 'n') {
                    termo[i] = ' ';
                    termo[i + 1] = ' ';
                    escreveMemLog( (long int) (&termo[i]), sizeof(char), 0);
                    escreveMemLog( (long int) (&termo[i + 1]), sizeof(char), 0);

                    contadorDeTermos++;
                }
                else{
                    termo[i] = ' ';
                    escreveMemLog( (long int) (&termo[i]), sizeof(char), 0);
                }
            }
            else if(isalpha(termo[i])) {
                termo[i] = tolower(termo[i]);
                escreveMemLog( (long int) (&termo[i]), sizeof(char), 0);
            }
        }

        documentoProcessado << termo << " ";   
        contadorDeTermos++;
    }
    // fecha o documento aberto
    documento.close();

    // remove o arquivo original e renomeia o arquivo novo para ter o nome original
    remove(nomeDocumento.c_str());
    rename(nomeDocumentoProcessado.c_str(), nomeDocumento.c_str());

    documentoProcessado.close();
    
    return contadorDeTermos;
}