// TAD LISTA CIRCULAR
#ifndef LISTACIRC_INT
#define LISTACIRC_INT
#include <stdbool.h>

//Encapsulamento dos dados
typedef struct listacirc_int L_circ;

L_circ* criar_lc(int cap);

int capacidade_lc(L_circ* L);

int tamanho_lc(L_circ* L);

bool cheia_lc(L_circ* L);

bool vazia_lc(L_circ* L);

bool inserir_lc(L_circ* L, int ctd);

void esvaziar_lc(L_circ* L);

bool remover_lc(L_circ* L, int* rem);

void exibir_lc(L_circ* L);

L_circ* liberar_lc(L_circ* L);

bool buscar_lc(L_circ* L, int valor);

#endif // LISTACIRC_INT
