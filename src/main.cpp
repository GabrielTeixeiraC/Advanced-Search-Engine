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
#include "resultado.hpp"
#include "memlog.hpp"
#include "processadorDeConsultas.hpp"

using namespace std;

int main(int argc, char ** argv)
// Descricao: programa principal 
// Entrada: argc e argv
// Saida: int
{
    // objeto que avalia a linha de comando
    OpcoesMain opcoes;

    // avaliar linha de comando
    opcoes.parse_args(argc, argv);

    // inicia log de acesso à memória
    iniciaMemLog((char *) opcoes.nomeArquivoLog.c_str());

    // ativar registro de acesso
    if (opcoes.regmem == 1){
        ativaMemLog();
    }
    else desativaMemLog();

    int tamanhoMaximoIndice;

    ProcessadorDeDocumentos * processador = new ProcessadorDeDocumentos();

    cout << "Processando Corpus." << endl;
    tamanhoMaximoIndice = processador->processaCorpus(opcoes.nomePastaCorpus);
    
    Resultado * resultados = new Resultado[processador->maiorIdDocumento + 1] {};

    IndiceInvertido * indiceInvertido = new IndiceInvertido(tamanhoMaximoIndice);
    
    cout << "Criando Indice Invertido." << endl;
    indiceInvertido->criaIndice(opcoes.nomePastaCorpus, opcoes.nomeArquivoStopwords, processador, resultados);

    ProcessadorDeConsultas processadorDeConsultas = ProcessadorDeConsultas(processador->numeroDeDocumentos, indiceInvertido, processador, resultados);
    
    cout << "Calculando Norma dos Documentos." << endl;
    processadorDeConsultas.calculaNormaDocumentos();
    
    cout << "Processando Consultas." << endl;
    processadorDeConsultas.processaConsulta(opcoes.nomeArquivoConsultas, opcoes.nomeArquivoStopwords);

    cout << "Ordenando Resultados." << endl;
    processadorDeConsultas.ordenaResultados();

    cout << "Imprimindo Resultados." << endl;
    processadorDeConsultas.imprimeResultados(opcoes.nomeArquivoSaida);

    // deleta os objetos alocados dinamicamente
    delete processador;
    delete resultados;
    indiceInvertido->desaloca();

    // conclui registro de acesso
    finalizaMemLog();  
    return 0;
}