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

Vocabulario::Vocabulario(int tamanhoMaximoVocabulario) {
    tamanhoVocabulario = 0;
    vetorDeTermos = new TermoVocabulario[tamanhoMaximoVocabulario];
}

void Vocabulario::desaloca() {
    delete[] this->vetorDeTermos;
}

int Vocabulario::posicaoTermoNoVocabulario(string termo) {
    for (int i = 0; i < tamanhoVocabulario; i++) {
        if (vetorDeTermos[i].termo == termo) {
            return i;
        }
        else {
            continue;
        }
    }
    return -1;
}

void Vocabulario::adicionaTermoVocabulario(string termo) {
    int posicaoTermo = posicaoTermoNoVocabulario(termo);
    if (posicaoTermo >= 0) {
        vetorDeTermos[posicaoTermo].frequencia++;
    }
    else {
        vetorDeTermos[tamanhoVocabulario].termo = termo;
        vetorDeTermos[tamanhoVocabulario].frequencia++;
        tamanhoVocabulario++;
    }
}

int Vocabulario::getTamanhoVocabulario() {
    return tamanhoVocabulario;
}

bool Vocabulario::eStopword(string palavra, string nomeArquivoStopwords)
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

void Vocabulario::criaVocabularioDocumento(string nomeDocumento, string nomeArquivoStopwords) {
    ifstream documento;
    documento.open(nomeDocumento);
    erroAssert(documento.is_open(), "Documento não foi aberto.");
        
    while (!documento.eof()) {
        string termo;
        documento >> termo;
        if(!documento.good()) {
            break;
        }

        if (eStopword(termo, nomeArquivoStopwords)) {
            continue;
        }
        else {
            adicionaTermoVocabulario(termo);
        }               
    }
    documento.close();

}

