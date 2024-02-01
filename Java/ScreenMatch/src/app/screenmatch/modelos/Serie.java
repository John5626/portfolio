package app.screenmatch.modelos;

public class Serie extends Titulo {
    private int temporadas;
    private boolean ativa;
    private int episodiosPorTemporada;
    private int minutosPorEpisosodio;

    public Serie(String nome, int anoLancamento) {
        super(nome, anoLancamento);
    }

    public Serie(TituloOmdb tituloOmdb, boolean incluidoNoPlano) {
        super(tituloOmdb, incluidoNoPlano);

        try {
            temporadas = Integer.valueOf(tituloOmdb.totalseasons());
        }catch (NumberFormatException e){
            e.getMessage();
            temporadas = -1;
        }
        String ano = tituloOmdb.year();
        if(Integer.valueOf(ano.substring(ano.length() - 4)) > 2023)
            this.ativa = true;
        else this.ativa = false;

        this.episodiosPorTemporada = 22;
        this.minutosPorEpisosodio = Integer.valueOf(tituloOmdb.runtime().substring(0, 2));
    }

    public int getTemporadas() {
        return temporadas;
    }

    public void setTemporadas(int temporadas) {
        this.temporadas = temporadas;
    }

    public boolean isAtiva() {
        return ativa;
    }

    public void setAtiva(boolean ativa) {
        this.ativa = ativa;
    }

    public int getEpisodiosPorTemporada() {
        return episodiosPorTemporada;
    }

    public void setEpisodiosPorTemporada(int episodiosPorTemporada) {
        this.episodiosPorTemporada = episodiosPorTemporada;
    }

    public int getMinutosPorEpisosodio() {
        return minutosPorEpisosodio;
    }

    public void setMinutosPorEpisosodio(int minutosPorEpisosodio) {
        this.minutosPorEpisosodio = minutosPorEpisosodio;
    }

    @Override
    public String toString() {
        return String.format("""
              Série: %s
              Lançamento: %d
              Temporadas: %d
              Episódios por temporada: %d
              Minutos por episódio: %d
              Em produção: %s
              Duração total: %d
                """, getNome(), getAnoLancamento(), getTemporadas(), getEpisodiosPorTemporada(),
                getMinutosPorEpisosodio(), ativa ? "sim" : "não", getDuracaoEmMinutos());
    }


}
