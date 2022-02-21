//---------------------------------------------------------------------
// Arquivo	: indiceInvertido.cpp
// Conteudo	: implementacao do indiceInvertido
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <regex>
#include <experimental/filesystem>
#include "indiceInvertido.hpp"
#include "processadorDeDocumentos.hpp"
#include "msgassert.hpp"
#include "vocabulario.hpp"

namespace fs = experimental::filesystem;
using namespace fs;

IndiceInvertido::IndiceInvertido(int tamanhoMaximoIndice){
    this->tamanhoMaximoIndice = tamanhoMaximoIndice;

    indiceTabela = new ListaEncadeada[tamanhoMaximoIndice];
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
    return valorHash;
}

void IndiceInvertido::insere(string termo, TermoIndice item) {
    int posicao;
    long long hash;
    hash = calculaHash(termo);

    posicao = hash % tamanhoMaximoIndice;
    
    indiceTabela[posicao].insereFinal(item);
}

void IndiceInvertido::pesquisa(string termo, ListaEncadeada * documentos) {
    int posicao;
    long long hash;
    ListaEncadeada * listaComColisoes = new ListaEncadeada();
    ListaEncadeada * listaSemColisoes = new ListaEncadeada();

    hash = calculaHash(termo);
    posicao = hash % tamanhoMaximoIndice;
    if (indiceTabela[posicao].getTamanho() == 0) {
        avisoAssert(indiceTabela[posicao].getTamanho() > 0, "Erro: Palavra não está presente nos documentos.");
    }
    else {
        listaComColisoes = &(indiceTabela[posicao]);
        for (int i = 1; i <= listaComColisoes->getTamanho(); i++) {
            TermoIndice itemCelula;
            itemCelula = listaComColisoes->getItem(i);
            if (itemCelula.termo == termo) {
                listaSemColisoes->insereFinal(itemCelula);
            }
            else {
                continue;
            }
        }        
    }
    *(documentos) = *(listaSemColisoes);
}


void IndiceInvertido::criaIndice(string nomePastaCorpus, string nomeArquivoStopwords, ProcessadorDeDocumentos * processador) {
    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        int tamanhoMaximoVocabularioDocumento;
        string nomeDocumento = arquivo.path();
        tamanhoMaximoVocabularioDocumento = processador->contaNumeroDeTermos(nomeDocumento);
        Vocabulario vocabulario = Vocabulario(tamanhoMaximoVocabularioDocumento, nomeArquivoStopwords);
  
        vocabulario.criaVocabularioDocumento(nomeDocumento);
        // regex para identificar nome do arquivo 
        // matches: [0] = nome do arquivo inteiro, [1] = /xxxx/xxxx (caminho), [2] = .xxx (extensão)

        smatch matches;
        regex regexNomeDoArquivo(".*\\/([0-9]*)\\.[a-z]*");
        regex_match(nomeDocumento, matches, regexNomeDoArquivo);
        unsigned long idDocumento = stoul(matches[1]);

        for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++){
            TermoIndice aux;
            string termo = vocabulario.vetorDeTermos[i].termo;

            aux.termo = termo;
            aux.documento = idDocumento;
            aux.frequencia = vocabulario.vetorDeTermos[i].frequencia;

            this->insere(termo, aux);
        }

        // cout << "Documento " << idDocumento << endl;
        // for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++){
        //     cout << vocabulario.vetorDeTermos[i].termo << " " << vocabulario.vetorDeTermos[i].frequencia << endl;
        // }
        // cout << "-----------------------------" << endl;
    }
}

void IndiceInvertido::desaloca() {
    delete[] this->indiceTabela;
}