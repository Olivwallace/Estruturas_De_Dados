/**
 * @file   tabelaHash.c (arquivo alterado para receber ponteiros de funcoes) arquivo base (tabelaHash_LE.c)
 * @brief  Implementação da tabela hash utilizando
 *         Hash Aberto e Lista Encadeada.
 */

//------- Inclusoes

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ListaE.h"
#include "tabelaHash.h"

//-------- Fim Inclusoes


//-------- Funcoes Hash Aberto

/// <summary>
///     Funcao para inicializar hash aberto.
/// </summary>
/// <param name="tableHash">Endereco de uma variavel tableHash_t</param>
/// <param name="funcaoHash">Funcao que sera responsavel por calcular hash dos dados</param>
/// <param name="tamanho">Tamanho da tabela Hash</param>
void inicializaHashAberto(tableHash_t* tableHash, uint32_t tamanho, funcaoHash_f funcaoHash, 
                            imprimirDado_f metodoImpressao, compararDado_f metodoComparacao, atribuirDado_f metodoAtribuicao){

    uint32_t i;

    // Cria o espaço para itens da tabela, que contem uma lista interna.
    tableHash->tabela = malloc(sizeof(itemTabela_t) * tamanho);

    if (tableHash->tabela != NULL) {
        
        tableHash->tamanho = tamanho;
        
        tableHash->funcoes.funcaoHash = funcaoHash;
        tableHash->funcoes.funcaoAtribui = metodoAtribuicao;
        tableHash->funcoes.funcaoCompara = metodoComparacao;
        tableHash->funcoes.funcaoImprime = metodoImpressao;

        tableHash->numItens = 0;

        // Inicializa as listas
        for (i = 0; i < tamanho; i++) {
            inicializaLista(&tableHash->tabela[i].listaCaixa);
        }

    }
}


/// <summary>
///     Função que finaliza uma tabela hash.
/// </summary>
/// <param name="tabHash">Endereco de variavel do tipo tableHash_t</param>
void liberaHash(tableHash_t* tabHash) {

    uint32_t i;

    // Destroi as listas
    for (i = 0; i < tabHash->tamanho; i++) {
        liberaLista(&(tabHash->tabela[i].listaCaixa));
    }

    // Libera o espaço para as listas
    free(tabHash->tabela);

    tabHash->funcoes.funcaoHash = NULL;
    tabHash->funcoes.funcaoAtribui = NULL;
    tabHash->funcoes.funcaoCompara = NULL;
    tabHash->funcoes.funcaoImprime = NULL;

    tabHash->tabela = NULL;
    tabHash->tamanho = 0;
    tabHash->numItens = 0;
}


/// <summary>
///     
/// </summary>
/// <param name="tabHash">Endereco da tabela</param>
/// <param name="posicao">Posicao previamente calculada para recalculo</param>
/// <returns>Nova posicao recalculada baseada no tamanho</returns>
static posicaoHash_t tabelaHashPosicaoSegura(tableHash_t* tabHash, posicaoHash_t posicao) {
    return posicao % tabHash->tamanho;
}


/// <summary>
/// Função que insere um item na tabela hash.
/// </summary>
/// <param name="tableHash">Endereço da tabela.</param>
/// <param name="dado">Item a ser inserido.</param>
/// <returns> TRUE: Se inseriu | FALSE: Já Presente </returns>
boolean_t insereHashAberto(tableHash_t* tableHash, infoTable_t dado) {
      
    posicaoHash_t posicao;
    infoTable_t* itemLista;

    // Calcula a posição onde inserir o elemento
    posicao = tableHash->funcoes.funcaoHash(dado);
    posicao = tabelaHashPosicaoSegura(tableHash, posicao);
        
    // Verifica se o item já está na lista
    // Procura na lista
    itemLista =  (infoTable_t *) buscarItemLista(&tableHash->tabela[posicao], dado, tableHash->funcoes.funcaoCompara);
    if (itemLista == NULL) return FALSE;

    // Vai na lista e insere
    insereInicioLista(&tableHash->tabela[posicao], dado, tableHash->funcoes.funcaoAtribui);

    // Se chegou até aqui é porque conseguiu inserir
    tableHash->numItens++;
    return TRUE;
}

/// <summary>
///     Funcao que verifica se dado ja pertence a tabela.
/// </summary>
/// <param name="tabelaHash">Endereco da tabela</param>
/// <param name="dado">Dado a ser encontrado</param>
/// <returns>TRUE: Se item presente | FALSE: Item nao pertece a tabela</returns>
boolean_t buscaHashAberto(tableHash_t* tabelaHash, infoTable_t dado) {

    posicaoHash_t posicao;
    infoTable_t* itemLista;

    // Calcula a posição onde inserir o elemento
    posicao = tabelaHash->funcoes.funcaoHash(dado);
    posicao = tabelaHashPosicaoSegura(tabelaHash, posicao);

    // Procura na lista
    itemLista = (infoTable_t*) buscarItemLista(&tabelaHash->tabela[posicao], dado, tabelaHash->funcoes.funcaoCompara);

    // Verifica se encontrou
    return itemLista != NULL;
}


/// <summary>
///     Funcao que remove item do hash.
/// </summary>
/// <param name="tableHash">Endereco da tabela Hash</param>
/// <param name="dado">Dado a ser removido</param>
/// <returns>TRUE: Item removido | FALSE: Item nao removido</returns>
boolean_t removeHashAberto(tableHash_t* tableHash, infoTable_t dado) {

    posicaoHash_t posicao;
    boolean_t removeu;

    // Calcula a posição onde inserir o elemento
    posicao = tableHash->funcoes.funcaoHash(dado);
    posicao = tabelaHashPosicaoSegura(tableHash, posicao);

    // Tenta remover
    removeu = retiraItemLista(&tableHash->tabela[posicao], dado, tableHash->funcoes.funcaoCompara);
    if (removeu) tableHash->numItens--;
    return removeu;
}


/// <summary>
/// Função que imprime todos os elementos da tabela hash.
/// </summary>
/// <param name="tabHash">Endereço da tabela.</param>
void imprimeHashAberto(tableHash_t* tableHash) {

    uint32_t i;

    for (i = 0; i < tableHash->tamanho; i++) {
        imprimeLista(&tableHash->tabela[i], tableHash->funcoes.funcaoImprime);
    }
}

//-------- Fim Funcoes Hash Aberto