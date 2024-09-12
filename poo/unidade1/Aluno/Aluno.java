package Aluno;

import java.time.LocalDate;

public class Aluno extends Pessoa{
    float[] notas = new float[3];

    public Aluno(String nome, LocalDate dataNascimento) {
        super(nome, dataNascimento);
    }

    public void setNotas(float nota1, float nota2, float nota3) {
        notas[0] = nota1;
        notas[1] = nota2;
        notas[2] = nota3;
    }

    public float calcularMedia() {
        float soma = 0;
        for (float nota : notas) {
            soma += nota;
        }
        return soma / notas.length;
    }

    @Override
    public String toString() {
        return "Nome: " + getNome() + "\n" +
        "Data de Nascimento: " + getDataNascimento() + "\n" +
        "Média: " + calcularMedia() + "\n";
    }
}
