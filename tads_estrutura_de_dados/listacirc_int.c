//IMPLEMENTAÇÃO TAD LISTA CIRCURLAR
#include <stdio.h>
#include <stdlib.h>

#include "listacirc_int.h"

struct listacirc_int
{
    int* dados;
    int inicio, fim, cap;
};

L_circ* criar_lc(int cap){
    L_circ* nova = (L_circ*) malloc(sizeof(L_circ));
    if(nova == NULL)
        return NULL;
    
    nova->dados = (int*) malloc(cap * sizeof(int));
    if(nova->dados == NULL){
        free(nova);
        return NULL;
    }

    nova->cap = cap;
    nova->inicio = -1;
    nova->fim = 0;

    return nova;

}

int capacidade_lc(L_circ* L){
    return L->cap;
}

int tamanho_lc(L_circ* L){
    if(L->inicio == -1)
        return 0;
    
    if(L->fim > L->inicio)
        return L->fim - L->inicio;

    else
        return L->fim - L->inicio + capacidade_lc(L);
}

bool cheia_lc(L_circ* L){
    if(tamanho_lc(L) == capacidade_lc(L))
        return true;
    
    return false;
}

bool vazia_lc(L_circ* L){
    if(tamanho_lc(L) == 0)
        return true;
    
    return false;
}

bool inserir_lc(L_circ* L, int ctd){
    if(cheia_lc(L))
        return false;

    if(vazia_lc(L)){
        L->inicio = 0;
        L->fim = 0;
    }    

    L->dados[L->fim] = ctd;
    L->fim = L->fim + 1;

    if(L->fim == capacidade_lc(L))
        L->fim = 0;
    
    return true;
}

void esvaziar_lc(L_circ* L){
    L->inicio = -1;
    L->fim = 0;
}

bool remover_lc(L_circ* L, int* rem){
    if(vazia_lc(L))
        return false;
    
    *rem = L->dados[L->inicio];
    
    L->inicio++;

    if(L->inicio == capacidade_lc(L))
        L->inicio = 0;
    
    if(L->inicio == L->fim){
        esvaziar_lc(L);
    }

    return true;
}

void exibir_lc(L_circ* L){
    if(L == NULL || vazia_lc(L))
        return;
    
    int id_pos = L->inicio;

    printf("\n");
    //indices do vetor
    for(int i = 0; i < tamanho_lc(L); i++){
        printf("%2d ", id_pos++);
        if(id_pos == capacidade_lc(L))
            id_pos = 0;
    }


    printf("\n");
    //Elementos do vetor
    id_pos = L->inicio;
    for(int i = 1; i <= tamanho_lc(L); i++){
        printf("%2d ", L->dados[id_pos++]);
        if(id_pos == capacidade_lc(L))
            id_pos = 0;
    }
    printf("\n");
}

L_circ* liberar_lc(L_circ* L){
    free(L);
    return NULL;
}

bool buscar_lc(L_circ* L, int valor){
    if(L == NULL || vazia_lc(L))
        return false;

    int id_pos = L->inicio;
    for(int i = 0; i < tamanho_lc(L); i++){
        if(id_pos == capacidade_lc(L))
            id_pos = 0;
        printf("%d ", id_pos);
        if(L->dados[id_pos] == valor)
            return true;
        id_pos++;
    }
    return false;
}





