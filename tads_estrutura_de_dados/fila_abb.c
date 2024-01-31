//IMPLEMENTAÇÃO TAD TIPO FILA ENCADEADA
//JOAO VICTOR ECOMP

#include <stdio.h>
#include <stdlib.h>
#include "fila_abb.h"

struct celula{
    no_arv* conteudo;
    struct celula* prox;

};

struct fila{
    celula* prim;
    int qtde;
};

fila_enc* criar_enc(){
    fila_enc* nova_lista = (fila_enc*) calloc(1, sizeof(fila_enc));
        
    return nova_lista;
}

static celula* criar_cel(int valor){
    celula* nova_cel = (celula*) malloc(sizeof(celula));
    if(nova_cel != NULL)
    {
        nova_cel->conteudo = criar_abb(valor);
        nova_cel->prox = NULL;
    }
    return nova_cel;
    
}

no_arv* frente_enc(fila_enc* F){
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


bool inserir_enc(fila_enc* F, no_arv* no){
    celula *cel = (celula*) calloc(1, sizeof(celula));

    if (F == NULL || cel == NULL) {
        return false;
    }

    cel->conteudo = no;
    cel->prox = NULL;

    if(vazia_enc(F)){
        F->prim = cel;
    } 
    else{
        celula* atual = F->prim;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = cel;
    }

    F->qtde++;

    return true;
}

bool remover_enc(fila_enc* F, no_arv* no){
    if(vazia_enc(F))
        return false;

    celula *removida = F->prim;
    F->prim = F->prim->prox;
    free(removida);
    F->qtde--;
    return true; 
    
}

fila_enc* liberar_enc(fila_enc* F){
    if(vazia_enc(F))
        return F;
    
    
    no_arv* n = (no_arv*) malloc(sizeof(no_arv*));
    while(!vazia_enc(F))
        remover_enc(F, n);

    free(F);
    return NULL;
}