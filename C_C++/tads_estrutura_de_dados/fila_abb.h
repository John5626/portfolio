//TAD TIPO FILA ENCADEADA ABB
//JOAO VICTOR ECOMP
#ifndef FILAABB_H
#define FILAABB_H

#include <stdbool.h>
#include "abb_int.h"

//Encapsulamento dos dados

typedef struct celula celula;
typedef struct fila fila_enc;


//OPERAÇOES AUXILIARES

/*Cria uma Fila encadeada
Entrada: Capacidade da fila
Saída: ponteiro para a nova fila criada ou NULL se houver erro na criação
*/
fila_enc* criar_enc();


/*retorna a frente
Entrada: fila F
Saída: nao tem
*/
no_arv* frente_enc(fila_enc* F);


/*Tamanho da Fila (quantidade de elementos válidos na fila)
inteiro tamanho(F)
Entrada: Fila F
Saída: tamanho da fila, ou seja, a quantidade de itens válidos presentes na fila
*/
int tamanho_enc(fila_enc* F);


/*Verificação de fila vazia
Entrada: Fila F
Saída: verdadeiro se estiver vazia; falso caso contrário
*/
bool vazia_enc(fila_enc* F);


/*
Inserção no fim
Entrada: fila F, elemento e a ser inserido
Saída: sucesso (verdadeiro) ou falha (falso) na operação
*/
bool inserir_enc(fila_enc* F, no_arv* no);


//OPERAÇOES DE REMOÇÃO

/*
Remoção no início e retorna o valor removido
Entrada: fila F e a variavel que armazenará o valor removido
Saída: sucesso ou falha na operação
*/
bool remover_enc(fila_enc* F, no_arv* removido);

fila_enc* liberar_enc(fila_enc* F);


#endif //FILAABB_H