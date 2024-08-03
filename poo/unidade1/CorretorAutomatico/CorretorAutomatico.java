package CorretorAutomatico;

public class CorretorAutomatico {


    public void corrigirProva(Prova prova, Gabarito gabarito) {
        if (prova.getNumeroQuestoes() != gabarito.getNumeroQuestoes()) {
            System.out.println("Gabarito inválido para essa prova!\n");
            return;
        }

        int nota = 0;
        int[] valorQuestoes = prova.getValorQuestoes();
        int numeroQuestoes = prova.getNumeroQuestoes();
        for (int i = 0; i < numeroQuestoes; i++) {
            if (prova.getRespostasQuestoes()[i] == gabarito.getRespostasQuestoes()[i]) {
                nota = nota + valorQuestoes[i];
            }
        }

        System.out.println("Aluno: " + prova.getNomeAluno());
        System.out.println("Nota: " + nota);
    }
}
