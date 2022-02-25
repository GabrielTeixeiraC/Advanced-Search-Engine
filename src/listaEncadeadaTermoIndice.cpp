//---------------------------------------------------------------------
// Arquivo	: listaEncadeadaTermoIndice.cpp
// Conteudo	: implementacao do listaEncadeadaTermoIndice
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "listaEncadeadaTermoIndice.hpp"
#include "termoIndice.hpp"
#include "memlog.hpp"

using namespace std;

// construtor da Lista Encadeada de Termos do Indice
ListaEncadeadaTermoIndice::ListaEncadeadaTermoIndice() {
    primeiro = new CelulaListaTermoIndice();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;

    // registra acesso à memória
    escreveMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 4);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaTermoIndice*), 4);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 4);
}

// checa se a Lista Encadeada de Termos do Indice está vazia
bool ListaEncadeadaTermoIndice::vazia() {
    return tamanho == 0;
}

// retorna o tamanho da Lista Encadeada de Termos do Indice
int ListaEncadeadaTermoIndice::getTamanho() {
    return tamanho;
}

// Descricao: insere um TermoIndice no final da Lista Encadeada de Termos do Indice
// Entrada: item
// Saida: -
void ListaEncadeadaTermoIndice::insereFinal(TermoIndice item){
    CelulaListaTermoIndice *nova;
    nova = new CelulaListaTermoIndice();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;

    // registra acesso à memoria
    escreveMemLog( (long int) (&nova), sizeof(CelulaListaTermoIndice*), 4);
    escreveMemLog( (long int) (&nova->item), sizeof(string), 0);
    escreveMemLog( (long int) (&ultimo->prox), sizeof(CelulaListaTermoIndice*), 4);
    leMemLog( (long int) (&nova), sizeof(CelulaListaTermoIndice*), 4);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaTermoIndice*), 4);
    leMemLog( (long int) (&nova), sizeof(CelulaListaTermoIndice*), 4);
}

void ListaEncadeadaTermoIndice::limpa(){
// Descricao: limpa a Lista Encadeada de Termos do Indice, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
    CelulaListaTermoIndice *p;
    p = primeiro->prox;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 4);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaTermoIndice*), 4);

    while (p!=NULL) {
        primeiro->prox = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaTermoIndice*), 4);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaTermoIndice*), 4);        
        
        delete p;
        p = NULL;
        p = primeiro->prox;

        escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 4);
        leMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaTermoIndice*), 4);
    }
    ultimo = primeiro;
    tamanho = 0;

    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaTermoIndice*), 4);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 4);
}
