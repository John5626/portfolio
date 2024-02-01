package app.screenmatch.excecao;

public class ErroDuracaoNaoInformada extends NumberFormatException {
    private String msg;
    public ErroDuracaoNaoInformada(String msg) {
        this.msg = msg;
    }

    @Override
    public String getMessage() {
        return this.msg;
    }
}
