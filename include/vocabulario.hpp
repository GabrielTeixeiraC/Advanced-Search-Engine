//---------------------------------------------------------------------
// Arquivo      : vocabulario.hpp
// Conteudo     : definicoes da classe Vocabulario
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef VOCABULARIOH
#define VOCABULARIOH

#include <string>
#include "termoVocabulario.hpp"

using namespace std;

class Vocabulario {
    private:
        int tamanhoVocabulario = 0;
    public:
        TermoVocabulario* vetorDeTermos;
        Vocabulario(int tamanhoMaximoVocabulario);
        int posicaoTermoNoVocabulario(string termo);
        void adicionaTermoVocabulario(string termo);
        int getTamanhoVocabulario();
        ~Vocabulario();
};

#endif
