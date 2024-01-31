//IMPLEMENTAÇÃO TAD TIPO LISTA ENCADEADA
//JOAO VICTOR ECOMP

#include <stdio.h>
#include <stdlib.h>
#include "listaenc_int.h"

struct celula{
    int conteudo;
    struct celula* prox;

};

struct Lista{
    celula* prim;
    int qtde;
};

lista_le* criar_le(){
    lista_le* nova_lista = (lista_le*) calloc(1, sizeof(lista_le));
    
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

void exibir_le(lista_le* L){
    if(vazia_le(L) || L == NULL)
        return;
    
    celula* atual = L->prim;
    while(atual != NULL)
    {
        printf("%d ", atual->conteudo);
        atual = atual->prox;
    }   

}

int tamanho_le(lista_le* L){
    if(L == NULL)
        return 0;

    return L->qtde;

}


bool vazia_le(lista_le* L){
    if(L == NULL) 
        return true;

    return L->qtde == 0;
}

bool inserir_inicio_le(lista_le* L, int e){
    if(L == NULL)
        return false;

    celula* cel = criar_cel(e);

    if (cel == NULL) {
        return false;
    }

    if (vazia_le(L)) {
        cel->prox = NULL;
    } else {
        cel->prox = L->prim;
    }

    L->prim = cel;
    L->qtde++;

    return true;
}

bool inserir_meio_le(lista_le* L, int e, int k){
    if(L == NULL || k < 1 || k > tamanho_le(L) + 1)
        return false;
    
    celula* cel = criar_cel(e);
    if(cel == NULL)
        return false;

    if(k == 1)
        return inserir_inicio_le(L, e);
    
    
    celula* temp = L->prim;
    for(int i=0; i < k-2; i++){
        temp = temp->prox;
    }
    
    cel->prox = temp->prox;
    temp->prox = cel;
    L->qtde++;

    return true;
}

bool inserir_fim_le(lista_le* L, int e){
    celula* cel = criar_cel(e);

    if (L == NULL || cel == NULL) {
        return false;
    }

    cel->conteudo = e;
    cel->prox = NULL;

    if (vazia_le(L)) {
        L->prim = cel;
    } else {
        celula* atual = L->prim;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = cel;
    }

    L->qtde++;

    return true;
}

bool remover_inicio_le(lista_le* L, int* valor){
    if(vazia_le(L))
        return false;

    celula *removida = L->prim;
    *valor = removida->conteudo;
    if(tamanho_le(L) == 1){
        L->prim = NULL;
        L->qtde--;
        return true;
    }
    L->prim = L->prim->prox;
    free(removida);
    L->qtde--;
    return true; 
    
}

bool remover_meio_le(lista_le* L, int k, int* valor_removido){
    if(vazia_le(L) || k < 1 || k > tamanho_le(L))
        return false;

    if(tamanho_le(L) == 1){
        return remover_inicio_le(L, valor_removido);
    }

    celula* temp = L->prim;
    for(int i = 0; i < k-2; i++){
        temp = temp->prox;
    }
    celula* removida = temp->prox;
    temp->prox = temp->prox->prox;
    *valor_removido = removida->conteudo;
    free(removida);
    L->qtde--;

    return true;
}


bool remover_fim_le(lista_le* L, int* valor_removido){
    if(vazia_le(L))
        return false;

    if(tamanho_le(L) == 1){
        return remover_inicio_le(L, valor_removido);
    }
    celula* atual = L->prim;
    do{
        atual = atual->prox;
    }while(atual->prox->prox != NULL);

    *valor_removido = atual->prox->conteudo;
    celula *removida = atual->prox;
    atual->prox = NULL;

    free(removida);
    L->qtde--;
    return true;
}

bool buscar_seq_le(lista_le* L, int e){
    if(vazia_le(L))
        return false;

    celula* atual = L->prim;
    while(atual != NULL){
        if(atual->conteudo == e)
            return true;
        atual = atual->prox;
    }
    return false;
}

lista_le* liberar_le(lista_le* L){
    if(vazia_le(L))
        return L;
    
    int r;
    while(!vazia_le(L))
        remover_fim_le(L, &r);

    free(L);
    return NULL;
}