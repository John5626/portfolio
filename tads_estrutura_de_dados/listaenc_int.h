//TAD TIPO LISTA ENCADEADA
//JOAO VICTOR ECOMP

#ifndef LISTA_ENC
#define LISTA_ENC

#include <stdbool.h>

//Encapsulamento dos dados

typedef struct celula celula;
typedef struct Lista lista_le;


//OPERAÇOES AUXILIARES

/*Cria uma lista encadeada
Entrada: Capacidade da lista
Saída: ponteiro para a nova lista criada ou NULL se houver erro na criação
*/
lista_le* criar_le();


/*Exibe a lista
Entrada: lista L
Saída: nao tem
*/
void exibir_le(lista_le* L);


/*Tamanho da lista (quantidade de elementos válidos na lista)
inteiro tamanho(L)
Entrada: lista L
Saída: tamanho da lista, ou seja, a quantidade de itens válidos presentes na lista
*/
int tamanho_le(lista_le* L);


/*Verificação de lista vazia
Entrada: lista L
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia_le(lista_le* L);


//OPERAÇOES DE INSERÇÂO

/*Inserção no início
Entrada: lista L, elemento e a ser inserido
Saída: sucesso ou falha na operação
*/
bool inserir_inicio_le(lista_le* L, int e);

/*
Inserção no meio
Entrada: lista L, elemento e a ser inserido, k-ésima posição onde o
elemento e será inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_meio_le(lista_le* L, int e, int k);

/*
Inserção no fim
Entrada: lista L, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_fim_le(lista_le* L, int e);


//OPERAÇOES DE REMOÇÃO

/*
Remoção no início e retorna o valor removido
Entrada: lista L e a variavel que armazenará o valor removido
Saída: sucesso ou falha na operação
*/
bool remover_inicio_le(lista_le* L, int* removido);


/*
Remoção no meio
Entrada: lista L, k-ésima posição na qual um elemento será removido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool remover_meio_le(lista_le* L, int k, int* valor_removido);

/*
Remoção no fim
Entrada: lista L
Saída: sucesso ou falha na operação
*/
bool remover_fim_le(lista_le* L, int* valor_removido);


//OPERAÇAO DE BUSCA

/*Busca sequencial
Entrada: lista L, elemento e a ser procurado na lista
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool buscar_seq_le(lista_le* L, int e);

lista_le* liberar_le(lista_le* L);



#endif // LISTA_ENC


