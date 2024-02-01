package app.screenmatch.excecao;

public class ErroDeConversaoDeAno extends RuntimeException {
    private String msg;
    public ErroDeConversaoDeAno(String msg) {
        this.msg = msg;
    }

    @Override
    public String getMessage() {
        return this.msg;
    }
}
