#pragma once

#ifndef __HASH_ABERTO_h__
#define __HASH_ABERTO_h__

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


//-------- Dado Armazenado Hash Aberto

typedef void* infoTable_t;

//-------- Fim Dado Armazenado Hash Aberto


//-------- Modelagem de Funcoes de Manipulacao e tipos 

typedef uint32_t boolean_t;
typedef uint32_t posicaoHash_t;

typedef void(*imprimirDado_f)(infoTable_t dadoImprimir);										//Prototipo de uma funcao que ira imprimir Tabela Hash.
typedef boolean_t(*atribuirDado_f)(infoTable_t* enderecoArmazenar, infoTable_t dadoArmazenar);	//Prototipo de uma funcao que ira inserir dado na Tabela Hash.
typedef uint32_t(*compararDado_f)(infoTable_t dadoBase, infoTable_t dadoComparado);				//Prototipo de uma funcao que ira comparar dados na Tabela Hash.
typedef posicaoHash_t(*funcaoHash_f)(infoTable_t dadoIO);										//Prototipo de uma funcao que ira calcular posicao para dado na Tabela Hash.

//-------- Fim Modelagem de Funcoes de Manipulacao e tipos


//-------- Estrutura Hash Aberto

struct funcoes_s {
	funcaoHash_f funcaoHash;
	atribuirDado_f funcaoAtribui;
	compararDado_f funcaoCompara;
	imprimirDado_f funcaoImprime;
};

typedef struct funcoes_s funcoes_t;

struct itemTabela_s {
	listaE_t listaCaixa;
};

typedef struct itemTabela_s itemTabela_t;

struct tableHash_s {
	uint32_t tamanho;
	uint32_t numItens;
	funcoes_t funcoes;
	itemTabela_t* tabela;
};

typedef struct tableHash_s tableHash_t;

//-------- Fim Estrutura Hash Aberto


//-------- Assinatura Funcoes Hash Aberto

void liberaHash(tableHash_t* tableHash);
void imprimeHashAberto(tableHash_t* tableHash);
void inicializaHashAberto(tableHash_t* tableHash, uint32_t tamanho, funcaoHash_f funcaoHash,
							imprimirDado_f metodoImpressao, compararDado_f metodoComparacao, atribuirDado_f metodoAtribuicao);
boolean_t buscaHashAberto(tableHash_t* tabelaHash, infoTable_t dado);
boolean_t removeHashAberto(tableHash_t* tableHash, infoTable_t dado);
boolean_t insereHashAberto(tableHash_t* tableHash, infoTable_t dado);

//-------- Fim Assinatura Funcoes Hash Aberto

#endif // __HASH_ABERTO_h__