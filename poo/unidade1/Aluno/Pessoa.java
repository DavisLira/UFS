package Aluno;

import java.time.LocalDate;

public abstract class Pessoa {
    private String nome;
    private LocalDate dataNascimento;

    // Construtor padrão
    public Pessoa() {
        this.nome = "Desconhecido";
        this.dataNascimento = LocalDate.now();
    }

    // Construtor parametrizado
    public Pessoa(String nome, LocalDate dataNascimento) {
        this.nome = nome;
        this.dataNascimento = dataNascimento;
    }

    // Getters e Setters
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public LocalDate getDataNascimento() {
        return dataNascimento;
    }

    public void setDataNascimento(LocalDate dataNascimento) {
        this.dataNascimento = dataNascimento;
    }

    public abstract void setNotas(float nota1, float nota2, float nota3);
    public abstract float calcularMedia();
}
