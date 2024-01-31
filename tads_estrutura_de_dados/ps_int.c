//IMPLEMENTAÇÃO TAD TIPO fila SEQUENCIAL
//JOAO VICTOR ECOMP

#include <stdio.h>
#include <stdlib.h>
#include "ps_int.h"


struct pilha_int{
    int *dados;
    int qtde, cap;
};

pilha_s* criar_ps(int cap){
    pilha_s* nova_ps = (pilha_s*) malloc(sizeof(pilha_s));
    if(nova_ps != NULL)
    {
        nova_ps->dados = (int*) malloc(cap * sizeof(int));
        if(nova_ps->dados == NULL){
            free(nova_ps);
            return NULL;
        }

        nova_ps->cap = cap;
        nova_ps->qtde = 0;
        
    }
    return nova_ps;
    
}

int topo_ps(pilha_s* P){
    if(vazia_ps(P))
        printf("Pilha vazia");
    
    return P->dados[P->qtde-1];
    
}

int capacidade_ps(pilha_s* P){

    return P->cap;
}

int tamanho_ps(pilha_s* P){
    return P->qtde;

}

bool cheia_ps(pilha_s* P){
    if(P->cap == P->qtde)
        return true;
    return false;

}

bool vazia_ps(pilha_s* P){
    if(P->qtde == 0) 
        return true;

    return false;
}

bool inserir_ps(pilha_s* P, int e){
    if(cheia_ps(P))
        return false;
    
    P->dados[P->qtde] = e;
    P->qtde++;
    return true;
}

bool remover_ps(pilha_s* P, int* removido){
    if(vazia_ps(P))
        return false;

    *removido = P->dados[P->qtde-1];

    P->qtde--;
    return true;   
    
}

pilha_s* liberar_ps(pilha_s* P){
    free(P);
    return NULL;
}