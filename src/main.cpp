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
#include <stdio.h>
#include <memlog.hpp>
#include <string.h>
#include <fstream>
#include <experimental/filesystem>
#include <regex>
#include <vocabulario.hpp>

using namespace std;

namespace fs = experimental::filesystem;
using namespace fs;

// variaveis globais para opcoes
int regmem;
string nomeArquivoConsultas, nomeArquivoSaida, nomePastaCorpus, nomeArquivoStopwords, nomeArquivoLog;

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

int processaDocumento(string nomeDocumento){
    ifstream documento;
    documento.open(nomeDocumento);
    int contadorDeTermos = 0;
    // regex para identificar nome do arquivo 
    // matches: [0] = nome do arquivo inteiro, [1] = /xxxx/xxxx (caminho), [2] = .xxx (extensão)

    smatch matches;
    regex regexNomeDoArquivo("(\\.*)([-\\/A-Za-z0-9]*)(.[a-z]*)");
    regex_match(nomeDocumento, matches, regexNomeDoArquivo);
    
    string pontos = matches[1];
    string nomeDoArquivoSemExtensao = matches[2];
    string extensaoDoArquivo = matches[3];

    string nomeDocumentoProcessado = "";

    // adiciona o sufixo PROCESSADO ao nome do arquivo passado como parametro 
    nomeDocumentoProcessado.append(pontos).append(nomeDoArquivoSemExtensao).append("PROCESSADO").append(extensaoDoArquivo);
    
    ofstream documentoProcessado;
    documentoProcessado.open(nomeDocumentoProcessado);

    while(!documento.eof()){
        string termo;
        documento >> termo;
        
        for (int i = 0; i < termo.size(); i++){
            if(!isalpha(termo[i])) {
                if(termo[i] == '\\' and termo[i + 1] == 'n') {
                    termo.replace(termo.begin() + i, termo.begin() + i + 2, " ");
                    contadorDeTermos++;
                }
                else{
                    termo.replace(termo.begin() + i, termo.begin() + i + 1, " ");
                }
            }
            else if(isalpha(termo[i])) {
                termo[i] = tolower(termo[i]);
            }
        }
        documentoProcessado << termo << " ";   
        contadorDeTermos++;
    }
    
    remove(nomeDocumento);
    rename(nomeDocumentoProcessado, nomeDocumento);

    return contadorDeTermos;
}

bool eStopword(string palavra, string nomeArquivoStopwords)
// Descricao: retorna se palavra é stopword ou não
// Entrada: palavra
// Saida: bool
{
    ifstream arquivoDeStopwords;
    arquivoDeStopwords.open(nomeArquivoStopwords);
    erroAssert(arquivoDeStopwords.is_open(), "Arquivo de stopwords não foi aberto.");

    while (!arquivoDeStopwords.eof()) {
        string stopword;

        arquivoDeStopwords >> stopword;

        if (stopword == palavra){
            return true;
        }
        else {
            continue;
        }
    }
    return false;   
}

void criaIndice(string nomePastaCorpus, string nomeArquivoStopwords){
    string caminhoDocumento;
    int contadorDeTermos = 0;
    // conta o número de termos
    for(const auto & arquivo : fs::directory_iterator(nomePastaCorpus)) {
        processaDocumento(arquivo.path());
    }
        
        
    //     // conta termos
    //     ifstream documento;
    //     documento.open(arquivo.path());
    //     erroAssert(documento.is_open(), "Documento não foi aberto.");
        
    //     while (!documento.eof()) {
    //         string termoBruto;
    //         documento >> termoBruto;
            
    //         smatch matches;
    //         regex regexComando("(\\n)*([A-Za-z]*)");
    //         regex_match(termoBruto, matches, regexComando);
    //         string termo = matches[2];           
    //         contadorDeTermos++;
    //     }
    //     documento.close();

    //     documento.open(arquivo.path());
    //     erroAssert(documento.is_open(), "Documento não foi aberto.");
        
    //     Vocabulario vocabulario = Vocabulario(contadorDeTermos);

    //     while (!documento.eof()) {
    //         string termoBruto;
    //         documento >> termoBruto;

    //         cerr << termoBruto << " | " << matches[0] << " | " << matches[1] << " | " << matches[2] << endl;
    //         string termo = matches[2];
    //         for (long unsigned int i = 0; i < termo.size(); i++){
    //             termo[i] = tolower(termo[i]);
    //         }

    //         if (eStopword(termo, nomeArquivoStopwords)) {
    //             continue;
    //         }
    //         else {
    //             vocabulario.adicionaTermoVocabulario(termo);
    //         }
                      

    //     }

    //     // for (int i = 0; i < vocabulario.getTamanhoVocabulario(); i++){
    //     //     cout << vocabulario.vetorDeTermos[i].termo << " " << vocabulario.vetorDeTermos[i].frequencia << endl;
    //     // }
        
    //     break;
    //     documento.close();
    // }
}

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
    fprintf(stderr,"main\n");
    fprintf(stderr,"\t-i \t(arquivo com consultas) \n");
    fprintf(stderr,"\t-o \t(arquivo de saída) \n");
    fprintf(stderr,"\t-c \t(pasta com documentos) \n");
    fprintf(stderr,"\t-s \t(arquivo com stopwords) \n");
    fprintf(stderr,"\t-p \t(registro de desempenho)\n");
    fprintf(stderr,"\t-l \t(padrao de acesso e localidade)\n");
}

void parse_args(int argc, char ** argv)
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
                    uso();
                    exit(1);
        }

        // verificação de existência dos nomes dos arquivos obrigatórios
        // erroAssert(nomeArquivoConsultas.length() > 0, "main - Nome do arquivo de consultas tem que ser definido.");
        // erroAssert(nomeArquivoSaida.length() > 0, "main - Nome do arquivo de saída tem que ser definido.");
        erroAssert(nomePastaCorpus.length() > 0, "main - Nome da pasta do corpus tem que ser definido.");
        // erroAssert(nomeArquivoStopwords.length() > 0, "main - Nome do arquivo de stopwords tem que ser definido.");
        // erroAssert(nomeArquivoLog.length() > 0, "main - Nome do arquivo de log tem que ser definido.");
}

int main(int argc, char ** argv)
// Descricao: programa principal 
// Entrada: argc e argv
// Saida: int
{
    // avaliar linha de comando
    parse_args(argc, argv);

    // iniciaMemLog((char *) nomeArquivoLog.c_str());

    // ativar registro de acesso
    if (regmem == 1){
        ativaMemLog();
    }
    else desativaMemLog();

    criaIndice(nomePastaCorpus, nomeArquivoStopwords);

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