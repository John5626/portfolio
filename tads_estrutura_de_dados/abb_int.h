//TAD ARVORE BINARIA DE BUSCA           JOAO VICTOR SOUZA - ECOMP
#ifndef ABB_INT_H
#define ABB_INT_H
#include <stdbool.h>

//Encapsulamento do No
typedef struct no no_arv;

/* Cria uma nova árvore binária de busca
Entrada: valor a ser armazenado no nó raiz.
Saída: Retorna um ponteiro para o nó raiz da árvore criada. 
*/
no_arv* criar_abb(int valor);


/* Insere um novo nó com o valor especificado na árvore binária de busca.
Entrada: ponteiro para o nó raiz e valor a ser inserido na árvore
Saída: Retorna o ponteiro para o nó raiz atualizado. 
*/
no_arv* inserir_abb(no_arv* no, int valor);


/* Percorre a árvore binária de busca em ordem e imprime os valores armazenados nos nós.
Entrada: ponteiro para o nó raiz da árvore a ser percorrida.
Saída: Nenhum.
*/
void percorrer_abb(no_arv* no);


/* Encontra o nó com o valor mínimo na árvore binária de busca.
Entrada: ponteiro para o nó raiz da árvore.
Saída: Retorna o ponteiro para o nó com o valor mínimo na árvore. 
*/
no_arv* minimo_abb(no_arv* no);


/* Verifica se um determinado valor está presente na árvore binária de busca.
Entrada: ponteiro para o nó e valor a ser buscado na árvore.
Saída: Retorna true se o valor estiver presente na árvore, ou false caso contrário. 
*/
bool buscar_abb(no_arv* no, int valor);


/* Realiza a busca em largura na árvore binária de busca e imprime os valores dos nós.
Entrada: ponteiro para o nó raiz da árvore a ser percorrida.
Saída: Nenhum. 
*/
void busca_largura_abb(no_arv* no);


/* Remove o nó com o valor especificado da árvore binária de busca.
Entrada: ponteiro para o nó raiz e valor a ser removido da árvore.
Saída: Retorna o ponteiro para o nó raiz atualizado após a remoção. 
*/
no_arv* remover_abb(no_arv* n, int valor);


/* Libera a memória alocada para a árvore binária de busca.
Entrada: ponteiro para o nó raiz da árvore a ser liberada.
Saída: Nenhum. 
*/
void liberar_abb(no_arv* n);

#endif //ABB_INT_H