package app.screenmatch.principal;

import app.screenmatch.modelos.Titulo;

import java.util.Scanner;


public class Utils {
    public static void cabecalho(){
        System.out.println("\t*******************************\t");
        System.out.println("   \t    Bem-Vindo ao ScreenMatch\t ");
        System.out.println("\t*******************************\t");
    }

    public static void imprimeEstrelas(int c){
        for(int i = 0; i < c; i++){
            System.out.print("★ ");
        }
    }

    public static void erroDeAdicao(){
        System.out.println("O titulo não será adicionado");
    }

    public static void avaliar(Titulo titulo){
        Scanner scan = new Scanner(System.in);
        System.out.println("Digite '-1' para encerrar a avaliação:");
        Boolean sair = false;
        double nota = 0;
        while (!sair) {
            nota = Double.valueOf(scan.nextLine());
            if ((int) nota == -1)
                break;
            else titulo.avaliarFilme(nota);
        }
    }


}
