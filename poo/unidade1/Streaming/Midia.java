package Streaming;

import java.time.LocalDate;

public abstract class Midia {
    private String titulo;
    private LocalDate dataLancamento;
    private String status = "Não iniciada";

    public Midia(String titulo, LocalDate dataLancamento) {
        this.titulo = titulo;
        this.dataLancamento = dataLancamento;
    }

    public String getTitulo() {
        return this.titulo;
    }

    public LocalDate getDataLancamento() {
        return this.dataLancamento;
    }

    public String getStatus() {
        return this.status;
    }
    
    public void iniciar() {
        this.status = "Iniciada";
    }

    public void pausar() {
        this.status = "Pausada";
    }

    public void parar() {
        this.status = "Parada";
    }
}
