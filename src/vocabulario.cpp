//---------------------------------------------------------------------
// Arquivo	: vocabulario.cpp
// Conteudo	: implementacao do vocabulario
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <fstream>
#include "vocabulario.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

// Construtor de Vocabulario
Vocabulario::Vocabulario(int tamanhoMaximoVocabulario, string nomeArquivoStopwords) 
{
    this->nomeArquivoStopwords = nomeArquivoStopwords;
    tamanhoVocabulario = 0;
    vetorDeTermos = new TermoVocabulario[tamanhoMaximoVocabulario];
}

void Vocabulario::desaloca() 
// Descricao: desaloca o vocabulario 
// Entrada: -
// Saida: -
{
    delete[] this->vetorDeTermos;
}

int Vocabulario::posicaoTermoNoVocabulario(string termo) 
// Descricao: retorna a posicao de um termo no vocabulario ou -1 se não existir 
// Entrada: termo
// Saida: posicao i
{
    for (int i = 0; i < tamanhoVocabulario; i++) {
        if (vetorDeTermos[i].termo == termo) {
            return i;
        }
        else {
            continue;
        }
    }
    // retorna -1 se não achar o termo no vocabulario
    return -1;
}

void Vocabulario::adicionaTermoVocabulario(string termo) 
// Descricao: adiciona um termo no vocabulario, aumentando a frequencia se já existir 
// Entrada: termo
// Saida: -
{
    // acha a posicao do termo no vocabulario
    int posicaoTermo = posicaoTermoNoVocabulario(termo);
    escreveMemLog( (long int) (&posicaoTermo), sizeof(int), 1);

    // se o termo está no vocabulario, aumenta sua frequencia
    if (posicaoTermo >= 0) {
        vetorDeTermos[posicaoTermo].frequencia++;
    }
    // senao, coloca o termo no final do vocabulario e aumenta sua frequencia
    else {
        vetorDeTermos[tamanhoVocabulario].termo = termo;
        escreveMemLog( (long int) (&vetorDeTermos[tamanhoVocabulario].termo), sizeof(string), 1);
        leMemLog( (long int) (&vetorDeTermos[tamanhoVocabulario].termo), sizeof(string), 1);

        vetorDeTermos[tamanhoVocabulario].frequencia++;
        escreveMemLog( (long int) (&vetorDeTermos[tamanhoVocabulario].frequencia), sizeof(int), 1);
        leMemLog( (long int) (&vetorDeTermos[tamanhoVocabulario].frequencia), sizeof(int), 1);

        tamanhoVocabulario++;
    }
}

int Vocabulario::getTamanhoVocabulario() 
// Descricao: retorna o tamanho do vocabulario 
// Entrada: -
// Saida: tamanhoVocabulario
{
    return tamanhoVocabulario;
}

bool Vocabulario::eStopword(string palavra)
// Descricao: retorna se palavra é stopword ou não
// Entrada: palavra
// Saida: bool
{
    // abre arquivo de stopwords
    ifstream arquivoDeStopwords;
    arquivoDeStopwords.open(nomeArquivoStopwords);
    erroAssert(arquivoDeStopwords.is_open(), "Arquivo de stopwords não foi aberto.");
    
    // checa se a palavra passada como parametro é uma stopword
    while (!arquivoDeStopwords.eof()) {
        string stopword;

        arquivoDeStopwords >> stopword;

        // se achar, retorna true
        if (stopword == palavra){
            return true;
        }
        else {
            continue;
        }
    }
    arquivoDeStopwords.close();

    // se não achou, retorna false
    return false;
}

void Vocabulario::criaVocabularioDocumento(string nomeDocumento) 
// Descricao: cria um vocabulario de um documento 
// Entrada: nomeDocumento
// Saida: -
{
    // abre um documento
    ifstream documento;
    documento.open(nomeDocumento);
    erroAssert(documento.is_open(), "Documento não foi aberto.");
    
    // le um termo e se não for stopword, adiciona no vocabulario
    while (!documento.eof()) {
        string termo;
        documento >> termo;
        if(!documento.good()) {
            break;
        }

        if (eStopword(termo)) {
            continue;
        }
        else {
            adicionaTermoVocabulario(termo);
        }               
    }
    
    // fecha o documento
    documento.close();
}

