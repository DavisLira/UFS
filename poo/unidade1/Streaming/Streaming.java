package Streaming;

import java.time.LocalDate;

public class Streaming {
    public static void main(String[] args) {
        Midia[] midias = new Midia[10];
        midias[0] = new Filme("Matrix", "Lana Wachowski", LocalDate.of(1999, 5, 21));
        midias[1] = new Filme("O Poderoso Chefão", "Francis Ford Coppola", LocalDate.of(1972, 9, 24));
        midias[2] = new Filme("A Origem", "Christopher Nolan", LocalDate.of(2010, 8, 06));
        midias[3] = new Filme("O Senhor dos Anéis: A Sociedade do Anel", "Peter Jackson", LocalDate.of(2001, 12, 19));
        midias[4] = new Filme("O Senhor dos Anéis: As Duas Torres", "Peter Jackson", LocalDate.of(2002, 12, 18));
        midias[5] = new Filme("O Senhor dos Anéis: O Retorno do Rei", "Peter Jackson", LocalDate.of(2003, 12, 20));
        midias[6] = new Musica("Bohemian Rhapsody", "Queen", LocalDate.of(1975, 10, 31));
        midias[7] = new Musica("Stairway to Heaven", "Led Zeppelin", LocalDate.of(1971, 11, 27));
        midias[8] = new Musica("Imagine", "John Lennon", LocalDate.of(1971, 10, 21));
        midias[9] = new Musica("Bohemian Rhapsody", "Queen", LocalDate.of(1975, 10, 31));

        System.out.println(midias[0]);

        Usuario usuario1 = new Usuario("João");
        usuario1.alugar(midias[0], midias);
        usuario1.alugar(midias[1], midias);
        usuario1.alugar(midias[2], midias);
        usuario1.alugar(midias[4], midias);
        usuario1.devolver(midias[0], midias);
        usuario1.devolver(midias[1], midias);
        usuario1.devolver(null, midias);
    }
}
