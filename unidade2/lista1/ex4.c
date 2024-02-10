// notas de 50 alunos

void verificaNota(float nota, int *acertos, int *situacao) {
    if (nota >= 7) {
        *acertos++;
    }

    if (*acertos >= 5)
    {
        *situacao = 1;
    } else if (*acertos < 5) {
        *situacao = 0;
    }
    
}

#include <stdio.h>
int main()
{

    for (int aluno = 1; aluno <= 3; aluno++) {
        printf("\nNota do %d° aluno: \n",aluno);

        float nota;
        int acertos = 0, situacao = -1;

        for (int avaliacao = 1; avaliacao <= 12; avaliacao++) {

            printf("%d° avaliacao: ",avaliacao);
            scanf("%f", &nota);

            verificaNota(nota, &acertos, &situacao);
        
            if (situacao == 1) {
                printf("Aluno aprovado com %d notas maiores ou iguais a 7\n\n", acertos);
            } else if (situacao == 0) {
                printf("O aluno so conseguiu nota suficiente em %d avaliacoes\n\n", acertos);
            }
            
        }
    }

    return 0;
}