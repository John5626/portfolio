//TAD TIPO LISTA SEQUENCIAL DE PONTOS
//JOAO VICTOR ECOMP
#ifndef LISTA_SEQ_PONTOS_H
#define LISTA_SEQ_PONTOS_H
#include <stdbool.h>

//ENCAPSULAMENTO DOS DADOS
typedef struct pontos pontos2D;
typedef struct lista lista_P2D;

//PROTÓTIPOS

/*Cria um lista sequencial do tipo pontos
Entrada: Capacidade da lista
Saída: ponteiro para a nova lista criada com capacidade cap ou NULL se houver erro na criação
*/
lista_P2D* criar(int cap);

/*Exibe um lista sequencial do tipo pontos
Entrada: ponteiro para o tipo lista de pontos
Saída: ponteiro para o tipo lista de pontos
*/
void exibir(lista_P2D* L);


                                                //OPERAÇOES AUXILIARES

/*Capacidade da lista de pontos
Entrada: lista L
Saída: capacidade da lista
*/
int capacidade(lista_P2D* L);

/*Tamanho da lista (quantidade de elementos válidos na lista) de pontos
Entrada: lista L
Saída: tamanho da lista, ou seja, a quantidade de itens válidos presentes na lista
*/
int tamanho(lista_P2D* L);

/*Verificação de lista cheia
Entrada: lista L
Saída: verdadeiro se estiver cheia; falso caso contrário
*/
bool cheia(lista_P2D* L);

/*Verificação de lista vazia
Entrada: lista L
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia(lista_P2D* L);


//OPERAÇOES DE INSERÇÂO

/*Inserção no início
Entrada: lista L, coordenadas (x,y) a serem inseridas
Saída: sucesso ou falha na operação
*/
bool inserir_inicio(lista_P2D* L, float x, float y);

/*
Inserção no meio
Entrada: lista L, lista L, coordenadas (x,y) a serem inseridas, k-ésima posição onde x,y serão inseridos
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_meio(lista_P2D* L, float x, float y, int k);

/*
Inserção no fim
Entrada: lista L, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_fim(lista_P2D* L, float x, float y);


                                                    //OPERAÇOES DE REMOÇÃO

/*
Remoção no início e retorna o valor removido
Entrada: lista L e a variaveis que armazenarão x,y
Saída: sucesso ou falha na operação
*/
bool remover_inicio(lista_P2D* L, float* x_rem, float* y_rem);


/*
Remoção no meio
Entrada: lista L, k-ésima posição na qual um elemento será removido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool remover_meio(lista_P2D* L, int k);

/*
Remoção no fim
Entrada: lista L
Saída: sucesso ou falha na operação
*/
bool remover_fim(lista_P2D* L);


                                                    //OPERAÇAO DE BUSCA

/*Busca sequencial
Entrada: lista L, elemento e a ser procurado na lista
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool buscar_seq(lista_P2D* L, float x, float y);

#endif // LISTA_SEQ_PONTOS_H
