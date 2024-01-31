//JOAO VICTOR - ECOMP                                   // Arquivo ponto2D.h
#ifndef PONTO2D_H // include guard                                      
#define PONTO2D_H

//Encapsulamento dos dados

typedef struct ponto ponto2D;

//Protótipos

/*
Cria um ponto e retorna uma referência para ele
Entrada: coordenadas do ponto
Saída: referência para um ponto
*/
ponto2D* criar_p(float x, float y);

/*
Exibe um ponto no formato de par ordenado => <x, y>
Entrada: uma referência para um ponto
Saída: Não tem
*/
void exibir_p(ponto2D* p);

/*
Libera a memoria alocada do ponto criado
Entrada: uma referência para um ponto
Saída: Não tem
*/
void liberar_p(ponto2D* p);

/*
Calcula a distância entre dois pontos
Entrada: dois parâmetros representando os pontos
Saída: retorna a distância calculada
*/
float calc_dist(ponto2D* p1, ponto2D* p2);

/*
Quandrante em que se encontra o ponto
Entrada: um parâmetro representando o ponto
Saída: 0 -> na origem do sistema cartesiano, 
       1 -> 1º quadrante, 
       2 -> 2º quadrante, 
       3 -> 3º quadrante, 
       4 -> 4º quadrante, 
       5 -> sobre o eixo X e 
       6 -> sobre o eixo Y
*/
int quadrante_p(ponto2D* p);

/*
Cria um ponto simétrico em relação ao eixo das abscissas
Entrada: uma referência para um ponto
Saída: um novo ponto simétrico em relação ao eixo das abscissas (eixo X)
*/
ponto2D* simX_p(ponto2D* p);

/*
Cria um ponto simétrico em relação ao eixo das ordenadas
Entrada: uma referência para um ponto
Saída: um novo ponto simétrico em relação ao eixo das ordenadas (eixo Y)
*/
ponto2D* simY_p(ponto2D* p);


#endif // PONTO2D_H