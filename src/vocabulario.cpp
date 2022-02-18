//---------------------------------------------------------------------
// Arquivo	: vocabulario.cpp
// Conteudo	: implementacao do vocabulario
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include "vocabulario.hpp"
#include "memlog.hpp"

Vocabulario::Vocabulario(int tamanhoMaximoVocabulario) {
    vetorDeTermos = new TermoVocabulario[tamanhoMaximoVocabulario];
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


Vocabulario::~Vocabulario() {
    delete[] this->vetorDeTermos;
}

