//TAD TIPO PILHA SEQUENCIAL
//JOAO VICTOR ECOMP

#ifndef PS_INT
#define PS_INT

#include <stdbool.h>

//Encapsulamento dos dados

typedef struct pilha_int pilha_s;


//OPERAÇOES AUXILIARES

/*Cria uma Pilha sequencial de inteiros
Entrada: Capacidade da pilha
Saída: ponteiro para a nova pilha criada com capacidade cap ou NULL se houver erro na criação
*/
pilha_s* criar_ps(int cap);

/*Exibe a frente da Pilha
Entrada: pilha P
Saída: topo da fila
*/
int topo_ps(pilha_s* P);

/*Capacidade da Pilha
Entrada: pilha P
Saída: capacidade da pilha
*/
int capacidade_ps(pilha_s* P);

/*Tamanho da pilha (quantidade de elementos válidos na pilha)
inteiro tamanho(P)
Entrada: pilha P
Saída: tamanho da pilha, ou seja, a quantidade de itens válidos presentes na pilha
*/
int tamanho_ps(pilha_s* P);

/*Verificação de pilha cheia
Entrada: pilha P
Saída: verdadeiro se estiver cheia; falso caso contrário
*/
bool cheia_ps(pilha_s* P);

/*Verificação de pilha vazia
Entrada: pilha P
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia_ps(pilha_s* P);



/*
Inserção na pilha
Entrada: pilha P, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_ps(pilha_s* P, int e);


//OPERAÇOES DE REMOÇÃO

/*
Remoção na pilha
Entrada: pilha P e a variavel que armazenará o valor removido
Saída: sucesso ou falha na operação
*/
bool remover_ps(pilha_s* P, int* removido);

pilha_s* liberar_ps(pilha_s* P);

/*
Libera a memoria alocada do tipo pilha_s
Entrada: pilha P
Saída: retorna NULL
*/
#endif // PS_INT.H


