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

    int tamanhoMaximoIndice = 0;

    ProcessadorDeDocumentos processador;
    processador.processaDocumento();



    // ativar registro de acesso
    if (opcoes.regmem == 1){
        ativaMemLog();
    }
    else desativaMemLog();

    IndiceInvertido indiceInvertido;

    indiceInvertido.criaIndice(opcoes.nomePastaCorpus, opcoes.nomeArquivoStopwords);

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