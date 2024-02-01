package app.screenmatch.calculos;

import app.screenmatch.modelos.Titulo;

public class CalculadoraDeTempo {
    private int tempoTotal = 0;

    public int getTempoTotal() {
        return this.tempoTotal;
    }
/*
    public void inclui(Filme f){
        this.tempoTotal += f.getDuracaoEmMinutos();
    }

 */

    public void inclui(Titulo title){
        //System.out.println("Adicionando duração em minutos: " + title);
        this.tempoTotal += title.getDuracaoEmMinutos();
    }

}
