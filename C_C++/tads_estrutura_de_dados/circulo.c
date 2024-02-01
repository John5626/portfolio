#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "circulo.h"



Circulo* criar(Circulo* a){
    Circulo* novo = (Circulo*)malloc(sizeof(Circulo));

    if(novo != NULL){
        novo->coordenadas.x = rand() % 41 - 20;
        novo->coordenadas.y = rand() % 41 - 20;

        novo->raio = rand() % 11 + 1;
    }

    return novo;
}

float* calcula_area(Circulo* a){
    float* area = (float*)malloc(sizeof(float));

    if(area != NULL && a->raio > 0){
        *area = (3.14 * pow(a->raio, 2));
    }
    else area = NULL;

    return area;
}

float* calcula_perimetro(Circulo* a){
    float* perimetro = (float*)malloc(sizeof(float));

    if(perimetro != NULL && a->raio > 0){
        *perimetro = 2.0 * 3.14 * a->raio;
    }
    else perimetro = NULL;

    return perimetro;
}           

Circulo* liberar(Circulo* a){
    free(a);

    return NULL;
}





