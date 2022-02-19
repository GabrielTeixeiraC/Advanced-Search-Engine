//---------------------------------------------------------------------
// Arquivo	: listaEncadeada.cpp
// Conteudo	: implementacao do listaEncadeada
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "listaEncadeada.hpp"
#include "memlog.hpp"

using namespace std;


// construtor da Lista Encadeada
ListaEncadeada::ListaEncadeada() {
    primeiro = new CelulaLista();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;

    // registra acesso à memória
    escreveMemLog( (long int) (&primeiro), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&primeiro), sizeof(CelulaLista*), 0);
}

// checa se a Lista Encadeada está vazia
bool ListaEncadeada::vazia() {
    return tamanho == 0;
}

// retorna o tamanho da Lista Encadeada
int ListaEncadeada::getTamanho() {
    return tamanho;
}

// Descricao: retorna a string na posição especificada
// Entrada: pos
// Saida: string
TermoIndice ListaEncadeada::getItem(int pos){
    CelulaLista *p;
    p = posiciona(pos, false);

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);

    return p->item;
}

// Descricao: Retorna a Celula da Lista Encadeada na posição especificada ou uma posição antes
// Entrada: pos, antes
// Saida: Celula de Lista Encadeada 
CelulaLista* ListaEncadeada::posiciona(int pos, bool antes = false){
    CelulaLista *p; 
    int i;

    if ( (pos > tamanho) || (pos <= 0) ){
        cerr << "ERRO: Posicao Invalida!" << endl;
    }

    // posiciona na célula anterior a desejada
    p = primeiro;
    for(i=1; i<pos; i++){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);
    }

    // vai para a próxima se antes for false
    if(!antes){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);        
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&primeiro), sizeof(CelulaLista*), 0);

    return p;
}

// Descricao: insere uma string no início da Lista Encadeada
// Entrada: item
// Saida: -
void ListaEncadeada::insereInicio(TermoIndice item){
    CelulaLista *nova;
    nova = new CelulaLista();
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;

    // nova celula é a ultima
    if(nova->prox == NULL){
        ultimo = nova;
        
        // registra acesso à memoria
        escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&nova->item), sizeof(string), 0);
    escreveMemLog( (long int) (&nova->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
}

// Descricao: insere uma string no final da Lista Encadeada
// Entrada: item
// Saida: -
void ListaEncadeada::insereFinal(TermoIndice item){
    CelulaLista *nova;
    nova = new CelulaLista();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;

    // registra acesso à memoria
    escreveMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&nova->item), sizeof(string), 0);
    escreveMemLog( (long int) (&ultimo->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
}

// Descricao: insere uma string na posição especificada da Lista Encadeada
// Entrada: item, pos
// Saida: -
void ListaEncadeada::inserePosicao(TermoIndice item, int pos){
    CelulaLista *p, *nova;
    p = posiciona(pos,true); // posiciona na célula anterior
    nova = new CelulaLista();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;

    // nova celula é a última
    if(nova->prox == NULL){
        ultimo = nova;

        // registra acesso à memoria
        escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&nova->item), sizeof(string), 0);
    escreveMemLog( (long int) (&nova->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&nova), sizeof(CelulaLista*), 0);    

}

// Descricao: remove uma string do início da Lista Encadeada
// Entrada: -
// Saida: string removida
TermoIndice ListaEncadeada::removeInicio(){
    TermoIndice aux;
    CelulaLista *p;
    if (tamanho == 0){
        cerr << "ERRO: Lista vazia!" << endl;
    }
    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;

    // string era a única na Lista Encadeada
    if(primeiro->prox == NULL){
        ultimo = primeiro;

        // registra acesso à memoria
        escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&primeiro), sizeof(CelulaLista*), 0);
    }

    aux = p->item;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&aux), sizeof(string), 0);
    leMemLog( (long int) (&p->item), sizeof(string), 0);  

    delete p;
    return aux;
}

// Descricao: remove uma string do final da Lista Encadeada
// Entrada: -
// Saida: string removida
TermoIndice ListaEncadeada::removeFinal(){
    TermoIndice aux;
    CelulaLista *p;
    if (tamanho == 0){
        cerr << "ERRO: Lista vazia!" << endl;
    }
    // posiciona p na celulaLista anterior à última
    p = posiciona(tamanho, true);
    p->prox = NULL;
    tamanho--;
    aux = ultimo->item;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&aux), sizeof(string), 0);
    leMemLog( (long int) (&ultimo->item), sizeof(string), 0);  

    delete ultimo;
    ultimo = p;
    
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    
    return aux;
}

// Descricao: remove uma string da posição especificada da Lista Encadeada
// Entrada: pos
// Saida: string removida
TermoIndice ListaEncadeada::removePosicao(int pos){
    TermoIndice aux;
    CelulaLista *p, *q;
    if (tamanho == 0){
        cerr << "ERRO: Lista vazia!" << endl;
    }
    // posiciona p na celulaLista anterior à pos
    p = posiciona(pos, true);
    q = p->prox;
    p->prox = q->prox;
    tamanho--;
    aux = q->item;
    delete q;

    // string era a última da Lista Encadeada
    if(p->prox == NULL){
        ultimo = p;

        // registra acesso à memoria
        escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&q), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&q->prox), sizeof(CelulaLista*), 0);
    escreveMemLog( (long int) (&aux), sizeof(string), 0);
    leMemLog( (long int) (&q->item), sizeof(string), 0);
    
    return aux;
}

TermoIndice ListaEncadeada::pesquisa(string termo) {
    
}

void ListaEncadeada::limpa(){
// Descricao: limpa a Lista Encadeada, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
    CelulaLista *p;
    p = primeiro->prox;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);

    while (p!=NULL) {
        primeiro->prox = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&p->prox), sizeof(CelulaLista*), 0);        
        
        delete p;
        p = NULL;
        p = primeiro->prox;

        escreveMemLog( (long int) (&p), sizeof(CelulaLista*), 0);
        leMemLog( (long int) (&primeiro->prox), sizeof(CelulaLista*), 0);
    }
    ultimo = primeiro;
    tamanho = 0;

    escreveMemLog( (long int) (&ultimo), sizeof(CelulaLista*), 0);
    leMemLog( (long int) (&primeiro), sizeof(CelulaLista*), 0);
}
