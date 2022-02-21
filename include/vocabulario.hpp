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
        int tamanhoVocabulario;
        string nomeArquivoStopwords;
    public:
        TermoVocabulario* vetorDeTermos;
        Vocabulario(int tamanhoMaximoVocabulario, string nomeArquivoStopwords);
        void criaVocabularioDocumento(string nomeDocumento);
        int posicaoTermoNoVocabulario(string termo);
        void adicionaTermoVocabulario(string termo);
        bool eStopword(string palavra);
        int getTamanhoVocabulario();
        void desaloca();
};

#endif
