//TAD MAX_HEAP            JOAO VICTOR SOUZA - ECOMP
#ifndef MAX_HEAP_H
#define MAX_HEAP_H
#include <stdbool.h>

typedef struct heap heap_max;

/* Cria um heap máximo com capacidade especificada.
Entrada: capacidade do heap.
Saída: ponteiro para a estrutura do heap criado. */
heap_max* criar_heap(int cap);

/* Verifica se o heap está cheio.
Entrada: ponteiro para a estrutura do heap.
Saída: verdadeiro se o heap estiver cheio, falso caso contrário. */
bool cheia_heap(heap_max* H);

/* Verifica se o heap está vazio.
Entrada: ponteiro para a estrutura do heap.
Saída: verdadeiro se o heap estiver vazio, falso caso contrário. */
bool vazia_heap(heap_max* H);

/* Esvazia o heap, removendo todos os elementos.
Entrada: ponteiro para a estrutura do heap.
Saída: verdadeiro se o heap foi esvaziado com sucesso, falso caso contrário. */
bool esvaziar_heap(heap_max* H);

/* Exibe os elementos do heap.
Entrada: ponteiro para a estrutura do heap.
Saída: nenhum (os elementos são exibidos na saída padrão). */
void exibir_heap(heap_max* H);

/* Libera a memória alocada para o heap.
Entrada: ponteiro para o ponteiro da estrutura do heap.
Saída: nenhum (a memória é liberada). */
void liberar_heap(heap_max** H);

/* Insere um elemento no heap.
Entrada: ponteiro para a estrutura do heap, valor a ser inserido.
Saída: verdadeiro se a inserção foi realizada com sucesso, falso caso contrário. */
bool inserir_heap(heap_max* H, unsigned int v);

/* Troca dois elementos no heap.
Entrada: ponteiro para a estrutura do heap, índices dos elementos a serem trocados.
Saída: nenhum (os elementos são trocados dentro do heap). */
void trocar_heap(heap_max* H, int id1, int id2);

/* Insere um vetor de elementos no heap.
Entrada: ponteiro para a estrutura do heap, vetor de elementos, número de elementos.
Saída: nenhum (os elementos do vetor são inseridos no heap). */
void inserir_vet_heap(heap_max* H, int* vet, unsigned int n);

/* Remove o elemento máximo do heap.
Entrada: ponteiro para a estrutura do heap.
Saída: valor do elemento removido. */
int remover_heap(heap_max* H);

/* Retorna o tamanho atual do heap.
Entrada: ponteiro para a estrutura do heap.
Saída: tamanho atual do heap. */
int tamanho_heap(heap_max* H);

#endif // MAX_HEAP_H