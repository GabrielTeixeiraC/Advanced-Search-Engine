//---------------------------------------------------------------------
// Arquivo      : listaEncadeadaOcorrenciaOcorrencia.hpp
// Conteudo     : definicoes da classe ListaEncadeadaOcorrenciaOcorrencia
// Autor        : Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico    : 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#ifndef LISTAENCADEADAOcorrenciaOCORRENCIAH
#define LISTAENCADEADAOcorrenciaOCORRENCIAH

#include <string>
#include "ocorrencia.hpp"
using namespace std;

// Celula da lista de termos com uma string e sua frequencia e um apontador para a próxima Celula
struct CelulaListaOcorrencia
{
    Ocorrencia item;
    CelulaListaOcorrencia* prox;

    // Construtor de uma Celula de Lista
    CelulaListaOcorrencia(){
        item = Ocorrencia();
        prox = NULL;
    }
};

class ListaEncadeadaOcorrencia {
    public:
        ListaEncadeadaOcorrencia();
        bool vazia();
        int getTamanho();
        void insereFinal(Ocorrencia item);
        void limpa();
        CelulaListaOcorrencia* primeiro;
    
    protected:
        int tamanho;
        CelulaListaOcorrencia* ultimo;
};


#endif
