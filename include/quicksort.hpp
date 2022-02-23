//---------------------------------------------------------------------
// Arquivo	: quicksort.h
// Conteudo	: definicao da classe do quicksort
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-01-13 - arquivo criado
//---------------------------------------------------------------------
#ifndef QUICKSORTH
#define QUICKSORTH

#include <iostream>
#include "resultado.hpp"

using namespace std;

class QuickSort {
    public:
        QuickSort(int tamanhoVetor);
        void OrdenaQuickSort(Resultado * resultados);
        void Ordena(int Esq, int Dir,  Resultado * resultados);
        void Particao(int Esq, int Dir, int *i, int *j, Resultado * resultados);
    protected:
        int tamanhoVetor;
};

#endif
