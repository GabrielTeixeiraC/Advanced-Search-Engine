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

// construtor do indice invertido
IndiceInvertido::IndiceInvertido(int tamanhoMaximoIndice){
    this->tamanhoMaximoIndice = tamanhoMaximoIndice;

    indiceTabela = new ListaEncadeadaTermoIndice[tamanhoMaximoIndice];
}

long long IndiceInvertido::calculaHash(string termo) 
// Descricao: calcula o hash de uma string
// Entrada: termo
// Saida: valorHash
{   
    // primo maior que o alfabeto
    int primo = 31;
    // numero alto para tirar o resto
    int modulo = 1e9 + 9;
    long long valorHash = 0;
    long long potenciaDoPrimo = 1;
    // calcula o hash elevando o primo a uma potencia i, multiplicando pelo numero equivalente à letra e tirando o resto 
    for (long unsigned int i = 0; i < termo.size(); i++) {
        valorHash = (valorHash + (termo[i] - 'a' + 1) * potenciaDoPrimo) % modulo;
        potenciaDoPrimo = (potenciaDoPrimo * primo) % modulo;
    }
    return valorHash;
}

void IndiceInvertido::insere(string termo, Ocorrencia ocorrencia) 
// Descricao: insere um termo numa posicao do hash 
// Entrada: termo, ocorrencia
// Saida: -
{
    int posicao;
    long long hash;
    hash = calculaHash(termo);

    // tira o módulo para caber na tabela do hash;
    posicao = hash % tamanhoMaximoIndice;

    CelulaListaTermoIndice* p = new CelulaListaTermoIndice();
    p = indiceTabela[posicao].primeiro->prox;

    for (int i = 0; i < indiceTabela[posicao].getTamanho(); i++) {
        // se o termo passado for igual ao termo na celula, insere a ocorrencia no final da Lista de Ocorrencias 
        if (p->item.termo == termo) {    
            p->item.ocorrencias->insereFinal(ocorrencia);
            return;
        }
        else {
            p = p->prox;
        }
    }
    // se não achou, insere um TermoIndice no final da posicao da tabela de hash
    TermoIndice aux;
    aux.termo = termo;
    aux.ocorrencias->insereFinal(ocorrencia);
    this->indiceTabela[posicao].insereFinal(aux);
}

void IndiceInvertido::pesquisa(string termo, ListaEncadeadaOcorrencia * documentos) 
// Descricao: pesquisa as ocorrencias de um termo 
// Entrada: termo, documentos
// Saida: -
{
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
                // se termo na celula for igual ao termo passado, copia os elementos da celula para o ponteiro passado como parametro
                *(documentos) = *(p->item.ocorrencias);
                return;
            }
            p = p->prox;
        }
        // senao, cria uma listaEncadeada nova para documentos
        documentos = new ListaEncadeadaOcorrencia();
        delete p;
    }
}

void IndiceInvertido::criaIndice(string nomePastaCorpus, string nomeArquivoStopwords, ProcessadorDeDocumentos * processador, Resultado * resultados) 
// Descricao: cria o indice invertido
// Entrada: nomePastaCorpus, nomeArquivoStopwords, processador, resultados
// Saida: -
{
    // itera sobre os arquivos
    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        int tamanhoMaximoVocabularioDocumento;
        // pega o nome do arquivo e o id do documento
        fs::path caminho = arquivo;
        string nomeDocumento = arquivo.path();
        unsigned long idDocumento = stoul(caminho.stem());

        // define os ids do vetor de resultados
        resultados[idDocumento].id = idDocumento;

        // cria um vocabulario do documento
        tamanhoMaximoVocabularioDocumento = processador->contaNumeroDeTermos(nomeDocumento);
        Vocabulario vocabulario = Vocabulario(tamanhoMaximoVocabularioDocumento, nomeArquivoStopwords);
        vocabulario.criaVocabularioDocumento(nomeDocumento);

        // para cada termo do vocabulario, insere sua ocorrencia no indice invertido
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

void IndiceInvertido::desaloca() 
// Descricao: desaloca a memória do indice invertido 
// Entrada: -
// Saida: -
{
    delete[] this->indiceTabela;
}