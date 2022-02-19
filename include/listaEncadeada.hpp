//---------------------------------------------------------------------
// Arquivo      : listaEncadeada.hpp
// Conteudo     : definicoes da classe ListaEncadeada
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef LISTAENCADEADAH
#define LISTAENCADEADAH

#include <string>
#include "termoIndice.hpp"

using namespace std;

// Celula da lista de termos com uma string e sua frequencia e um apontador para a próxima Celula
struct CelulaLista
{
    TermoIndice item;
    CelulaLista* prox;

    // Construtor de uma Celula de Lista
    CelulaLista(){
        item = TermoIndice();
        prox = NULL;
    }
};


class ListaEncadeada {
    public:
        ListaEncadeada();
        bool vazia();
        int getTamanho();
        TermoIndice getItem(int pos);
        void insereInicio(TermoIndice item);
        void insereFinal(TermoIndice item);
        void inserePosicao(TermoIndice item, int pos);
        TermoIndice removeInicio();
        TermoIndice removeFinal();
        TermoIndice removePosicao(int pos);
        TermoIndice pesquisa(string termo);
        void limpa();
    
    protected:
        int tamanho;
        CelulaLista* primeiro;
        CelulaLista* ultimo;
        CelulaLista* posiciona(int pos, bool antes);
};


#endif
