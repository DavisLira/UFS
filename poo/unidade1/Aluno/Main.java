package Aluno;

import java.time.LocalDate;

public class Main {
    public static void main(String[] args) {
        Pessoa[] alunos = new Pessoa[3];

        alunos[0] = new Aluno("João", LocalDate.of(2000, 12, 27));
        alunos[0].setNotas(8.6f, 7.0f, 9.0f);
        
        alunos[1] = new Aluno("José", LocalDate.of(1999, 6, 21));
        alunos[1].setNotas(6f, 6f, 9.0f);
        
        alunos[2] = new Aluno("Maria", LocalDate.of(2002, 3, 1));
        alunos[2].setNotas(8.6f, 9.0f, 10.0f);

        for (Pessoa pessoa : alunos) {
            System.out.println(pessoa.toString());
        }
    }
}
