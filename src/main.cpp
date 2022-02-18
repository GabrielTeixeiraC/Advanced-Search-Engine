//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: arquivo principal do programa 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-17 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include <getopt.h>
#include <msgassert.hpp>
#include "processadorDeDocumentos.hpp"
#include <stdio.h>
#include "memlog.hpp"
#include <string.h>
#include <fstream>
#include <experimental/filesystem>
#include <regex>
#include "vocabulario.hpp"
#include "opcoesMain.hpp"

using namespace std;

namespace fs = experimental::filesystem;
using namespace fs;

// long long calculaHash(string termo) {
//     int primo = 31;
//     int modulo = 1e9 + 9;
//     long long valorHash = 0;
//     long long potenciaDoPrimo = 1;
//     for (int i = 0; i < termo.length(); i++) {
//         valorHash = (valorHash + (termo[i] - 'a' + 1) * potenciaDoPrimo) % modulo;
//         potenciaDoPrimo = (potenciaDoPrimo * primo) % modulo;
//     }
//     return valorHash;
// }

void criaIndice(string nomePastaCorpus, string nomeArquivoStopwords){
    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        ProcessadorDeDocumentos processador;

        int tamanhoMaximoVocabulario = processador.processaDocumento(arquivo.path());

        ifstream documento;
        documento.open(arquivo.path());
        erroAssert(documento.is_open(), "Documento não foi aberto.");
        
        Vocabulario vocabulario = Vocabulario(tamanhoMaximoVocabulario);

        while (!documento.eof()) {
            string termo;
            documento >> termo;
            if(!documento.good()) {
                break;
            }

            if (processador.eStopword(termo, nomeArquivoStopwords)) {
                continue;
            }
            else {
                vocabulario.adicionaTermoVocabulario(termo);
            }
                      
        }

        for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++){
            cout << vocabulario.vetorDeTermos[i].termo << " " << vocabulario.vetorDeTermos[i].frequencia << endl;
        }
        cout << "-----------------------------" << endl;
        documento.close();
    }
}


int main(int argc, char ** argv)
// Descricao: programa principal 
// Entrada: argc e argv
// Saida: int
{
    OpcoesMain opcoes;

    // avaliar linha de comando
    opcoes.parse_args(argc, argv);

    // iniciaMemLog((char *) nomeArquivoLog.c_str());

    // ativar registro de acesso
    if (opcoes.regmem == 1){
        ativaMemLog();
    }
    else desativaMemLog();

    criaIndice(opcoes.nomePastaCorpus, opcoes.nomeArquivoStopwords);

    // // abre arquivo de resultado
    // ofstream arquivoSaida;
    // arquivoSaida.open(nomeArquivoSaida);
    // erroAssert(arquivoSaida.is_open(), "Arquivo de saída não foi aberto.");
    


    // // fecha arquivo de saída
    // arquivoSaida.close();

    // // conclui registro de acesso
    // finalizaMemLog();  
    return 0;
}