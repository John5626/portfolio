package app.screenmatch.modelos;

import app.screenmatch.excecao.ErroDeConversaoDeAno;
import app.screenmatch.excecao.ErroDuracaoNaoInformada;

public class Titulo implements Comparable<Titulo> {
    private String nome;
    private int duracaoEmMinutos;
    private int anoLancamento;

    private boolean incluidoNoPlano;
    private double somaAvaliacoes;
    private int totalDeAvaliacoes;


    public Titulo(String nome, int anoLancamento) {
        this.nome = nome;
        this.anoLancamento = anoLancamento;
    }

    public Titulo(TituloOmdb tituloOmdb, boolean incluidoNoPlano) {
        this.nome = tituloOmdb.title();
        if(tituloOmdb.year().length() > 4){
            throw new ErroDeConversaoDeAno("Não foi possível a conversão do ano, " +
                    "pois há mais de 4 caracteres");
        }
        this.anoLancamento = Integer.valueOf(tituloOmdb.year());

        if(tituloOmdb.runtime().equalsIgnoreCase("N/A")){
            this.anoLancamento = -1;
            throw new ErroDuracaoNaoInformada("Nao foi informada uma duração para o título.");

        }
        this.duracaoEmMinutos = Integer.valueOf(tituloOmdb.runtime().substring(0, 2));

        this.incluidoNoPlano = incluidoNoPlano;


    }

    public String getNome() {
        return nome;
    }

    public int getAnoLancamento() {
        return anoLancamento;
    }

    public boolean isIncluidoNoPlano() {
        return incluidoNoPlano;
    }

    public int getTotalDeAvaliacoes(){
        return totalDeAvaliacoes;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setIncluidoNoPlano(boolean incluidoNoPlano) {
        this.incluidoNoPlano = incluidoNoPlano;
    }

    public void setAnoLancamento(int anoLancamento) {
        this.anoLancamento = anoLancamento;
    }

    public void setDuracaoEmMinutos(int duracaoEmMinutos) {
        this.duracaoEmMinutos = duracaoEmMinutos;
    }

    public int getDuracaoEmMinutos() {
        return duracaoEmMinutos;
    }

    public void avaliarFilme(double nota){
        somaAvaliacoes += nota;
        totalDeAvaliacoes++;

    }

    public String exibirFichaTecnica(){
        /*
        System.out.println("Filme: " + getNome());
        System.out.println("Lançamento: " + getAnoLancamento());
        System.out.println("Duração: " + duracaoEmMinutos);
         */

        return String.format("""
                Filme: %s
                Lançamento: %d
                Duração: %d
                """, getNome(), getAnoLancamento(), getDuracaoEmMinutos());
    }

    public double retornarMedia(){
        return somaAvaliacoes / totalDeAvaliacoes;
    }

    @Override
    public int compareTo(Titulo titulo2) {
        return this.getNome().compareTo(titulo2.getNome());
    }

}
