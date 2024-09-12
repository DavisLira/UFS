package Streaming;

import java.time.LocalDate;

public class Musica extends Midia{
    private String Artista;

    public Musica(String titulo, String Artista, LocalDate dataLancamento) {
        super(titulo, dataLancamento);
        this.Artista = Artista;
    }

    public String getArtista() {
        return Artista;
    }
}
