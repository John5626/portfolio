package app.screenmatch.calculos;

public class FiltroRecomendacao {
    public void filtra(Classificacao c){
        if(c.getClassificacao() >= 4)
            System.out.println("Está entre os preferidos do momento!");
        else if (c.getClassificacao() >= 2) {
            System.out.println("Muito bem avaliado no momento!");
        }
        else System.out.println("Coloue na lista para assistir depois!");

    }
}
