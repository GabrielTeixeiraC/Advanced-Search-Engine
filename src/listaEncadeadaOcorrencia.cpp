//---------------------------------------------------------------------
// Arquivo	: listaEncadeadaOcorrencia.cpp
// Conteudo	: implementacao do listaEncadeadaOcorrencia
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "listaEncadeadaOcorrencia.hpp"
#include "memlog.hpp"
#include "ocorrencia.hpp"

using namespace std;

// construtor da Lista Encadeada de Ocorrencias
ListaEncadeadaOcorrencia::ListaEncadeadaOcorrencia() {
    primeiro = new CelulaListaOcorrencia();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;

    // registra acesso à memória
    escreveMemLog( (long int) (&primeiro), sizeof(CelulaListaOcorrencia*), 3);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaOcorrencia*), 3);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaOcorrencia*), 3);
}

// checa se a Lista Encadeada está vazia
bool ListaEncadeadaOcorrencia::vazia() {
    return tamanho == 0;
}

// retorna o tamanho da Lista Encadeada
int ListaEncadeadaOcorrencia::getTamanho() {
    return tamanho;
}

// Descricao: retorna a Ocorrencia na posição especificada
// Entrada: pos
// Saida: Ocorrencia
Ocorrencia ListaEncadeadaOcorrencia::getItem(int pos){
    CelulaListaOcorrencia *p;
    p = posiciona(pos, false);

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia*), 3);

    return p->item;
}

// Descricao: Retorna a Celula da Lista Encadeada na posição especificada ou uma posição antes
// Entrada: pos, antes
// Saida: Celula de Lista Encadeada de Ocorrencia
CelulaListaOcorrencia* ListaEncadeadaOcorrencia::posiciona(int pos, bool antes = false){
    CelulaListaOcorrencia *p; 
    int i;

    if ( (pos > tamanho) || (pos <= 0) ){
        cerr << "ERRO: Posicao Invalida!" << endl;
    }

    // posiciona na célula anterior a desejada
    p = primeiro;
    for(i=1; i<pos; i++){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia*), 3);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaOcorrencia*), 3);
    }

    // vai para a próxima se antes for false
    if(!antes){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia*), 3);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaOcorrencia*), 3);        
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia*), 3);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaOcorrencia*), 3);

    return p;
}

// Descricao: insere uma Ocorrencia no final da Lista Encadeada de Ocorrencia
// Entrada: item
// Saida: -
void ListaEncadeadaOcorrencia::insereFinal(Ocorrencia item){
    CelulaListaOcorrencia *nova;
    nova = new CelulaListaOcorrencia();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;

    // registra acesso à memoria
    escreveMemLog( (long int) (&nova), sizeof(CelulaListaOcorrencia*), 3);
    escreveMemLog( (long int) (&nova->item), sizeof(string), 0);
    escreveMemLog( (long int) (&ultimo->prox), sizeof(CelulaListaOcorrencia*), 3);
    leMemLog( (long int) (&nova), sizeof(CelulaListaOcorrencia*), 3);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaOcorrencia*), 3);
    leMemLog( (long int) (&nova), sizeof(CelulaListaOcorrencia*), 3);
}

void ListaEncadeadaOcorrencia::limpa(){
// Descricao: limpa a Lista Encadeada de Ocorrencia, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
    CelulaListaOcorrencia *p;
    p = primeiro->prox;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia*), 3);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaOcorrencia*), 3);

    while (p!=NULL) {
        primeiro->prox = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaOcorrencia*), 3);
        leMemLog( (long int) (&p->prox), sizeof(CelulaListaOcorrencia*), 3);        
        
        delete p;
        p = NULL;
        p = primeiro->prox;

        escreveMemLog( (long int) (&p), sizeof(CelulaListaOcorrencia*), 3);
        leMemLog( (long int) (&primeiro->prox), sizeof(CelulaListaOcorrencia*), 3);
    }
    ultimo = primeiro;
    tamanho = 0;

    escreveMemLog( (long int) (&ultimo), sizeof(CelulaListaOcorrencia*), 3);
    leMemLog( (long int) (&primeiro), sizeof(CelulaListaOcorrencia*), 3);
}
