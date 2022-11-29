//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ListaE.h"

//-------- Fim Inclusoes


//-------- Funcoes Lista Encadeada

/// <summary>
///		Funcao para Inicializar uma estrutura de lista vazia.
/// </summary>
/// <param name="lista">Endereco de uma variavel listaE_t</param>
void inicializaLista(listaE_t* lista) {
	lista->numItens = 0;
	lista->primeiro = NULL;
}


/// <summary>
///		Funcao que verificar se lista esta vazia.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <returns>TRUE: Lista Vazia | FALSE: Lista Preenchida</returns>
boolean_t listaTaVazia(listaE_t* lista) {
	return (lista->numItens == 0);
}


/// <summary>
///		Funcao para inserir no inicio de uma lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <param name="dado">Dado do tipo infoLista_t a ser inserido na lista</param>
/// <param name="metodoAtribuicao">Funcao que ira cuidar do metodo correto de atribuir o dado a um endereco da lista</param>
/// <returns>TRUE: Inseriu dado| FALSE: Erro na insercao </returns>
boolean_t insereInicioLista(listaE_t* lista, infoLista_t dado, atribuirDado_f metodoAtribuicao) {
	boolean_t conseguiuInserir = FALSE;
	itemListaE_t* novo = malloc(sizeof(itemListaE_t));

	if (novo != NULL) {
		conseguiuInserir = metodoAtribuicao(novo, dado);
		
		if (conseguiuInserir) {
			novo->proxItem = lista->primeiro;

			lista->numItens++;
			lista->primeiro = novo;
		}
	}

	return conseguiuInserir;
}


/// <summary>
///		Funcao para inserir no final de uma lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <param name="dado">Dado do tipo infoLista_t a ser inserido na lista</param>
/// <param name="metodoAtribuicao">Funcao que ira cuidar do metodo correto de atribuir o dado a um endereco da lista</param>
/// <returns>TRUE: Inseriu dado| FALSE: Erro na insercao </returns>
boolean_t insereFimLista(listaE_t* lista, infoLista_t dado, atribuirDado_f metodoAtribuicao) {
	boolean_t conseguiuInserir = FALSE;
	itemListaE_t* novo = malloc(sizeof(itemListaE_t));

	if (novo != NULL) {
		itemListaE_t* atual = lista->primeiro;
		itemListaE_t* anterior = NULL;

		while (atual != NULL) {  //Percorre lista até posição final (NULL).
			anterior = atual;
			atual = atual->proxItem;
		}

		conseguiuInserir = metodoAtribuicao(novo, dado);

		if (conseguiuInserir) {

			if (anterior == NULL) { //Se anterior for NULL, a lista está vazia, então elemento é inserido no inicio.
				novo->proxItem = lista->primeiro;
				lista->primeiro = novo;
			}
			else { //Como a possição final é NULL, o endereço do elemento é atribuido ao penúltimo elemento da lista.
				anterior->proxItem = novo;
			}

			lista->numItens++;
		}
	}

	return conseguiuInserir;
}


/// <summary>
///		Funcao para inserir ordenado em uma lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <param name="dado">Dado do tipo infoLista_t a ser inserido na lista</param>
/// <param name="metodoComparacao">Funcao que ira cuidar do metodo correto de comparar os dados durante a busca da posicao ideal</param>
/// <param name="metodoAtribuicao">Funcao que ira cuidar do metodo correto de atribuir o dado a um endereco da lista</param>
/// <returns>TRUE: Inseriu dado| FALSE: Erro na insercao </returns>
boolean_t insereOrdenado(listaE_t* lista, infoLista_t dado, compararDado_f metodoComparacao, atribuirDado_f metodoAtribuicao) {
	boolean_t conseguiuInserir = FALSE;
	itemListaE_t* novo;
	itemListaE_t* anterior = NULL;
	itemListaE_t* atual = lista->primeiro;

	novo = (itemListaE_t*)(malloc(sizeof(itemListaE_t)));

	if (novo != NULL) {

		while (atual != NULL && metodoComparacao(atual->dadoArmazenado, dado) < 0) { //Percorre lista em busca de posição ideal para inserir ou Final da Lista.
			anterior = atual;
			atual = atual->proxItem;
		}

		conseguiuInserir = metodoAtribuicao(novo, dado);

		if (conseguiuInserir) {

			if (anterior == NULL) { //Se anterior for NULL, a lista está vazia, então elemento é inserido no inicio.
				novo->proxItem = lista->primeiro;
				lista->primeiro = novo;
			}
			else {	//Se anterior contém um endereço, o elemento atual é inserido após ele.
				novo->proxItem = anterior->proxItem;
				anterior->proxItem = novo;
			}

			lista->numItens++;
			conseguiuInserir = TRUE;
		}
	}

	return conseguiuInserir;
}


/// <summary>
///		Funcao que imprime uma lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <param name="metodoImpressao">Funcao que ira cuidar do metodo correto de imprimir os dados de uma lista</param>
void imprimeLista(listaE_t* lista, imprimirDado_f metodoImpressao) {
	itemListaE_t* atual = lista->primeiro;

	while (atual != NULL) {
		metodoImpressao(atual->dadoArmazenado);
		atual = atual->proxItem;
	}
}


/// <summary>
///		Funcao que busca um item semelhante na lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <param name="dado">Dado do tipo infoLista_t a ser inserido na lista</param>
/// <param name="metodoComparacao">Funcao que ira cuidar do metodo correto de comparar os dados durante a busca da posicao ideal</param>
/// <returns>Endereco de um itemListaE_t que possui o dado buscado</returns>
itemListaE_t* buscarItemLista(listaE_t* lista, infoLista_t dado, compararDado_f metodoComparacao) {
	itemListaE_t* atual, * posicaoEncontrada = NULL;
	boolean_t encontrado = FALSE;

	for (atual = lista->primeiro; atual != NULL && !encontrado; atual = atual->proxItem) { //Percorre lista em busca de item.
		if (metodoComparacao(atual->dadoArmazenado, dado) == 0) {
			posicaoEncontrada = atual;
			encontrado = TRUE; //Se encontrado iterrompe o laço alterando status de variavel booleana.
		}
	}

	return posicaoEncontrada; //Retorna posição onde foi localizado item.
}


/// <summary>
///		Funcao para remover um item da lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
/// <param name="dado">Dado do tipo infoLista_t a ser inserido na lista</param>
/// <param name="metodoComparacao">Funcao que ira cuidar do metodo correto de comparar os dados durante a busca da posicao ideal</param>
/// <returns>TRUE: Dado removido | FALSE: Nao tinha dado/Erro remocao</returns>
boolean_t retiraItemLista(listaE_t* lista, infoLista_t dado, compararDado_f metodoComparacao) {

	boolean_t itemRemovido = FALSE;
	itemListaE_t* anterior = lista->primeiro;
	itemListaE_t* atual = lista->primeiro;

	// Busca pelo item até encontrá-lo ou a lista chegar no final
	while ((atual != NULL) && metodoComparacao(atual->dadoArmazenado, dado) == 0) {
		anterior = atual;
		atual = atual->proxItem;
	}


	if (atual != NULL) {

		// Se chegou até aqui é porque encontrou e está em <atual>
		if (anterior == NULL) {  // Verifica se é o primeiro

			lista->primeiro = atual->proxItem;
		}
		else {

			anterior->proxItem = atual->proxItem;
		}

		// Libera o espaço alocado pelo atual
		free(atual);

		itemRemovido = TRUE;
	}


	// Retorna a lista
	return itemRemovido;
}


/// <summary>
///		Funcao para liberar lista.
/// </summary>
/// <param name="lista">Endereco de uma variavel do tipo listaE_t</param>
void liberaLista(listaE_t* lista) {

	itemListaE_t* atual = lista->primeiro;

	while (atual != NULL) {
		itemListaE_t* tmp = atual->proxItem;
		free(atual);
		atual = tmp;
	}
}

//-------- Fim Funcoes Lista Encadeada