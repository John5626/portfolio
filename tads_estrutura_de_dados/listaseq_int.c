//IMPLEMENTAÇÃO TAD TIPO LISTA SEQUENCIAL
//JOAO VICTOR ECOMP

#include <stdio.h>
#include <stdlib.h>
#include "listaseq_int.h"


struct lista{
    int *dados;
    int qtde, cap;
};

lista_s* criar(int cap){
    lista_s* nova_lista = (lista_s*) malloc(sizeof(lista_s));
    if(nova_lista != NULL)
    {
        nova_lista->dados = (int*) malloc(cap * sizeof(int));
        if(nova_lista->dados == NULL){
            free(nova_lista);
            return NULL;
        }

        nova_lista->cap = cap;
        nova_lista->qtde = 0;
        
    }
    return nova_lista;
    
}

void exibir(lista_s* L){
    for(int i = 0; i < tamanho(L); i++)
        printf("%d ", L->dados[i]);

}

bool invalido(lista_s* L, int k) {

    return (k <= 0 || k > tamanho(L) + 1);
}

int capacidade(lista_s* L){

    return L->cap;
}

int tamanho(lista_s* L){
    return L->qtde;

}

bool cheia(lista_s* L){
    if(L->cap == L->qtde)
        return true;
    return false;

}

bool vazia(lista_s* L){
    if(L->qtde == 0) 
        return true;

    return false;
}

bool inserir_inicio(lista_s* L, int e){
    if(cheia(L))
        return false;
    
    for(int i = L->qtde; i > 0; i--)
        L->dados[i] = L->dados[i-1];
    L->dados[0] = e;
    L->qtde++;
    
    return true;
}

bool inserir_meio(lista_s* L, int e, int k){
    if(cheia(L) || k <= 0 || k > tamanho(L)+1)
        return false;
    for(int i = L->qtde; i >= k; i--) {
        L->dados[i] = L->dados[i-1];
        
    }
    L->dados[k-1] = e;
    L->qtde++;
    return true;
}

bool inserir_fim(lista_s* L, int e){
    if(cheia(L))
        return false;
    
    L->dados[L->qtde] = e;
    L->qtde++;
    return true;
}

bool remover_inicio(lista_s* L, int* removido){
    if(vazia(L))
        return false;

    *removido = L->dados[0];

    for(int i = 0; i < tamanho(L)-1; i++){
        L->dados[i] = L->dados[i+1];
        
    }
    L->qtde--;
    return true;   
    
}

bool remover_meio(lista_s* L, int k){
    if(vazia(L) || k < 1 || k > tamanho(L))
        return false;

    for(int i = k; i < tamanho(L); i++){
        L->dados[i-1] = L->dados[i];
        
    }  
    L->qtde--;
    return true;
}


bool remover_fim(lista_s* L){
    if(vazia(L))
        return false;

    L->qtde--;
    return true;
}

bool buscar_seq(lista_s* L, int e){
    if(vazia(L))
        return false;
    for(int i = 0; i < tamanho(L); i++){
        if(L->dados[i] = e)
            return true;
        
    }
    return false;
}

int qtde_impares_lst(lista_s *l){
    if(vazia(l))
        return false;
    
    int impares = 0;
    for(int i=0; i < tamanho(l); i++){
        if(l->dados[i] % 2 != 0 ){
            impares++;
        }
    }
    return impares;
}