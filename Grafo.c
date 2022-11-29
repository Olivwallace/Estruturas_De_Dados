//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ListaE.h"
#include "Grafo.h"

//-------- Fim Inclusoes


//-------- Funcoes Grafo Lista Adjacencia

/// <summary>
///		Funcao para inicializar um grafo vazio.
/// </summary>
/// <param name="grafo">Endereco do grafo</param>
void inicializaGrafoVazio(grafo_t* grafo, atribuirDado_f metodoAtribui, compararDado_f metodoCompara, imprimirDado_f metodoImprime) {
	grafo->numArestas = 0;
	grafo->numVerticesAtual = 0;
	grafo->numVerticesGerados = 0;
	grafo->verticesGrafo = NULL;

	grafo->funcoes.funcaoAtribui = metodoAtribui;
	grafo->funcoes.funcaoCompara = metodoCompara;
	grafo->funcoes.funcaoImprime = metodoImprime;
}


/// <summary>
///		Funcao para cria um novo vertice no grafo.
/// </summary>
/// <param name="grafo">Endereco do grafo</param>
/// <param name="dado">Dado a ser armazenado no vertice</param>
/// <param name="metodoAtribuicao">Funcao que ira realizar a atribuicao de dado no endereco do vertice</param>
/// <returns>TRUE: Se vertice criado | FALSE: Se vertice nao gerado </returns>
boolean_t criaNovoVertice(grafo_t* grafo, idVertice_t idUnico) {
	boolean_t conseguiuAdicionar = FALSE;
	int novaPos = grafo->numVerticesAtual + 1;

	verticeGrafo_t *vertice = buscaVerticeGrafo(grafo, idUnico);
	
	if (vertice == NULL) {

		grafo->verticesGrafo = (verticeGrafo_t*) realloc(grafo->verticesGrafo, novaPos * sizeof(verticeGrafo_t));

		if (grafo->verticesGrafo != NULL) {
			grafo->funcoes.funcaoAtribui(&grafo->verticesGrafo[novaPos - 1].id, idUnico);
			inicializaLista(&grafo->verticesGrafo[novaPos - 1].listaConexoes);

			grafo->numVerticesAtual++;
			grafo->numVerticesGerados++;
			conseguiuAdicionar = TRUE;
		}

	}

	return conseguiuAdicionar;
}


/// <summary>
///		Funcoe para criar adjacencia
/// </summary>
/// <param name="grafo">Endereco do grafo a ser inserido</param>
/// <param name="verticeBase">Vertice onde sera inserido</param>
/// <param name="verticeAdj">Id do vertice a ser adicionado</param>
/// <returns>TRUE: Criou adjacencia com sucesso | FALSE: Não foi possivel adicionar adjacencia</returns>
boolean_t criaAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, idVertice_t verticeAdj) {
	boolean_t inserido = FALSE;

	if (verticeBase != NULL && verticeBase->id != verticeAdj && buscarItemLista(&verticeBase->listaConexoes, verticeAdj, grafo->funcoes.funcaoCompara) != NULL) {
		inserido = insereOrdenado(&verticeBase->listaConexoes, verticeAdj, grafo->funcoes.funcaoCompara, grafo->funcoes.funcaoAtribui);
		if (inserido) grafo->numArestas++;
	}

	return inserido;
}


/// <summary>
///		Funcao para remover uma ajacencia do grafo.
/// </summary>
/// <param name="grafo">Endereco do grafo a ser removido</param>
/// <param name="verticeBase">Endereco do vertice onde sera removida adjacencia</param>
/// <param name="verticeAdj">Id do vertice a ser removido da adjacencia</param>
/// <returns></returns>
boolean_t removeAdjacencia(grafo_t* grafo, verticeGrafo_t* verticeBase, idVertice_t verticeAdj) {
	boolean_t removido = FALSE;

	if (verticeBase != NULL && verticeBase->id != verticeAdj) {
		removido = retiraItemLista(&verticeBase->listaConexoes, verticeAdj, grafo->funcoes.funcaoCompara);
		if (removido) grafo->numArestas--;
	}

	return removido;
}


boolean_t removeVerticeGrafo(grafo_t* grafo, verticeGrafo_t* verticeRemove) {
	boolean_t conseguiuRemover = FALSE;
	
	if (verticeRemove != NULL) {
		
		for (int i = 0; i < grafo->numVerticesAtual; i++) {
			if (grafo->verticesGrafo[i].id != verticeRemove->id) {
				if (buscarItemLista(&grafo->verticesGrafo[i].listaConexoes, verticeRemove->id, grafo->funcoes.funcaoCompara) != NULL) {
					retiraItemLista(&grafo->verticesGrafo[i].listaConexoes, verticeRemove->id, grafo->funcoes.funcaoCompara);
				}
			}
		}

		if(verticeRemove->listaConexoes.numItens != 0)
			liberaLista(&verticeRemove->listaConexoes);
	}

	return conseguiuRemover;
}


verticeGrafo_t* buscaVerticeGrafo(grafo_t* grafo,idVertice_t idVertice) {
	uint32_t i;
	verticeGrafo_t* verticeLocalizado = NULL;

	for (i = 0; i < grafo->numVerticesAtual; i++) {
		if (grafo->verticesGrafo[i].id == idVertice)
			verticeLocalizado = &grafo->verticesGrafo[i];;
	}

	return verticeLocalizado;
}


void liberaGrafo(grafo_t* grafo) {
	uint32_t i;

	for (i = grafo->numVerticesAtual; i >= 0 ; i--) {
		removeVerticeGrafo(grafo, &grafo->verticesGrafo[i]);
	}
}

//-------- Fim Funcoes Grafo Lista Adjacencia