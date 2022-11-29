#pragma once

#ifndef __LISTA_ENCADEADA_h__
#define __LISTA_ENCADEADA_h__


//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//-------- Fim Inclusoes


//-------- Constantes

#define SUCESSO (0)
#define TRUE (1==1)
#define FALSE (1!=1)
#define max2(a,b) ((a >b)? a : b)

//-------- Fim Constantes


//-------- Dado Armazenado Pilha

typedef void* infoLista_t;

//-------- Fim Dado Armazenado Pilha


//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef uint32_t boolean_t;

typedef void(*imprimirDado_f)(infoLista_t dadoImprimir);											//Prototipo de uma funcao que ira imprimir Lista.
typedef boolean_t(*atribuirDado_f)(infoLista_t* enderecoArmazenar, infoLista_t dadoArmazenar);		//Prototipo de uma funcao que ira inserir dado na Lista.
typedef uint32_t(*compararDado_f)(infoLista_t dadoUm, infoLista_t dadoDois);						//Prototipo de uma funcao que ira comparar dados na Lista.

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Estrutura Lista Encadeada

struct itemListaE_s {
	struct itemListaE_s* proxItem;
	infoLista_t dadoArmazenado;
};

typedef struct itemListaE_s itemListaE_t;

struct listaE_s {
	uint32_t numItens;
	itemListaE_t* primeiro;
};

typedef struct listaE_s listaE_t;

//-------- Fim Estrutura Lista Encadeada


//-------- Assinatura Funcoes Lista Encadeada

void inicializaLista(listaE_t* lista);
boolean_t listaTaVazia(listaE_t* lista);
boolean_t insereInicioLista(listaE_t* lista, infoLista_t dado, atribuirDado_f metodoAtribuicao);
boolean_t insereFimLista(listaE_t* lista, infoLista_t dado, atribuirDado_f metodoAtribuicao);
boolean_t insereOrdenado(listaE_t* lista, infoLista_t dado, compararDado_f metodoComparacao, atribuirDado_f metodoAtribuicao);
void imprimeLista(listaE_t* lista, imprimirDado_f metodoImpressao);
itemListaE_t* buscarItemLista(listaE_t* lista, infoLista_t dado, compararDado_f metodoComparacao);
boolean_t retiraItemLista(listaE_t* lista, infoLista_t dado, compararDado_f metodoComparacao);
void liberaLista(listaE_t* lista);

//-------- Fim Assinatura Funcoes Lista Encadeada

#endif // __LISTA_ENCADEADA_h__
