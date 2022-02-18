//---------------------------------------------------------------------
// Arquivo	: indiceInvertido.cpp
// Conteudo	: implementacao do indiceInvertido
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "indiceInvertido.hpp"
#include "processadorDeDocumentos.hpp"
#include "msgassert.hpp"
#include "vocabulario.hpp"

namespace fs = experimental::filesystem;
using namespace fs;

long long IndiceInvertido::calculaHash(string termo) {
    int primo = 31;
    int modulo = 1e9 + 9;
    long long valorHash = 0;
    long long potenciaDoPrimo = 1;
    for (long unsigned int i = 0; i < termo.size(); i++) {
        valorHash = (valorHash + (termo[i] - 'a' + 1) * potenciaDoPrimo) % modulo;
        potenciaDoPrimo = (potenciaDoPrimo * primo) % modulo;
    }
    return valorHash;
}

void IndiceInvertido::criaIndice(string nomePastaCorpus, string nomeArquivoStopwords){
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