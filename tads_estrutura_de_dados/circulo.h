// TAD
#ifndef CIRCULO_H
#define CIRCULO_H


//REGISTROS

/*
Coordenadas do centro do circulo
*/
typedef struct{
    float x,y;
}Ponto;

/*
Dados do circulo
*/
typedef struct{
    float raio;
    Ponto coordenadas;
}Circulo;

//PROTOTIPOS (declaração das funçoes)

/*
Cria um circulo com coordenadas entre [-20,20] e raio ]0,10]
Entrada: Variavel do tipo circulo
Saída: retorna a variavel do tipo circulo com raio e coordenadas aleatorias
*/
Circulo* criar(Circulo* a);

/*
Calcula a area do circulo
Entrada: Variavel do tipo circulo
Saída: retorna a area
*/
float* calcula_area(Circulo* a);

/*
Calcula o perimetro do circulo
Entrada: Variavel do tipo circulo
Saída: retorna o perimetro
*/
float* calcula_perimetro(Circulo* a);


/*
Calcula o perimetro do circulo
Entrada: Variavel do tipo circulo
Saída: retorna NULL
*/
Circulo* liberar(Circulo* a);

#endif CIRCULO_H
