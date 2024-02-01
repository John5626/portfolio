//IMPLEMENTAÇAO TAD MAX_HEAP            JOAO VICTOR SOUZA - ECOMP
#include <stdio.h>
#include <stdlib.h>

#include "max_heap.h"
#define FLAG_ERRO -1


/* Retorna o índice do filho esquerdo de um nó pai no heap.
Função estática interna.
Entrada: ponteiro para a estrutura do heap, índice do nó pai.
Saída: índice do filho esquerdo. */
static int indice_filho_esq(heap_max* H, int id_pai);

/* Retorna o índice do filho direito de um nó pai no heap.
Função estática interna.
Entrada: ponteiro para a estrutura do heap, índice do nó pai.
Saída: índice do filho direito. */
static int indice_filho_dir(heap_max* H, int id_pai);

/* Retorna o índice do pai de um nó filho no heap.
Função estática interna.
Entrada: ponteiro para a estrutura do heap, índice do nó filho.
Saída: índice do pai. */
static int indice_pai(heap_max* H, int id_filho);

/* Realiza a manutenção da propriedade de heap máximo a partir de um nó pai no heap.
Função estática interna.
Entrada: ponteiro para a estrutura do heap, índice do nó pai.
Saída: nenhum (o heap é reorganizado se necessário). */
static void max_heapify(heap_max* H, int id_pai);

/* Insere um elemento no final do heap, mantendo a propriedade de heap máximo.
Função estática interna.
Entrada: ponteiro para a estrutura do heap, valor a ser inserido.
Saída: verdadeiro se a inserção foi realizada com sucesso, falso caso contrário. */
static bool inserir_fim_heap(heap_max* H, unsigned int v);

struct heap{
    unsigned int* dados;
    unsigned int cap;
    unsigned int qtde;
};


heap_max* criar_heap(int cap){
    heap_max* nova = (heap_max*) malloc(sizeof(heap_max));
    if(nova == NULL)
        return NULL;
    
    nova->dados = (int*) malloc(cap * sizeof(int));
    if(nova->dados == NULL){
        free(nova);
        return NULL;
    }

    nova->qtde = 0;
    nova->cap = cap;

    return nova;
}

bool cheia_heap(heap_max* H){
    if(H == NULL)
        return false;

    return H->qtde == H->cap;
    
}

bool vazia_heap(heap_max* H){
    if(H == NULL)
        return false;
    
    return H->qtde == 0;
}

bool esvaziar_heap(heap_max* H){
    if(H == NULL)
        return false;

    H->qtde = 0;
    return true;
}

void exibir_heap(heap_max* H){
    int nivel = 1;
    for(int i = 1; i <= H->qtde; i++){
        if(i == nivel){
            printf("\n");
            nivel = 2*i;
        }
        printf("%d ", H->dados[i - 1]);
    }
}

void liberar_heap(heap_max** H){
    free((*H)->dados);
    free(*H);
    *H = NULL;
}

bool inserir_heap(heap_max* H, unsigned int v){
    if(!inserir_fim_heap(H, v)){
        return false;
    }

    int id_v = H->qtde - 1;          //indice atual de v
    int id_pai = indice_pai(H, id_v);//indice atual do pai de v

    while(id_pai >= 0 && H->dados[id_v] > H->dados[id_pai]){
        trocar_heap(H, id_v, id_pai);
        id_v = id_pai;
        id_pai = indice_pai(H, id_v);
    }

    return true;
}


void trocar_heap(heap_max* H, int id1, int id2){
    int aux = H->dados[id1];
    H->dados[id1] = H->dados[id2];
    H->dados[id2] = aux;
}

void inserir_vet_heap(heap_max* H, int* vet, unsigned int n){
    for(int i = 0; i < n; i++)
        inserir_heap(H, vet[i]);
}

int remover_heap(heap_max* H){
    if(H == NULL || vazia_heap(H))
        return FLAG_ERRO;
    
    int retorno = H->dados[0];
    H->dados[0] = H->dados[H->qtde - 1];
    H->qtde--;

    max_heapify(H, 0);

    return retorno;

}

int tamanho_heap(heap_max* H){
    if(H == NULL)
        return FLAG_ERRO;

    return H->qtde;
}


//FUNÇOES ESTATICAS
static int indice_filho_esq(heap_max* H, int id_pai){        //indice de um pai
    int esq = 2* id_pai + 1;
    if(esq >= H->qtde){
        return FLAG_ERRO;
    }
    return esq;
}

static int indice_filho_dir(heap_max* H, int id_pai){        //indice de um pai
    int dir = 2* id_pai + 2;
    if(dir >= H->qtde){
        return FLAG_ERRO;
    }
    return dir;
}

static int indice_pai(heap_max* H, int id_filho){
    if(id_filho <= 0)
        return FLAG_ERRO;

    return (id_filho - 1) / 2;
}

static void max_heapify(heap_max* H, int id_pai){
    if(H == NULL || id_pai < 0 || id_pai >= H->qtde)
        return;

    int id_fesq = indice_filho_esq(H, id_pai);
    int id_fdir = indice_filho_dir(H, id_pai);

    if(id_fesq >= H->qtde)
        return;

    while((id_fesq > 0 && H->dados[id_pai] < H->dados[id_fesq]) ||
           (id_fdir > 0 && H->dados[id_pai] < H->dados[id_fdir])){

        if(id_fdir >= H->qtde){
            trocar_heap(H, id_pai, id_fesq);
            return;
        }
        else if (H->dados[id_fesq] >= H->dados[id_fdir]){
            trocar_heap(H, id_pai, id_fesq);
            id_pai = id_fesq;

        }else{
            trocar_heap(H, id_pai, id_fdir);
            id_pai = id_fdir;
        }
        id_fesq = indice_filho_esq(H, id_pai);

        if(id_fesq >= H->qtde)
            return;
        id_fdir = indice_filho_dir(H, id_pai);
    
    }
}

static bool inserir_fim_heap(heap_max* H, unsigned int v){
    if(H == NULL || cheia_heap(H))
        return false;

    H->dados[H->qtde] = v;
    H->qtde++;

    return true;
}


