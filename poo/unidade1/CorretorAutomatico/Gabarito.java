package CorretorAutomatico;

public class Gabarito {
    private int numeroQuestoes;
    private char respostasQuestoes[];

    public Gabarito(
        int numeroQuestoes
    ) {
        this.numeroQuestoes = numeroQuestoes;
        this.respostasQuestoes = new char[numeroQuestoes];
    }

    public int getNumeroQuestoes() {
        return this.numeroQuestoes;
    }

    public char[] getRespostasQuestoes() {
        return this.respostasQuestoes;
    }

    public void respostas(char[] respostas) {
        this.respostasQuestoes = respostas;
    }
}
