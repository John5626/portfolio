//IMPLEMETAÇÃO TAD ARVORE BINARIA DE BUSCA             JOAO VICTOR SOUZA - ECOMP
#include <stdio.h>
#include <stdlib.h>

#include "abb_int.h"
#include "fila_abb.h"

struct no{
    int info;
    no_arv* sae; //sub-arvore a esquerda
    no_arv* sad; //sub-arvore a direita
};

no_arv* criar_abb(int valor){
    no_arv* nova = (no_arv*) malloc(sizeof(no_arv));
    if(nova != NULL){
        nova->info = valor;
        nova->sae = nova->sad = NULL;
    }
    return nova;
}

no_arv* inserir_abb(no_arv* no, int valor){
    if(no == NULL)
        return criar_abb(valor);

    if(valor <= no->info)
        no->sae = inserir_abb(no->sae, valor);

    else no->sad = inserir_abb(no->sad, valor);

    return no;
}

void percorrer_abb(no_arv* no){
    if(no == NULL)
        return;
    
    percorrer_abb(no->sae);
    printf("%d ", no->info);
    percorrer_abb(no->sad);
}

no_arv* minimo_abb(no_arv* no){
    if(no == NULL)
        return NULL;

    else if(no->sae != NULL)
        return minimo_abb(no->sae);

    return no;
}

bool buscar_abb(no_arv* no, int valor){
    if(no == NULL)
        return false;

    if(valor == no->info)
        return true;

    else if(valor <= no->info)
        return buscar_abb(no->sae, valor);
    
    else return buscar_abb(no->sad, valor);
}

void busca_largura_abb(no_arv* no){
    fila_enc* f = criar_enc();
    inserir_enc(f, no);

    no_arv *rem;
    while(!vazia_enc(f)){
        no_arv* atual = frente_enc(f);
        printf("%d ", atual->info);
        remover_enc(f, rem);

        if(atual->sae)
            inserir_enc(f, atual->sae);
        if(atual->sad)
            inserir_enc(f, atual->sad);
    }
}

no_arv* remover_abb(no_arv* no, int valor){
    if(no == NULL)
        return NULL;

    if(valor < no->info)
        no->sae = remover_abb(no->sae, valor);

    else if(valor > no->info)
        no->sad = remover_abb(no->sad, valor);
    
    else{
        no_arv* temp = NULL;

        if(no->sae == NULL && no->sad == NULL){
            free(no);
            return NULL;
        }
        else if(no->sae == NULL){
            temp = no->sad;
            free(no);
            return temp;
        }
        else if(no->sad == NULL){
            temp = no->sae;
            free(no);
            return temp;
        }
        else{
            no_arv* temp = minimo_abb(no->sad);
            no->info = temp->info;
            no->sad = remover_abb(no->sad, temp->info); 
        }
    }

    return no;
}

void liberar_abb(no_arv* no){
    if(no == NULL){
        return;
    }

    no_arv* temp = no;
    liberar_abb(no->sae);
    liberar_abb(no->sad);
    free(temp);
}



