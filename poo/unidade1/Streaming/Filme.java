package Streaming;

import java.time.LocalDate;

public class Filme extends Midia {
    private String diretor;

    public Filme(String titulo, String diretor, LocalDate dataLancamento) {
        super(titulo, dataLancamento);
        this.diretor = diretor;
    }

    public String getDiretor() {
        return this.diretor;
    }
}
