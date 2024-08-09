// Construa um programa que armazene nome, matrícula e média de
// até N alunos e dê ao usuário a possibilidade de ver a listagem dos
// alunos em ordem alfabética ou em ordem de classificação. Obs: uma
// vez que os dados sejam digitados, o usuário deve poder ver as listagens
// quantas vezes ele desejar.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct RegTurma{
	char nome[20];
    char matricula[4];
    float media;
};

typedef struct RegTurma turma;

char continuar(char resp) {
    resp = toupper(resp);
    if (resp == 'S' || resp == 'N') {
        return resp;
    } else {
        printf("Digite uma resposta valida [S / N]: ");
        scanf(" %c", &resp);
        continuar(resp);
    }
    return toupper(resp);
}

int ordemAlfabetica(const void *a, const void *b) {
    const turma *aluno1 = (const turma *)a;
    const turma *aluno2 = (const turma *)b;
    return strcmp(aluno1->nome, aluno2->nome);
}

int ordemDaMedia(const void *a, const void *b) {
    const turma *aluno1 = (const turma *)a;
    const turma *aluno2 = (const turma *)b;
    
    if (aluno1->media < aluno2->media) return 1;
    else if (aluno1->media > aluno2->media) return -1;
    else return 0;
}


void main () 
{
    char cont;
    int qtd, opc;
    turma *alunos;

    printf("Digite a quantidade de alunos: ");
    scanf("%d", &qtd);

    alunos = (turma*) malloc(qtd*sizeof(turma));

    if(!alunos) {
        printf("Memória nao alocada. \nEncerrando programa...\n");
        return;
    }

    for (int i = 0; i < qtd; i++)
    {
        char nome[20];
        printf("Digite o nome do %d° aluno: ", i+1);
        scanf(" %20[^\n]s", nome);
        for (int j = 0; j < 20; j++)
        {
            nome[j] = tolower(nome[j]);
        }
        nome[0] = toupper(nome[0]);
        strcpy(alunos[i].nome, nome);
        printf("Digite a matricula do %d° aluno: ", i+1);
        scanf(" %4[^\n]s", alunos[i].matricula);
        printf("Digite a média do %d° aluno: ", i+1);
        scanf("%f", &alunos[i].media);
        printf("\n");
    }

    do
    {
        printf("****************************\n");
        printf("Escolha a forma de listagem:\n");
        printf("  1 - Ordem Alfabética\n");
        printf("  2 - Ordem da Média\n");
        printf("Opcao: ");
        scanf("%d", &opc);
        printf("****************************\n");
        
        switch (opc)
        {
        case 1:
            qsort(alunos, qtd, sizeof(turma), ordemAlfabetica);
            break;
        case 2:
           qsort(alunos, qtd, sizeof(turma), ordemDaMedia);
            break;
        default:
            break;
        }

        for (int i = 0; i < qtd; i++) {
            printf("*** Nome: %s \n", alunos[i].nome);
            printf("*** Matricula: %s \n", alunos[i].matricula);
            printf("*** Média: %.2f \n", alunos[i].media);
            printf("****************************\n");
        }

        printf("Quer fazer outra listagem? S – Sim ou N - Não.\n");
        scanf(" %c", &cont);
        cont = toupper(cont);
        cont = continuar(cont);
    } while (cont == 'S');
    

    free(alunos);
}
