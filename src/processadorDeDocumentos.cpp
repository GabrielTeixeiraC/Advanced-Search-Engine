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

int ProcessadorDeDocumentos::processaDocumento(string nomeDocumento) {
    ifstream documento;
    documento.open(nomeDocumento);
    erroAssert(documento.is_open(), "Documento não foi aberto.");

    int contadorDeTermos = 0;
    // regex para identificar nome do arquivo 
    // matches: [0] = nome do arquivo inteiro, [1] = /xxxx/xxxx (caminho), [2] = .xxx (extensão)

    smatch matches;
    regex regexNomeDoArquivo("(\\.*)([-\\/A-Za-z0-9]*)(.[a-z]*)");
    regex_match(nomeDocumento, matches, regexNomeDoArquivo);
    
    string pontos = matches[1];
    string nomeDoArquivoSemExtensao = matches[2];
    string extensaoDoArquivo = matches[3];

    string nomeDocumentoProcessado = "";

    // adiciona o sufixo PROCESSADO ao nome do arquivo passado como parametro 
    nomeDocumentoProcessado.append(pontos).append(nomeDoArquivoSemExtensao).append("PROCESSADO").append(extensaoDoArquivo);
    
    ofstream documentoProcessado;
    documentoProcessado.open(nomeDocumentoProcessado);
    erroAssert(documentoProcessado.is_open(), "Documento Processado não foi aberto.");

    while(!documento.eof()){
        string termo;
        documento >> termo;
        
        for (long unsigned int i = 0; i < termo.size(); i++){
            if(!isalpha(termo[i])) {
                if(termo[i] == '\\' and termo[i + 1] == 'n') {
                    termo.replace(termo.begin() + i, termo.begin() + i + 2, " ");
                    contadorDeTermos++;
                }
                else{
                    termo.replace(termo.begin() + i, termo.begin() + i + 1, " ");
                }
            }
            else if(isalpha(termo[i])) {
                termo[i] = tolower(termo[i]);
            }
        }
        documentoProcessado << termo << " ";   
        contadorDeTermos++;
    }
    documento.close();
    remove(nomeDocumento.c_str());
    rename(nomeDocumentoProcessado.c_str(), nomeDocumento.c_str());

    documentoProcessado.close();
    
    return contadorDeTermos;
}

bool ProcessadorDeDocumentos::eStopword(string palavra, string nomeArquivoStopwords) {
// Descricao: retorna se palavra é stopword ou não
// Entrada: palavra
// Saida: bool
{
    ifstream arquivoDeStopwords;
    arquivoDeStopwords.open(nomeArquivoStopwords);
    erroAssert(arquivoDeStopwords.is_open(), "Arquivo de stopwords não foi aberto.");
    
    while (!arquivoDeStopwords.eof()) {
        string stopword;

        arquivoDeStopwords >> stopword;

        if (stopword == palavra){
            return true;
        }
        else {
            continue;
        }
    }
    return false;   
}
}