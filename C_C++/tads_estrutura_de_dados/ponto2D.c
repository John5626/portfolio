//JOAO VICTOR - ECOMP                               // Arquivo ponto2D.c
#include <stdio.h>                                              
#include <stdlib.h>
#include <math.h>

#include "ponto2D.h"

//REGISTROS

struct ponto
{
    float x, y;
};

//IMPLEMENTAÇÃO DOS PROTÓTIPOS

ponto2D* criar_p(float x, float y) {
    ponto2D* novo = (ponto2D*) calloc(1, sizeof(ponto2D));
    if(novo != NULL) {
        novo->x = x;
        novo->y = y;
    }
    return novo;
}

void exibir_p(ponto2D *p) {
    printf("<%.2f, %.2f>", p->x, p->y);
}

void liberar_p(ponto2D* p){
    free(p);
}

float calc_dist(ponto2D* p1, ponto2D* p2){
    float d;

    d = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));

    return d;
}

int quadrante_p(ponto2D* p){
    if(p->x == 0 && p->y == 0)
        return 0;

    if(p->x > 0 && p->y > 0)
        return 1;
    
    if(p->x < 0 && p->y > 0)
        return 2;

    if(p->x < 0 && p->y < 0)
        return 3;

    if(p->x > 0 && p->y < 0)
        return 4;

    if(p->y == 0)
        return 5;

     if(p->x == 0)
        return 6;

}

ponto2D* simX_p(ponto2D* p){
    ponto2D* p_sim = criar_p(-1.0 * p->x, p->y);
    
    return p_sim; 
    
}

ponto2D* simY_p(ponto2D* p){
    ponto2D* p_sim = criar_p(p->x, -1.0 * p->y);
    return p_sim; 
    
}