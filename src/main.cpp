//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: arquivo principal do programa 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-17 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include <msgassert.hpp>
#include <fstream>
#include "opcoesMain.hpp"
#include "processadorDeDocumentos.hpp"
#include "indiceInvertido.hpp"
#include "vocabulario.hpp"
#include "memlog.hpp"
#include "processadorDeConsultas.hpp"

using namespace std;

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

    int tamanhoMaximoIndice;

    ProcessadorDeDocumentos * processador = new ProcessadorDeDocumentos();
    tamanhoMaximoIndice = processador->processaCorpus(opcoes.nomePastaCorpus);
    
    IndiceInvertido * indiceInvertido = new IndiceInvertido(tamanhoMaximoIndice);
    indiceInvertido->criaIndice(opcoes.nomePastaCorpus, opcoes.nomeArquivoStopwords, processador);

    string termo;
    ProcessadorDeConsultas processadorDeConsultas = ProcessadorDeConsultas(processador->numeroDeDocumentos, indiceInvertido, processador);
    processadorDeConsultas.calculaNormaDocumentos(opcoes.nomePastaCorpus, opcoes.nomeArquivoStopwords);
    processadorDeConsultas.processaConsulta(opcoes.nomeArquivoConsultas, opcoes.nomeArquivoStopwords);










    while (cin){
        ListaEncadeada * aux = new ListaEncadeada();
        cin >> termo;
        indiceInvertido->pesquisa(termo, aux);
        for (int i = 1; i <= aux->getTamanho(); i++) {
            cerr << aux->getItem(i).documento << " " << aux->getItem(i).frequencia << endl;
        }
    
    }
    double contador = 0;
    for (int i = 0; i < tamanhoMaximoIndice; i++) {
        if (indiceInvertido->indiceTabela[i].getTamanho() > 0) {
            contador++;
        }
    }

    double porcentagem = contador/tamanhoMaximoIndice;

    cout << "Porcentagem: " << porcentagem * 100 << "%" << endl;

    
    
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