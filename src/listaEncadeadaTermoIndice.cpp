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
    escreveMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 0);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaTermoIndice*), 0);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 0);
}

// checa se a Lista Encadeada de Termos do Indice está vazia
bool ListaEncadeadaTermoIndice::vazia() {
    return tamanho == 0;
}

// retorna o tamanho da Lista Encadeada de Termos do Indice
int ListaEncadeadaTermoIndice::getTamanho() {
    return tamanho;
}

// Descricao: retorna o TermoIndice na posição especificada
// Entrada: pos
// Saida: TermoIndice
TermoIndice ListaEncadeadaTermoIndice::getItem(int pos){
    CelulaListaTermoIndice *p;
    p = posiciona(pos, false);

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 0);

    return p->item;
}

// Descricao: Retorna a Celula da Lista Encadeada de Termos do Indice na posição especificada ou uma posição antes
// Entrada: pos, antes
// Saida: Celula de Lista Encadeada de Termos do Indice 
CelulaListaTermoIndice* ListaEncadeadaTermoIndice::posiciona(int pos, bool antes = false){
    CelulaListaTermoIndice *p; 
    int i;

    if ( (pos > tamanho) || (pos <= 0) ){
        cerr << "ERRO: Posicao Invalida!" << endl;
    }

    // posiciona na célula anterior a desejada
    p = primeiro;
    for(i=1; i<pos; i++){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 0);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaTermoIndice*), 0);
    }

    // vai para a próxima se antes for false
    if(!antes){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 0);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaTermoIndice*), 0);        
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 0);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 0);

    return p;
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
    escreveMemLog( (long int) (&nova), sizeof(CelulaListaTermoIndice*), 0);
    escreveMemLog( (long int) (&nova->item), sizeof(string), 0);
    escreveMemLog( (long int) (&ultimo->prox), sizeof(CelulaListaTermoIndice*), 0);
    leMemLog( (long int) (&nova), sizeof(CelulaListaTermoIndice*), 0);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaTermoIndice*), 0);
    leMemLog( (long int) (&nova), sizeof(CelulaListaTermoIndice*), 0);
}

void ListaEncadeadaTermoIndice::limpa(){
// Descricao: limpa a Lista Encadeada de Termos do Indice, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
    CelulaListaTermoIndice *p;
    p = primeiro->prox;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 0);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaTermoIndice*), 0);

    while (p!=NULL) {
        primeiro->prox = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaTermoIndice*), 0);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaTermoIndice*), 0);        
        
        delete p;
        p = NULL;
        p = primeiro->prox;

        escreveMemLog( (long int) (&p), sizeof(CelulaListaTermoIndice*), 0);
        leMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaTermoIndice*), 0);
    }
    ultimo = primeiro;
    tamanho = 0;

    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaTermoIndice*), 0);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaTermoIndice*), 0);
}
