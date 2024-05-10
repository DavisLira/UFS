// Escrever programa em C para ler nome, 3 notas e
// frequência (em percetual) dos 80 alunos do projeto
// AprendaProgramação, calcular a média destes (média da
// turma) e emitir em tela a situação final de cada aluno.

// São aprovados todos os que ficam com média (aritmética
// simples) acima da média da turma e têm frequência acima
// de 65%.

// Deve ser exibido o nome de cada aluno, seguido das
// notas, média e da situação final: APROVADO ou
// REPROVADO.

#include <stdio.h>
#include <ctype.h>


struct tpAluno {    // tp = tipo
    char nome[21];
    float nota1;
    float nota2;
    float nota3;
    int frequencia;
};

// Forma de diminuir a declaração da variável
typedef struct tpAluno tpSt;
// tpSt vetor[80]; // ou
// struct tpAluno vetor[80];

const int ALUNOS = 80;


void recebeDados(tpSt *aluno) {
    for (int i = 0; i < ALUNOS; i++)
    {
        printf("Digite o nome do %d° aluno: ", i + 1);
        scanf(" %20[^\n]s", aluno[i].nome);
        for (int j = 0; j < 20; j++) {
            aluno[i].nome[j] = toupper(aluno[i].nome[j]);
        }
        printf("Digite a 1° nota do %d aluno: ", i + 1);
        scanf("%f", &aluno[i].nota1);
        printf("Digite a 2° nota do %d aluno: ", i + 1);
        scanf("%f", &aluno[i].nota2);
        printf("Digite a 3° nota do %d aluno: ", i + 1);
        scanf("%f", &aluno[i].nota3);
        printf("Digite a frequencia do %d aluno: ", i + 1);
        scanf("%d", &aluno[i].frequencia);
        printf("\n");
    }
    
}

void mediaTotal(tpSt *aluno, float *mediaTurma) {
    float media;

    for (int i = 0; i < ALUNOS; i++) {
        media += (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;
    }

    *mediaTurma =  media / ALUNOS;
}

void mostraResultado(tpSt *aluno, float mediaTurma) {
    for (int i = 0; i < ALUNOS; i++) {
        float media;

        printf("nome: %s\n", aluno[i].nome);
        printf("nota 1: %.2f\n", aluno[i].nota1);
        printf("nome 2: %.2f\n", aluno[i].nota2);
        printf("nome 3: %.2f\n", aluno[i].nota3);

        media = (aluno[i].nota1 + aluno[i].nota2 + aluno[i].nota3) / 3;

        printf("Média do aluno %s: %.2f\n", aluno[i].nome, media);
        printf("Frequencia: %d%%\n", aluno[i].frequencia);

        if (media >= mediaTurma && aluno[i].frequencia >= 65) {
            printf("APROVADO!!\n\n");
        } else {
            printf("REPROVADO!!\n\n");
        }
    }
}

int main()
{
    // rg = registro
    tpSt rgAlunos[ALUNOS];
    float mediaTurma;

    recebeDados(rgAlunos);
    mediaTotal(rgAlunos, &mediaTurma);

    printf("Media da turma: %.2f\n\n", mediaTurma);

    mostraResultado(rgAlunos, mediaTurma);

    return 0;
}