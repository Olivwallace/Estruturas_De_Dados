//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "PilhaL.h"

//-------- Fim Inclusoes


//-------- Funcoes Pilha Lista

/// <summary>
///		Funcao para incializa uma pilha vazia.
/// </summary>
/// <param name="pilha">Endereco de uma variavel pilha_t</param>
/// <param name="capacidade">Tamanho maximo para uma pilha</param>
void inicializaPilha(pilha_t* pilha, uint32_t capacidade) {
	if (capacidade != 0) { //Se capacidade 0, nao tem porque inicializar pilha.
		pilha->capacidade = capacidade;
		pilha->numItens = 0;
		pilha->topoPilha = NULL;
	}
}


/// <summary>
///		Funcao para verificar se pilha esta vazia.
/// </summary>
/// <param name="pilha">Endereco de uma variavel pilha_t</param>
/// <returns>TRUE: Se vazia | FALSE: Se preenchida</returns>
boolean_t pilhaVazia(pilha_t* pilha) {
	return (pilha->numItens == 0);
}


/// <summary>
///		Funcao para empilhar item no topo da pilha. 
/// </summary>
/// <param name="pilha">Endereco de uma variavel pilha_t</param>
/// <param name="dado">Dado do tipo infoPilha_t a ser inserido na pilha</param>
/// <param name="metodoAtribuicao">Funcao que ira cuidar do metodo correto de atribuir o dado a um endereco da pilha</param>
/// <returns>TRUE: Inseriu dado| FALSE: Erro na insercao </returns>
boolean_t empilhaPilha(pilha_t* pilha, infoPilha_t dado, atribuirDado_f metodoDeAtribuicao) {
	boolean_t conseguiuEmpilhar = FALSE;

	if (pilha->capacidade != pilha->numItens) { // Verificar se capacidade maxima foi atingida para que seja inserido um novo item.

		itemPilha_t* novo = malloc(sizeof(itemPilha_t));

		if (novo != NULL) { // Confirma se existe espaco alocado em novo para que possa inserir o dado e posiciona-lo no topo da pilha.
			conseguiuEmpilhar = metodoDeAtribuicao(novo, dado);
			
			if (conseguiuEmpilhar) {
				novo->proxItem = pilha->topoPilha;

				pilha->numItens++;
				pilha->topoPilha = novo;
			}
		}
	}

	return conseguiuEmpilhar;
}


/// <summary>
///		Funcao para desempilhar item no topo da pilha.
/// </summary>
/// <param name="pilha">Endereco de uma variavel pilha_t</param>
/// <param name="dado">Ponteiro de um infoPilha_t onde item topo sera descarregado</param>
/// <param name="metodoAtribuicao">Funcao que ira cuidar do metodo correto de atribuir o dado a um endereco da pilha</param>
/// <returns>TRUE: Desempilhou| FALSE: Erro no desempilhamento </returns>
boolean_t desempilhaPilha(pilha_t* pilha, infoPilha_t* enderecoRetornoDado, atribuirDado_f metodoDeAtribuicao) {
	boolean_t conseguiuDesempilhar = FALSE;

	if (!pilhaVazia(pilha)) { //Confirma se tem elementos na pilha.

		//Armazena endereco do topo da pilha e proximo item.
		itemPilha_t* atualTopo = pilha->topoPilha;
		itemPilha_t* temp = atualTopo->proxItem;

		conseguiuDesempilhar = metodoDeAtribuicao(enderecoRetornoDado, atualTopo->dadoArmazenado); // Salva o dado da pilha.

		if (conseguiuDesempilhar) {
			free(atualTopo); // Libera topo da pilha.

			pilha->topoPilha = temp; //Posiciona topo da pilha no elemento seguinte.
			pilha->numItens--;
		}	
	}

	return conseguiuDesempilhar;
}


/// <summary>
///		Funcao para liberar pilha.
/// </summary>
/// <param name="pilha">Endereco de uma variavel do tipo pilha_t</param>
void liberaPilha(pilha_t* pilha) {
	itemPilha_t* atualTopo = pilha->topoPilha;

	while (atualTopo != NULL) {
		itemPilha_t* tmp = atualTopo->proxItem;
		free(atualTopo);
		atualTopo = tmp;
	}
}


/// <summary>
///		Funcao que imprime uma pilha.
/// </summary>
/// <param name="pilha">Endereco de uma variavel do tipo pilha_t</param>
/// <param name="metodoImpressao">Funcao que ira cuidar do metodo correto de imprimir os dados de uma pilha</param>
void imprimePilha(pilha_t* pilha, imprimirDado_f metodoDeImpressao) {
	itemPilha_t* atual = pilha->topoPilha;

	while (atual != NULL) {
		metodoDeImpressao(atual->dadoArmazenado);
		atual = atual->proxItem;
	}
}

//-------- Fim Funcoes Pilha Lista