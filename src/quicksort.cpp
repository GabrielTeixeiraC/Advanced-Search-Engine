//---------------------------------------------------------------------
// Arquivo	: quicksort.cpp
// Conteudo	: implementacao do quicksort
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-01-13 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <string.h>
#include "quicksort.hpp"
#include "memlog.hpp"

// construtor da classe QuickSort
QuickSort::QuickSort(int tamanhoVetor){
    this->tamanhoVetor = tamanhoVetor;
}

// Descricao: método que particiona o vetor de acordo com um pivô
// Entrada: Esq, Dir, i, j, Resultados
// Saida: -
void QuickSort::Particao(int Esq, int Dir, int *i, int *j, Resultado * resultados){
    Resultado esquerda, meio, direita, pivo, aux;
    *i = Esq; 
    *j = Dir;
    
    // define o pivô como a mediana entre os valores nas extremidades e o valor
    // no meio do intervalo, evitando o pior caso do QuickSort
    esquerda = resultados[*i];
    leMemLog( (long int) (&resultados[*i]), sizeof(Resultado), 2);
    escreveMemLog( (long int) (&esquerda), sizeof(Resultado), 2);

    meio = resultados[(*i + *j)/2];
    leMemLog( (long int) (&resultados[(*i + *j)/2]), sizeof(Resultado), 2);
    escreveMemLog( (long int) (&meio), sizeof(Resultado), 2);

    direita = resultados[*j];
    leMemLog( (long int) (&resultados[*j]), sizeof(Resultado), 2);
    escreveMemLog( (long int) (&direita), sizeof(Resultado), 2);
    
    if(esquerda.resultado >= meio.resultado && esquerda.resultado >= direita.resultado) {
        if(meio.resultado >= direita.resultado) {
            pivo = meio;
            leMemLog( (long int) (&meio), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&pivo), sizeof(Resultado), 2);
        } 
        else {
            pivo = direita;
            leMemLog( (long int) (&direita), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&pivo), sizeof(Resultado), 2);
        } 
    }
    else if(meio.resultado >= esquerda.resultado && meio.resultado >= direita.resultado) {
        if(esquerda.resultado >= direita.resultado) {
            pivo = esquerda;
            leMemLog( (long int) (&esquerda), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&pivo), sizeof(Resultado), 2);
        } 
        else {
            pivo = direita;
            leMemLog( (long int) (&direita), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&pivo), sizeof(Resultado), 2);
        } 
    }
    else {
        if(esquerda.resultado >= meio.resultado) {
            pivo = esquerda;

            leMemLog( (long int) (&esquerda), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&pivo), sizeof(Resultado), 2);
        } 
        else {
            pivo = meio;

            leMemLog( (long int) (&meio), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&pivo), sizeof(Resultado), 2);
        } 
    }

    // passa elementos maiores que o pivô para a sua esquerda e
    // os elementos menores que o pivô para a sua direita
    do { 
        // para no primeiro elemento à esquerda do pivô que é menor do que ele ou
        // é igual e possui id >= ao do pivô
        while (resultados[*i].resultado >= pivo.resultado){
            if (resultados[*i].resultado == pivo.resultado){
                if (resultados[*i].id >= pivo.id){
                    break;
                } 
                else{
                    (*i)++;
                }
            }
            else{
                (*i)++;
            }
        }
        // para no primeiro elemento à direita do pivô que é maior do que ele ou
        // é igual e possui id <= ao do pivô
        while (resultados[*j].resultado <= pivo.resultado) {
            if (resultados[*j].resultado == pivo.resultado){
                if (resultados[*j].id <= pivo.id){
                    break;
                } 
                else{
                    (*j)--;
                } 
            }
            else{
                (*j)--;
            }
        }
        // troca de lado os elementos identificados pelos loops acima
        if (*i <= *j){
            aux = resultados[*i];
            leMemLog( (long int) (&resultados[*i]), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&aux), sizeof(Resultado), 2);

            resultados[*i] = resultados[*j];
            leMemLog( (long int) (&resultados[*j]), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&resultados[*i]), sizeof(Resultado), 2);

            resultados[*j] = aux;
            leMemLog( (long int) (&aux), sizeof(Resultado), 2);
            escreveMemLog( (long int) (&resultados[*j]), sizeof(Resultado), 2);

            (*i)++; 
            (*j)--;

        }
    } while (*i <= *j);
}

// Descricao: método que particiona e ordena o vetor recursivamente
// Entrada: Esq, Dir, Resultados
// Saida: -
void QuickSort::Ordena(int Esq, int Dir, Resultado * resultados){
    int i, j;
    // particiona o vetor
    Particao(Esq, Dir, &i, &j, resultados);
    
    // chama o método de ordenação recursivamente em cada partição do vetor
    if (Esq < j) Ordena(Esq, j, resultados);
    if (i < Dir) Ordena(i, Dir, resultados);
}

// Descricao: método que ordena o vetor de Resultados
// Entrada: resultados
// Saida: -
void QuickSort::OrdenaQuickSort(Resultado * resultados){
    int indiceFinal = this->tamanhoVetor - 1;
    Ordena(0, indiceFinal, resultados);
}