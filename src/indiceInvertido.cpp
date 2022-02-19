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

IndiceInvertido::IndiceInvertido(int tamanhoMaximoIndice){
    this->tamanhoMaximoIndice = tamanhoMaximoIndice;

    indiceInvertido = new ListaEncadeada[tamanhoMaximoIndice];
}


long long IndiceInvertido::calculaHash(string termo) {
    int primo = 31;
    int modulo = 1e9 + 9;
    long long valorHash = 0;
    long long potenciaDoPrimo = 1;
    for (long unsigned int i = 0; i < termo.size(); i++) {
        valorHash = (valorHash + (termo[i] - 'a' + 1) * potenciaDoPrimo) % modulo;
        potenciaDoPrimo = (potenciaDoPrimo * primo) % modulo;
    }
    return valorHash % tamanhoMaximoIndice;
}

void IndiceInvertido::Insere(string termo, TermoIndice item) {
    int posicao;

    posicao = calculaHash(termo);
    indiceInvertido[posicao].insereFinal(item);
}

ListaEncadeada IndiceInvertido::Pesquisa(string termo) {
    int pos;
    ListaEncadeada item;

    pos = calculaHash(termo);
    if (indiceInvertido[pos].getTamanho() == 0) {
        avisoAssert(indiceInvertido[pos].getTamanho() > 0, "Erro: Palavra não está presente nos documentos.");
    }
    else{
        item = indiceInvertido[pos];
    }
    return item;

}


void IndiceInvertido::criaIndice(string nomePastaCorpus, string nomeArquivoStopwords){
    ProcessadorDeDocumentos processador;

    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        int tamanhoVocabularioDocumento;
        tamanhoVocabularioDocumento = processador.contaNumeroDeTermos(arquivo.path());
        Vocabulario vocabulario = Vocabulario(tamanhoVocabularioDocumento);
  
        vocabulario.criaVocabularioDocumento(arquivo.path(), nomeArquivoStopwords);

        for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++){
            cout << vocabulario.vetorDeTermos[i].termo << " " << vocabulario.vetorDeTermos[i].frequencia << endl;
        }
        cout << "-----------------------------" << endl;
    }
}

void IndiceInvertido::desaloca() {
    delete[] this->indiceInvertido;
}