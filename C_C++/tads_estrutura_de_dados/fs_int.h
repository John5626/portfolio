//TAD TIPO fila SEQUENCIAL
//JOAO VICTOR ECOMP

#ifndef FS_INT
#define FS_INT

#include <stdbool.h>

//Encapsulamento dos dados

typedef struct fila_int fila_s;


//OPERAÇOES AUXILIARES

/*Cria uma Fila sequencial de inteiros
Entrada: Capacidade da fila
Saída: ponteiro para a nova fila criada com capacidade cap ou NULL se houver erro na criação
*/
fila_s* criar_fs(int cap);

/*Exibe a fila
Entrada: fila L
Saída: nao tem
*/
int frente_fs(fila_s* L);

/*Capacidade da fila
Entrada: fila L
Saída: capacidade da fila
*/
int capacidade_fs(fila_s* L);

/*Tamanho da fila (quantidade de elementos válidos na fila)
inteiro tamanho(L)
Entrada: fila L
Saída: tamanho da fila, ou seja, a quantidade de itens válidos presentes na fila
*/
int tamanho_fs(fila_s* L);

/*Verificação de fila cheia
Entrada: fila L
Saída: verdadeiro se estiver cheia; falso caso contrário
*/
bool cheia_fs(fila_s* L);

/*Verificação de fila vazia
Entrada: fila L
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia_fs(fila_s* L);



/*
Inserção na fila
Entrada: fila L, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_fs(fila_s* L, int e);


//OPERAÇOES DE REMOÇÃO

/*
Remoção na fila
Entrada: fila L e a variavel que armazenará o valor removido
Saída: sucesso ou falha na operação
*/
bool remover_fs(fila_s* L, int* removido);

fila_s* liberar_fs(fila_s* F);

/*
Libera a memoria alocada do tipo fila_s
Entrada: fila L
Saída: retorna NULL
*/
#endif // FS_INT.H


