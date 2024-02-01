//IMPLEMENTAÇÃO TAD TIPO LISTA SEQUENCIAL DE PONTOS
//JOAO VICTOR ECOMP
#include <stdio.h>
#include <stdlib.h>

#include "listaseq_P2D.h"

//REGISTROS
struct pontos
{
    float x, y;
};

struct lista
{
    pontos2D* dados;
    int qtde, cap;
};

//IMPLEMENTAÇÃO PROTÓTIPOS

lista_P2D* criar(int cap){
    lista_P2D* nova_lista = (lista_P2D*) malloc(sizeof(lista_P2D));
    if(nova_lista != NULL)
    {
        nova_lista->dados = (pontos2D*) malloc(cap * sizeof(pontos2D));
        if(nova_lista->dados == NULL){
            free(nova_lista);
            return NULL;
        }

        nova_lista->cap = cap;
        nova_lista->qtde = 0;
        
    }
    return nova_lista;
    
}

void exibir(lista_P2D* L){
    for(int i = 0; i < tamanho(L); i++)
        printf("(%.2f, %.2f)   ", L->dados[i].x, L->dados[i].y);

}

int capacidade(lista_P2D* L){

    return L->cap;
}

int tamanho(lista_P2D* L){
    return L->qtde;

}

bool cheia(lista_P2D* L){
    if(L->cap == L->qtde)
        return true;
    return false;

}

bool vazia(lista_P2D* L){
    if(L->qtde == 0) 
        return true;

    return false;
}

bool inserir_inicio(lista_P2D* L, float x, float y){
    if(cheia(L))
        return false;
    
   for(int i = L->qtde; i > 0; i--){
        L->dados[i].x = L->dados[i-1].x;
        L->dados[i].y = L->dados[i-1].y;
   }
        
        
    L->dados[0].x = x;
    L->dados[0].y = y;
    L->qtde++;
    
    return true;
}

bool inserir_meio(lista_P2D* L, float x, float y, int k){
    if(cheia(L) || k <= 0 || k > tamanho(L)+1)
        return false;
    for(int i = L->qtde; i >= k; i--) {
        L->dados[i].x = L->dados[i-1].x;
        L->dados[i].y = L->dados[i-1].y;
        
    }
    L->dados[k-1].x = x;
    L->dados[k-1].y = y;
    L->qtde++;
    return true;
}

bool inserir_fim(lista_P2D* L, float x, float y){
    if(cheia(L))
        return false;
    
    L->dados[L->qtde].x = x;
    L->dados[L->qtde].y = y;
    L->qtde++;
    return true;
}

bool remover_inicio(lista_P2D* L, float* x_rem, float* y_rem){
    if(vazia(L))
        return false;

    *x_rem = L->dados[0].x;
    *y_rem = L->dados[0].y;


    for(int i = 0; i < tamanho(L)-1; i++){
        L->dados[i].x = L->dados[i+1].x;
        L->dados[i].y = L->dados[i+1].y;
        
    }
    L->qtde--;
    return true;   
    
}

bool remover_meio(lista_P2D* L, int k){
    if(vazia(L) || k < 1 || k > tamanho(L))
        return false;

    for(int i = k; i < tamanho(L); i++){
        L->dados[i-1].x = L->dados[i].x;
        L->dados[i-1].y = L->dados[i].y;
    }  
    L->qtde--;
    return true;
}


bool remover_fim(lista_P2D* L){
    if(vazia(L))
        return false;

    L->qtde--;
    return true;
}

bool buscar_seq(lista_P2D* L, float x, float y){
    if(vazia(L))
        return false;
    for(int i = 0; i < tamanho(L); i++){
        if(L->dados[i].x == x && L->dados[i].y == y)
            return true;
        
    }
    return false;
}



