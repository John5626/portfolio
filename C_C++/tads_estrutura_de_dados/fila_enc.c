//IMPLEMENTAÇÃO TAD TIPO FILA ENCADEADA
//JOAO VICTOR ECOMP

#include <stdio.h>
#include <stdlib.h>
#include "fila_enc.h"

struct celula{
    int conteudo;
    struct celula* prox;

};

struct fila{
    celula* prim;
    int qtde;
};

fila_enc* criar_enc(){
    fila_enc* nova_lista = (fila_enc*) calloc(1, sizeof(fila_enc));
    if(nova_lista == NULL){
        free(nova_lista);
        return NULL;
    }
    
    return nova_lista;
    
}

static celula* criar_cel(int valor){
    celula* nova_cel = (celula*) malloc(sizeof(celula));
    if(nova_cel != NULL)
    {
        nova_cel->conteudo = valor;
        nova_cel->prox = NULL;
    }
    return nova_cel;
    
}

int frente_enc(fila_enc* F){
    if(vazia_enc(F) || F == NULL){
        printf("FILA VAZIA\n");
    }
    
    return F->prim->conteudo;

}

int tamanho_enc(fila_enc* F){
    if(F == NULL)
        return 0;

    return F->qtde;

}


bool vazia_enc(fila_enc* F){
    if(F == NULL) 
        return true;

    return F->qtde == 0;
}


bool inserir_enc(fila_enc* F, int e){
    celula* cel = criar_cel(e);

    if (F == NULL || cel == NULL) {
        return false;
    }

    cel->conteudo = e;
    cel->prox = NULL;

    if (vazia_enc(F)) {
        F->prim = cel;
    } else {
        celula* atual = F->prim;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = cel;
    }

    F->qtde++;

    return true;
}

bool remover_enc(fila_enc* F, int* valor){
    if(vazia_enc(F))
        return false;

    celula *removida = F->prim;
    *valor = removida->conteudo;
    if(tamanho_enc(F) == 1){
        F->prim = NULL;
        F->qtde--;
        return true;
    }
    F->prim = F->prim->prox;
    free(removida);
    F->qtde--;
    return true; 
    
}

fila_enc* liberar_enc(fila_enc* F){
    if(vazia_enc(F))
        return F;
    
    int r;
    while(!vazia_enc(F))
        remover_enc(F, &r);

    free(F);
    return NULL;
}