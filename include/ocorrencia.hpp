//---------------------------------------------------------------------
// Arquivo	: ocorrencia.h
// Conteudo	: definicao da struct ocorrencia
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2022-02-18 - arquivo criado
//---------------------------------------------------------------------
#ifndef OCORRENCIAH
#define OCORRENCIAH

using namespace std;

// Ocorrencia: guarda o documento de origem de um termo e sua frequencia
struct Ocorrencia {
    int documento;
    int frequencia;
};

#endif
