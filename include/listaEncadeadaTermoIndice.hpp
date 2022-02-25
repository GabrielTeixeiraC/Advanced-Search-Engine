//---------------------------------------------------------------------
// Arquivo      : listaEncadeadaTermoIndice.hpp
// Conteudo     : definicoes da classe ListaEncadeadaTermoIndice
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef LISTAENCADEADATERMOINDICEH
#define LISTAENCADEADATERMOINDICEH

#include <string>
#include "termoIndice.hpp"
using namespace std;

// Celula da lista de termos com uma string e sua frequencia e um apontador para a próxima Celula
struct CelulaListaTermoIndice
{
    TermoIndice item;
    CelulaListaTermoIndice* prox;

    // Construtor de uma Celula de Lista
    CelulaListaTermoIndice(){
        item = TermoIndice();
        prox = NULL;
    }
};


class ListaEncadeadaTermoIndice {
    public:
        ListaEncadeadaTermoIndice();
        bool vazia();
        int getTamanho();
        void insereFinal(TermoIndice item);
        void limpa();
        CelulaListaTermoIndice* primeiro;
    
    protected:
        int tamanho;
        CelulaListaTermoIndice* ultimo;
};


#endif
