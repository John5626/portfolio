//TAD TIPO LISTA ENCADEADA      JOAO VICTOR ECOMP
#ifndef LISTA__DP_ENC_H
#define LISTA__DP_ENC_H

#include <stdbool.h>

//Encapsulamento dos dados

typedef struct celula celula;
typedef struct Lista lista_dp;


//OPERAÇOES AUXILIARES

/*Cria uma lista duplamente encadeada
Entrada: Capacidade da lista
Saída: ponteiro para a nova lista criada ou NULL se houver erro na criação
*/
lista_dp* criar_dp();


/*Exibe a lista
Entrada: lista L
Saída: nao tem
*/
void exibir_dp(lista_dp* L);


/*Tamanho da lista (quaISTA_ENCntidade de elementos válidos na lista)
inteiro tamanho(L)
Entrada: lista L
Saída: tamanho da lista, ou seja, a quantidade de itens válidos presentes na lista
*/
int tamanho_dp(lista_dp* L);


/*Verificação de lista vazia
Entrada: lista L
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia_dp(lista_dp* L);


//OPERAÇOES DE INSERÇÂO

/*Inserção no início
Entrada: lista L, elemento e a ser inserido
Saída: sucesso ou falha na operação
*/
bool inserir_inicio_dp(lista_dp* L, int e);

/*
Inserção no meio
Entrada: lista L, elemento e a ser inserido, k-ésima posição onde o
elemento e será inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_meio_dp(lista_dp* L, int e, int k);

/*
Inserção no fim
Entrada: lista L, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_fim_dp(lista_dp* L, int e);


//OPERAÇOES DE REMOÇÃO

/*
Remoção no início e retorna o valor removido
Entrada: lista L e a variavel que armazenará o valor removido
Saída: sucesso ou falha na operação
*/
bool remover_inicio_dp(lista_dp* L, int* removido);


/*
Remoção no meio
Entrada: lista L, k-ésima posição na qual um elemento será removido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool remover_meio_dp(lista_dp* L, int k, int* valor_removido);

/*
Remoção no fim
Entrada: lista L
Saída: sucesso ou falha na operação
*/
bool remover_fim_dp(lista_dp* L, int* valor_removido);


//OPERAÇAO DE BUSCA

/*Busca sequencial
Entrada: lista L, elemento e a ser procurado na lista
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool buscar_seq_dp(lista_dp* L, int e);

lista_dp* liberar_dp(lista_dp* L);

void percorrer_inverso(lista_dp* L);

lista_dp* concaternar(lista_dp* l1, lista_dp* l2);

lista_dp* alternar(lista_dp* l1, lista_dp* l2);

#endif // LISTA_DP_ENC_H


