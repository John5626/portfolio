package app.screenmatch.modelos;

import app.screenmatch.api.Gson;

import java.util.Scanner;

public class ConveteTitulo {
    private TituloOmdb tituloOmdb;
    private boolean ativa;
    private Titulo titulo;

    public void inicializa(String json){
        Gson gson = new Gson();
        gson.inicializa();

        this.tituloOmdb = gson.getGson().fromJson(json, TituloOmdb.class);
    }

    public Titulo converte(){
        if (this.tituloOmdb.response().equals("True")) {
            System.out.println("O título '" + tituloOmdb.title() + "' está ativo no plano? S/N");
            Scanner scan = new Scanner(System.in);
            if(scan.nextLine().equalsIgnoreCase("S"))
                this.ativa = true;
            else this.ativa = false;

            //Inicializa Titulo como Filme ou Serie
            if (tituloOmdb.type().equals("movie"))
                this.titulo = new Filme(tituloOmdb, ativa);

            if (tituloOmdb.type().equals("series"))
                this.titulo = new Serie(tituloOmdb, ativa);

            System.out.println("Conversão realizada com sucesso!");

            return titulo;

        } else System.out.println("Filme não encontrado!");

        return null;
    }



}
