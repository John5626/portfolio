//TAD TIPO LISTA SEQUENCIAL
//JOAO VICTOR ECOMP

#ifndef LISTA_SEQ
#define LISTA_SEQ

#include <stdbool.h>

//Encapsulamento dos dados

typedef struct lista lista_s;


//OPERAÇOES AUXILIARES

/*Cria uma lista sequencial
Entrada: Capacidade da lista
Saída: ponteiro para a nova lista criada com capacidade cap ou NULL se houver erro na criação
*/
lista_s* criar(int cap);

/*Exibe a lista
Entrada: lista L
Saída: nao tem
*/
void exibir(lista_s* L);

/*Capacidade da lista
Entrada: lista L
Saída: capacidade da lista
*/
int capacidade(lista_s* L);

/*Tamanho da lista (quantidade de elementos válidos na lista)
inteiro tamanho(L)
Entrada: lista L
Saída: tamanho da lista, ou seja, a quantidade de itens válidos presentes na lista
*/
int tamanho(lista_s* L);

/*Verificação de lista cheia
Entrada: lista L
Saída: verdadeiro se estiver cheia; falso caso contrário
*/
bool cheia(lista_s* L);

/*Verificação de lista vazia
Entrada: lista L
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia(lista_s* L);


//OPERAÇOES DE INSERÇÂO

/*Inserção no início
Entrada: lista L, elemento e a ser inserido
Saída: sucesso ou falha na operação
*/
bool inserir_inicio(lista_s* L, int e);

/*
Inserção no meio
Entrada: lista L, elemento e a ser inserido, k-ésima posição onde o
elemento e será inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_meio(lista_s* L, int e, int k);

/*
Inserção no fim
Entrada: lista L, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_fim(lista_s* L, int e);


//OPERAÇOES DE REMOÇÃO

/*
Remoção no início e retorna o valor removido
Entrada: lista L e a variavel que armazenará o valor removido
Saída: sucesso ou falha na operação
*/
bool remover_inicio(lista_s* L, int* removido);


/*
Remoção no meio
Entrada: lista L, k-ésima posição na qual um elemento será removido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool remover_meio(lista_s* L, int k);

/*
Remoção no fim
Entrada: lista L
Saída: sucesso ou falha na operação
*/
bool remover_fim(lista_s* L);


//OPERAÇAO DE BUSCA

/*Busca sequencial
Entrada: lista L, elemento e a ser procurado na lista
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool buscar_seq(lista_s* L, int e);

/*Quantidade de elementos impares na lista
Entrada: lista L
Saída: quantidade de impares
*/
int qtde_impares_lst(lista_s *l);

#endif // LISTA_SEQ


