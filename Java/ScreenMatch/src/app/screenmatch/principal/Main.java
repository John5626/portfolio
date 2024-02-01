package app.screenmatch.principal;

import app.screenmatch.api.Gson;
import app.screenmatch.api.Http;
import app.screenmatch.excecao.ErroDeConversaoDeAno;
import app.screenmatch.excecao.ErroDuracaoNaoInformada;
import app.screenmatch.modelos.*;


import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        Scanner scan = new Scanner(System.in);

        Utils utils = new Utils();

        utils.cabecalho();

        String busca;
        List<Titulo> titulos = new ArrayList<>();

        Gson gson = new Gson();
        gson.inicializa();

        while (true) {
            try {
                Http http = new Http();
                http.client();

                System.out.print("Informe o título para pesquisa: "); busca = scan.nextLine();

                if(busca.equalsIgnoreCase("sair"))
                    break;

                http.request(busca);

                String json = http.response();

                //System.out.println(json);

                ConveteTitulo conveteTitulo = new ConveteTitulo();
                conveteTitulo.inicializa(json);
                Titulo titulo = conveteTitulo.converte();


                //Adiciona o Titulo à lista
                if(titulo != null) {
                    titulos.add(titulo);
                    utils.avaliar(titulo);
                    System.out.println(titulo.getNome() + " adicionado à lista!");

                }
                System.out.println(titulo);
                System.out.println();

            }catch (ErroDeConversaoDeAno e) {
                utils.erroDeAdicao();
                System.out.println(e.getMessage());
            }catch (ErroDuracaoNaoInformada e){
                utils.erroDeAdicao();
                System.out.println(e.getMessage());
            }


        }

        if(titulos.size() != 0){
            FileWriter wrt = new FileWriter("filmes.json");
            wrt.write(gson.getGson().toJson(titulos));
            wrt.close();
        }
        else System.out.println("Nao foi criado o arquivo Json, pois a lista de títulos estava vazia.");


        System.out.println("O programa finalizou corretamente");

        scan.close();





    }
}
