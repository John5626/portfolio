#include <stdio.h>
#include <stdlib.h>
#include "lista_dp_enc.h"

struct celula {
    int conteudo;
    struct celula* prox;
    struct celula* ant;
};

struct Lista {
    celula* prim;
    int qtde;
};

lista_dp* criar_dp() {
    lista_dp* nova_lista = (lista_dp*)calloc(1, sizeof(lista_dp));
    return nova_lista;
}

static celula* criar_cel(int valor) {
    celula* nova_cel = (celula*)malloc(sizeof(celula));
    if (nova_cel != NULL) {
        nova_cel->conteudo = valor;
        nova_cel->prox = NULL;
        nova_cel->ant = NULL;
    }
    return nova_cel;
}

void exibir_dp(lista_dp* L) {
    if (vazia_dp(L) || L == NULL)
        return;

    celula* atual = L->prim;
    while (atual != NULL) {
        printf("%d ", atual->conteudo);
        atual = atual->prox;
    }
}

int tamanho_dp(lista_dp* L) {
    if (L == NULL)
        return 0;

    return L->qtde;
}

bool vazia_dp(lista_dp* L) {
    return L->qtde == 0;
}

bool inserir_inicio_dp(lista_dp* L, int e) {
    celula* cel = criar_cel(e);

    if (cel == NULL)
        return false;

    cel->ant = NULL;
    cel->prox = L->prim;

    if (!vazia_dp(L))
        L->prim->ant = cel;

    L->prim = cel;
    L->qtde++;

    return true;
}

bool inserir_meio_dp(lista_dp* L, int e, int k) {
    if (L == NULL || k < 1 || k > tamanho_dp(L) + 1)
        return false;

    celula* cel = criar_cel(e);
    if (cel == NULL)
        return false;

    if (k == 1)
        return inserir_inicio_dp(L, e);

    celula* temp = L->prim;
    for (int i = 0; i < k - 2; i++) {
        temp = temp->prox;
    }

    cel->ant = temp;
    cel->prox = temp->prox;

    if (temp->prox != NULL)
        temp->prox->ant = cel;

    temp->prox = cel;
    L->qtde++;

    return true;
}

bool inserir_fim_dp(lista_dp* L, int e) {
    celula* cel = criar_cel(e);

    if (L == NULL || cel == NULL) {
        return false;
    }

    cel->conteudo = e;
    cel->prox = NULL;

    if (vazia_dp(L)) {
        L->prim = cel;
        cel->ant = NULL;
    } else {
        celula* atual = L->prim;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        cel->ant = atual;
        atual->prox = cel;
    }

    L->qtde++;

    return true;
}

bool remover_inicio_dp(lista_dp* L, int* valor) {
    if (vazia_dp(L))
        return false;

    celula* removida = L->prim;
    *valor = removida->conteudo;

    if (tamanho_dp(L) == 1) {
        L->prim = NULL;
    } else {
        L->prim->prox->ant = NULL;
        L->prim = L->prim->prox;
    }

    free(removida);
    L->qtde--;
    return true;
}

bool remover_meio_dp(lista_dp* L, int k, int* valor_removido) {
    if (vazia_dp(L) || k <= 0 || k > tamanho_dp(L))
        return false;

    if (k == 1) {
        return remover_inicio_dp(L, valor_removido);
    }

    celula* atual = L->prim;
    int contador = 1;

    // Percorre a lista até a posição k-1
    while (contador < k - 1) {
        atual = atual->prox;
        contador++;
    }

    celula* removida = atual->prox;

    celula* proximo = removida->prox;
    atual->prox = proximo;

    if (proximo != NULL)
        proximo->ant = atual;

    *valor_removido = removida->conteudo;
    free(removida);
    L->qtde--;

    return true;
}

bool remover_fim_dp(lista_dp* L, int* valor_removido) {
    if (vazia_dp(L))
        return false;

    if (tamanho_dp(L) == 1) {
        return remover_inicio_dp(L, valor_removido);
    }

    celula* atual = L->prim;
    while (atual->prox->prox != NULL) {
        atual = atual->prox;
    }

    celula* removida = atual->prox;
    atual->prox = NULL;

    *valor_removido = removida->conteudo;
    free(removida);
    L->qtde--;

    return true;
}


bool buscar_seq_dp(lista_dp* L, int e) {
    if (vazia_dp(L))
        return false;

    celula* atual = L->prim;
    while (atual != NULL) {
        if (atual->conteudo == e)
            return true;
        atual = atual->prox;
    }
    return false;
}

lista_dp* liberar_dp(lista_dp* L) {
    if (vazia_dp(L))
        return L;

    int r;
    while (!vazia_dp(L))
        remover_fim_dp(L, &r);

    free(L);
    return NULL;
}

void percorrer_inverso(lista_dp* L){
    if(!vazia_dp(L)){
        celula* atual = L->prim;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual = atual->ant;

        while (atual != NULL)
        {
            printf("%d, ", atual->conteudo);
            atual = atual->ant;
            
        }
      
    }
}

lista_dp* concaternar(lista_dp* l1, lista_dp* l2){
    if(vazia_dp(l1) && vazia_dp(l2))
        return NULL;

    lista_dp* l3 = criar_dp();

    celula* atual = l1->prim;
    while (atual != NULL)
    {
        inserir_fim_dp(l3, atual->conteudo);
        atual = atual->prox;
    }
    atual = l2->prim;

    while (atual != NULL)
    {
        inserir_fim_dp(l3, atual->conteudo);
        atual = atual->prox;
    }
    return l3;

}

lista_dp* alternar(lista_dp* l1, lista_dp* l2){
    if(vazia_dp(l1) && vazia_dp(l2))
        return NULL;

    lista_dp* l3 = criar_dp();

    celula* atual1= l1->prim;
    celula* atual2= l2->prim;
    while (atual1 != NULL && atual2 !=NULL)
    {
        inserir_fim_dp(l3, atual1->conteudo);
        inserir_fim_dp(l3, atual2->conteudo);
        atual1 = atual1->prox;
        atual2 = atual2->prox;
    }
    
    while (atual1 != NULL)
    {
        inserir_fim_dp(l3, atual1->conteudo);
        atual1 = atual1->prox;
    }

    while (atual2 != NULL)
    {
        inserir_fim_dp(l3, atual2->conteudo);
        atual2 = atual2->prox;
    }
    return l3;

}