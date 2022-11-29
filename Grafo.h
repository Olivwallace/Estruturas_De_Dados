#pragma once

#ifndef __GRAFO_h__
#define __GRAFO_h__

//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ListaE.h"

//-------- Fim Inclusoes


//-------- Constantes

#define SUCESSO (0)
#define TRUE (1==1)
#define FALSE (1!=1)
#define max2(a,b) ((a >b)? a : b)

//-------- Fim Constantes


//-------- Dado Armazenado Grafo (Lista de Adjacencia)

typedef void* idVertice_t;

//-------- Fim Dado Armazenado Grafo (Lista de Adjacencia)


//-------- Estrutura Grafo (Lista de Adjacencia)

struct funcoesGrafo_s {
	imprimirDado_f funcaoImprime;
	atribuirDado_f funcaoAtribui;
	compararDado_f funcaoCompara;
};

typedef struct funcoesGrafo_s funcoesGrafo_t;

struct verticeGrafo_s {
	idVertice_t id;
	listaE_t listaConexoes;
};

typedef struct verticeGrafo_s verticeGrafo_t;

struct grafo_s {
	uint32_t numArestas;
	uint32_t numVerticesAtual;
	uint32_t numVerticesGerados;
	verticeGrafo_t* verticesGrafo;
	funcoesGrafo_t funcoes;
};

typedef struct grafo_s grafo_t;

//-------- Fim Estrutura Grafo (Lista de Adjacencia)


//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef uint32_t boolean_t;

typedef void(*imprimirDado_f)(verticeGrafo_t* dadoImprimir);										//Prototipo de uma funcao que ira imprimir o Grafo.
typedef boolean_t(*atribuirDado_f)(idVertice_t* enderecoArmazenar, idVertice_t dadoArmazenar);		//Prototipo de uma funcao que ira inserir dado no Grafo.
typedef uint32_t(*compararDado_f)(idVertice_t dadoUm, idVertice_t dadoDois);							//Prototipo de uma funcao que ira comparar dados no Grafo.

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Assinatura Funcoes Grafo (Lista de Adjacencia)

void inicializaGrafoVazio(grafo_t* grafo, atribuirDado_f metodoAtribui, compararDado_f metodoCompara, imprimirDado_f metodoImprime);
boolean_t criaNovoVertice(grafo_t* grafo, idVertice_t dado);
boolean_t criaAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, idVertice_t verticeAdj);
boolean_t removeAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, idVertice_t verticeAdj);
verticeGrafo_t* buscaVerticeGrafo(grafo_t* grafo, idVertice_t idVertice);
void liberaGrafo(grafo_t* grafo);

//-------- Fim Assinatura Funcoes Grafo (Lista de Adjacencia)

#endif // __GRAFO_h__
