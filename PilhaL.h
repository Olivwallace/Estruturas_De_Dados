#pragma once

#ifndef __PILHA_LISTA_h__
#define __PILHA_LISTA_h__

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

typedef void* infoPilha_t;

//-------- Fim Dado Armazenado Pilha


//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef uint32_t boolean_t;

typedef void(*imprimirDado_f)(infoPilha_t dadoImprimir);											//Prototipo de uma funcao que ira imprimir Pilha.
typedef boolean_t(*atribuirDado_f)(infoPilha_t* enderecoArmazenar, infoPilha_t dadoArmazenar);		//Prototipo de uma funcao que ira inserir dado na Pilha.
typedef uint32_t(*compararDado_f)(infoPilha_t dadoUm, infoPilha_t dadoDois);					//Prototipo de uma funcao que ira comparar dados na Pilha.

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Estrutura Pilha Lista

struct itemPilha_s {
	struct itemPilha_s* proxItem;
	infoPilha_t dadoArmazenado;
};

typedef struct itemPilha_s itemPilha_t;

struct pilha_s {
	uint32_t capacidade;
	uint32_t numItens;
	itemPilha_t* topoPilha;
};

typedef struct pilha_s pilha_t;

//-------- Fim Estrutura Pilha Lista


//-------- Assinatura Funcoes Pilha Lista

void inicializaPilha(pilha_t* pilha, uint32_t capacidade);
boolean_t pilhaVazia(pilha_t* pilha);
boolean_t empilhaPilha(pilha_t* pilha, infoPilha_t dado, atribuirDado_f metodoDeAtribuicao);
boolean_t desempilhaPilha(pilha_t* pilha, infoPilha_t* enderecoRetornoDado, atribuirDado_f metodoDeAtribuicao);
void liberaPilha(pilha_t* pilha);
void imprimePilha(pilha_t* pilha, imprimirDado_f metodoDeImpressao);

//-------- Fim Assinatura Funcoes Pilha Lista

#endif // __PILHA_LISTA_h__