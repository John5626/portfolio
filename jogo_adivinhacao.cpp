#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

void cabecalho();
int select_nivel();
void chute_info(int tentativas, int* chute);
void game_over(int tentativas, int pontos, bool acertou);

int main(){
    srand(time(NULL));
    
    
    cabecalho();

    int n_tentativas = select_nivel();

    const int N_SECRETO = rand() % 100;
    

    int tentativas = 0;
    float pontos = 1000.0;
    
    int chute;
    bool acertou;


    while(tentativas != n_tentativas){
        tentativas++;
    
        chute_info(tentativas, &chute);
        
        double pts_perdidos = abs((chute - N_SECRETO)) / float(2);
        pontos -= pts_perdidos;

        acertou = chute == N_SECRETO;
        bool maior = chute > N_SECRETO;

        if(acertou){
            break;
        }
        else
            if(maior)
                cout << "Seu chute foi maior que o numero secreto" << endl;

            else
                cout << "Seu chute foi menor que o numero secreto" << endl;

    }

    game_over(tentativas, pontos, acertou);
    
}

void cabecalho(){
    cout << "*************************************" << endl;
    cout << "* Bem-vindo ao Jogo da Adivinhacao! *" << endl;  
    cout << "*************************************" << endl;  
}

int select_nivel(){
    cout << "Escolha a dificuldade" << endl;
    cout << "(F) Facil, (M) Medio, (D) Dificil" << endl;

    char nivel;
    cout << "Nivel: ";
    cin >> nivel;

    int n_tentativas;
    
    switch (nivel)
    {
        case 'F':
            n_tentativas = 15;
    
            break;

        case 'M':
            n_tentativas = 10;
    
            break;
        
        case 'D':
            n_tentativas = 5;
    
            break;
    
        default:
            cout << "Dificuldade incorreta" << endl;
            exit(1);
            
    }
    return n_tentativas;
}

void chute_info(int tentativas, int* chute){
    cout << endl;
        cout << "Tentativa " << tentativas << ": " << endl;
        cout << "Seu chute: ";
        cin >> *chute;
        //cout << "Valor do chute: " << chute << endl;

}

void game_over(int tentativas, int pontos, bool acertou){
    if(acertou){
        cout << endl << "FIM DE JOGO!"<< endl;
        cout << "Parabens! Voce acertou em " << tentativas << " tentativas :)" << endl;
        
        cout.precision(2); 
        cout << fixed;
        cout << "Sua pontuacao foi de " << pontos << " pontos.";
    }
    else cout << "Voce perdeu, OTARIO! Tente novamente, TROXA! :(" << endl;
}