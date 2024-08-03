package CorretorAutomatico;

public class Prova {
    private String nomeAluno;
    private int numeroQuestoes;
    private char respostasQuestoes[];
    private int valorQuestoes[];

    public Prova(
        String nomeAluno,
        int numeroQuestoes
    ) {
        this.nomeAluno = nomeAluno;
        this.numeroQuestoes = numeroQuestoes;
        this.respostasQuestoes = new char[numeroQuestoes];
        this.valorQuestoes = new int[numeroQuestoes];
    }

    public String getNomeAluno() {
        return this.nomeAluno;
    }

    public int getNumeroQuestoes() {
        return this.numeroQuestoes;
    }

    public char[] getRespostasQuestoes() {
        return this.respostasQuestoes;
    }

    public int[] getValorQuestoes() {
        return this.valorQuestoes;
    }

    public void responder(char[] respostas) {
        this.respostasQuestoes = respostas;
    }

    public void notasProva(int[] notas) {
        int total = 0;
        for (int i = 0; i < notas.length; i++) {
            total = total + notas[i];
        }

        if (total != 10) {
            System.out.println("Erro na pontuação da prova\n");
            return;
        }

        this.valorQuestoes = notas;
    }
}
