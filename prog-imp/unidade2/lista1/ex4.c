// notas de 50 alunos
#include <stdio.h>

void verificaNota(float nota, int *acertos, int *situacao) {
    if (nota >= 7) {
        (*acertos)++;
    }

    if (*acertos >= 5)
    {
        *situacao = 1;
    } else if (*acertos < 5) {
        *situacao = 0;
    }
    
}

int main()
{

    for (int aluno = 1; aluno <= 50; aluno++) {
        printf("\nNota do %d° aluno: \n",aluno);

        float nota;
        int acertos = 0, situacao = 0;

        for (int avaliacao = 1; avaliacao <= 12; avaliacao++) {

            printf("%d° avaliacao: ",avaliacao);
            scanf("%f", &nota);

            verificaNota(nota, &acertos, &situacao);
            
        }

        if (situacao == 1) {
            printf("Aprovado! Nota suficiente em %d avaliacoes\n\n", acertos);
        } else if (situacao == 0) {
            printf("Reprovado! Nota suficiente em %d avaliacoes\n\n", acertos);
        }
    }

    return 0;
}