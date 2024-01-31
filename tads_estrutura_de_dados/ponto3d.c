//JOAO VICTOR ECOMP

#include "ponto3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exibir(Ponto *a){
    printf("\n(%.2f, %.2f, %.2f)\n", a->x, a->y, a->z);

}   

void mover(Ponto* a, float dx, float dy, float dz){
    a->x = dx + a->x;
    a->y = dy + a->y;
    a->z = dz + a->z;

}

Ponto* liberar(Ponto* a){
    free(a);

    return NULL;
}



