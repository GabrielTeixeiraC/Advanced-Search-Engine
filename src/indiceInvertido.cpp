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
#include "ocorrencia.hpp"

namespace fs = experimental::filesystem;
using namespace fs;

IndiceInvertido::IndiceInvertido(int tamanhoMaximoIndice){
    this->tamanhoMaximoIndice = tamanhoMaximoIndice;

    indiceTabela = new ListaEncadeadaTermoIndice[tamanhoMaximoIndice];
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

void IndiceInvertido::insere(string termo, Ocorrencia ocorrencia) {
    int posicao;
    long long hash;
    hash = calculaHash(termo);

    posicao = hash % tamanhoMaximoIndice;

    CelulaListaTermoIndice* p = new CelulaListaTermoIndice();
    p = indiceTabela[posicao].primeiro->prox;
    for (int i = 0; i < indiceTabela[posicao].getTamanho(); i++) {
        if (p->item.termo == termo) {    
            p->item.ocorrencias->insereFinal(ocorrencia);
            return;
        }
        else {
            p = p->prox;
        }
    }
    TermoIndice aux;
    aux.termo = termo;
    aux.ocorrencias->insereFinal(ocorrencia);
    this->indiceTabela[posicao].insereFinal(aux);
}

void IndiceInvertido::pesquisa(string termo, ListaEncadeadaOcorrencia * documentos) {
    int posicao;
    long long hash;

    hash = calculaHash(termo);
    posicao = hash % tamanhoMaximoIndice;

    if (indiceTabela[posicao].getTamanho() == 0) {
        avisoAssert(indiceTabela[posicao].getTamanho() > 0, "Erro: Palavra não está presente nos documentos.");
    }
    else {
        CelulaListaTermoIndice * p = new CelulaListaTermoIndice();
        p = indiceTabela[posicao].primeiro->prox;
        while (p != NULL) {
            if (p->item.termo == termo) {
                *(documentos) = *(p->item.ocorrencias);
                return;
            }
            p = p->prox;
        }
        documentos = new ListaEncadeadaOcorrencia();
        delete p;
    }
}

void IndiceInvertido::criaIndice(string nomePastaCorpus, string nomeArquivoStopwords, ProcessadorDeDocumentos * processador, Resultado * resultados) {
    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        int tamanhoMaximoVocabularioDocumento;
        fs::path caminho = arquivo;
        string nomeDocumento = arquivo.path();

        unsigned long idDocumento = stoul(caminho.stem());
        
        resultados[idDocumento].id = idDocumento;

        tamanhoMaximoVocabularioDocumento = processador->contaNumeroDeTermos(nomeDocumento);
        Vocabulario vocabulario = Vocabulario(tamanhoMaximoVocabularioDocumento, nomeArquivoStopwords);
  
        vocabulario.criaVocabularioDocumento(nomeDocumento);

        for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++){
            string termo = vocabulario.vetorDeTermos[i].termo;
            
            Ocorrencia ocorrencia;
            
            ocorrencia.documento = idDocumento;
            ocorrencia.frequencia = vocabulario.vetorDeTermos[i].frequencia;
            
            this->insere(termo, ocorrencia);
        }
        
        vocabulario.desaloca();

    }
}

void IndiceInvertido::desaloca() {
    delete[] this->indiceTabela;
}