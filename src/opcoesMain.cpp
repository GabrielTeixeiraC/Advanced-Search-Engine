//---------------------------------------------------------------------
// Arquivo	: opcoesMain.cpp
// Conteudo	: implementacao do opcoesMain
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <getopt.h>
#include "opcoesMain.hpp"
#include "msgassert.hpp"

using namespace std;

void OpcoesMain::uso() 
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
    cerr << "main\n";
    cerr << "\t-i \t(arquivo com consultas) \n";
    cerr << "\t-o \t(arquivo de saída) \n";
    cerr << "\t-c \t(pasta com documentos) \n";
    cerr << "\t-s \t(arquivo com stopwords) \n";
    cerr << "\t-p \t(registro de desempenho)\n";
    cerr << "\t-l \t(padrao de acesso e localidade)\n";
}

void OpcoesMain::parse_args(int argc, char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: -
{
    // variaveis externas do getopt
    extern char * optarg;

    // variavel auxiliar
    int comando;

    // inicializacao variaveis globais para opcoes
    regmem = 0;
    nomeArquivoConsultas = "";
    nomeArquivoSaida = "";
    nomeArquivoLog = "";
    nomePastaCorpus = "";
    nomeArquivoStopwords = "";

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((comando = getopt(argc, argv, "i:o:c:s:p:l")) != EOF)
        switch(comando) {
            case 'i':
                nomeArquivoSaida = optarg;
                break;
            case 'o':
                nomeArquivoSaida = optarg;
                break;
            case 'c':
                nomePastaCorpus = optarg;
                break;
            case 's':
                nomeArquivoStopwords = optarg;
                break;
            case 'p': 
	            nomeArquivoLog = optarg;
		        break;
            case 'l': 
                regmem = 1;
		        break;
            case 'h':
                default:
                    this->uso();
                    exit(1);
        }

        // verificação de existência dos nomes dos arquivos obrigatórios
        // erroAssert(nomeArquivoConsultas.length() > 0, "main - Nome do arquivo de consultas tem que ser definido.");
        // erroAssert(nomeArquivoSaida.length() > 0, "main - Nome do arquivo de saída tem que ser definido.");
        erroAssert(nomePastaCorpus.length() > 0, "main - Nome da pasta do corpus tem que ser definido.");
        erroAssert(nomeArquivoStopwords.length() > 0, "main - Nome do arquivo de stopwords tem que ser definido.");
        // erroAssert(nomeArquivoLog.length() > 0, "main - Nome do arquivo de log tem que ser definido.");
}