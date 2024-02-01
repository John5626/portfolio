//IMPLEMENTAÇÃO TAD TIPO fila SEQUENCIAL
//JOAO VICTOR ECOMP

#include <stdio.h>
#include <stdlib.h>
#include "fs_int.h"


struct fila_int{
    int *dados;
    int qtde, cap;
};

fila_s* criar_fs(int cap){
    fila_s* nova_fs = (fila_s*) malloc(sizeof(fila_s));
    if(nova_fs != NULL)
    {
        nova_fs->dados = (int*) malloc(cap * sizeof(int));
        if(nova_fs->dados == NULL){
            free(nova_fs);
            return NULL;
        }

        nova_fs->cap = cap;
        nova_fs->qtde = 0;
        
    }
    return nova_fs;
    
}

int frente_fs(fila_s* F){
    if(vazia_fs(F))
        printf("fila vazia");
    
    return F->dados[0];
    
}

int capacidade_fs(fila_s* F){

    return F->cap;
}

int tamanho_fs(fila_s* F){
    return F->qtde;

}

bool cheia_fs(fila_s* F){
    if(F->cap == F->qtde)
        return true;
    return false;

}

bool vazia_fs(fila_s* F){
    if(F->qtde == 0) 
        return true;

    return false;
}

bool inserir_fs(fila_s* F, int e){
    if(cheia_fs(F))
        return false;
    
    F->dados[F->qtde] = e;
    F->qtde++;
    return true;
}

bool remover_fs(fila_s* F, int* removido){
    if(vazia_fs(F))
        return false;

    *removido = F->dados[0];

    for(int i = 0; i < tamanho_fs(F)-1; i++){
        F->dados[i] = F->dados[i+1];
        
    }
    F->qtde--;
    return true;   
    
}

fila_s* liberar_fs(fila_s* F){
    free(F);
    return NULL;
}