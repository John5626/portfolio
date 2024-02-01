package app.screenmatch.modelos;

import app.screenmatch.calculos.Classificacao;

public class Filme extends Titulo implements Classificacao {
    private String diretor;

    public Filme(TituloOmdb tituloOmdb, boolean incluidoNoPlano) {
        super(tituloOmdb, incluidoNoPlano);
        this.diretor = tituloOmdb.director();

    }

    public Filme(String nome, int anoLancamento) {
        super(nome, anoLancamento);
    }


    public String getDiretor() {
        return diretor;
    }

    public void setDiretor(String diretor) {
        this.diretor = diretor;
    }


    @Override
    public int getClassificacao() {
        return (int) getTotalDeAvaliacoes() / 2;
    }



    @Override
    public String toString() {
        return String.format("""
                Filme: %s
                Lançamento: %d
                Duração: %d
                """, getNome(), getAnoLancamento(), getDuracaoEmMinutos());
    }
}
