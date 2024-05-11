#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

    // Função para continuar
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

    // Struct dos atletas
struct RegAtleta{
	char nome[20];
    int idade;
    float peso;
};
typedef struct RegAtleta atl;

    // Struct dos Alunos
struct RegTurma{
	char nome[20];
    char matricula[4];
    float media;
};
typedef struct RegTurma turma;

    // Listagem dos atletas
void mostraAtleta(atl atleta) {
    printf("\n*******************************\n");
    printf("%s com %d anos e pesando %.2fKg\n", atleta.nome, atleta.idade, atleta.peso);
}

    // Ordena alunos em ordem alfabética
int ordemAlfabetica(const void *a, const void *b) {
    const turma *aluno1 = (const turma *)a;
    const turma *aluno2 = (const turma *)b;
    return strcmp(aluno1->nome, aluno2->nome);
}

    // Ordena alunos pela ordem da média (decrescente)
int ordemDaMedia(const void *a, const void *b) {
    const turma *aluno1 = (const turma *)a;
    const turma *aluno2 = (const turma *)b;
    
    if (aluno1->media < aluno2->media) return 1;
    else if (aluno1->media > aluno2->media) return -1;
    else return 0;
}


// Guarde N números em um vetor alocado dinamicamente. Exiba a
// média dos números lidos e os múltiplos de 6 digitados.
void quest1 () {
    int *numeros, *mult6, quantos, qtddiv = 0, total = 0;

    printf("Digite a quantidade de itens: ");
    scanf("%d", &quantos);

    numeros = (int*) malloc(quantos*sizeof(int));
    mult6 = (int*) malloc(qtddiv*sizeof(int));

    if(!numeros) {
        printf("Memória nao alocada. \nEncerrando programa...\n");
        return;
    }

    for (int i = 0; i < quantos; i++)
    {
        printf("Digite o %d° valor: ", i+1);
        scanf("%d", &numeros[i]);
        total += numeros[i];
        if (numeros[i] % 6 == 0) 
        {
            mult6 = (int*) realloc(mult6, (qtddiv + 1) * sizeof(int));
            mult6[qtddiv] = numeros[i];
            qtddiv++;
        }
    }
    
    printf("\n*****************************\n");
    printf("  Média dos números lidos: %.2f\n", (float)total/quantos);
    printf("  Números multiplos de 6:");
    
    for (int i = 0; i < qtddiv; i++)
    {
        printf(" %d", mult6[i]);
    }
    if (qtddiv == 0) printf(" 0");

    printf("\n\n");

    free(numeros);
    free(mult6);
}

// Crie um struct que guarde nome, idade e peso um atletas. Em um
// vetor, alocado dinamicamente, guarde os dados de N atletas. Exiba uma
// listagem dos dados dos atletas cadastrados. Ao final exiba a média dos
// pesos e quantos atletas são menores de idade.
void quest2 () {
    int qtd, qtdMenor18 = 0;
    float pesoTotal = 0;
    atl *atletas;

    printf("Digite a quantidade de atletas: ");
    scanf("%d", &qtd);

    atletas = (atl*) malloc(qtd*sizeof(atl));

    if(!atletas) {
        printf("Memória nao alocada. \nEncerrando programa...\n");
        return;
    }

    for (int i = 0; i < qtd; i++)
    {
        char nome[20];
        printf("Digite o nome do %d° atleta: ", i+1);
        scanf(" %20[^\n]s", nome);
        for (int j = 0; j < 20; j++)
        {
            nome[j] = tolower(nome[j]);
        }
        nome[0] = toupper(nome[0]);
        strcpy(atletas[i].nome, nome);
        printf("Digite a idade do %d° atleta: ", i+1);
        scanf(" %d", &atletas[i].idade);
        printf("Digite o peso do %d° atleta: ", i+1);
        scanf(" %f", &atletas[i].peso);
        printf("\n");
        pesoTotal += atletas[i].peso;

        if (atletas[i].idade < 18)
        {
            qtdMenor18++;
        }
        
    }

    for (int i = 0; i < qtd; i++)
    {
        mostraAtleta(atletas[i]);
    }
    printf("\n*******************************\n");

    printf("\nMédia do peso dos atletas: %.2fKg\n", pesoTotal / qtd);
    printf("Temos %d atletas menores de idade\n", qtdMenor18);
    

    free(atletas);
}

// Construa um programa que armazene nome, matrícula e média de
// até N alunos e dê ao usuário a possibilidade de ver a listagem dos
// alunos em ordem alfabética ou em ordem de classificação. Obs: uma
// vez que os dados sejam digitados, o usuário deve poder ver as listagens
// quantas vezes ele desejar.
void quest3 () 
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


void main ()
{
    char continuarPrincial;
    do
    {
        int questao;
        printf("\n-------------------------------------------");
        printf("\nLista 1 da 1° unidade de Estrutura de Dados\n");
        printf("-------------------------------------------\n\n");
        printf("Questão 1: Lista de números\n");
        printf("Questão 2: Lista dos atleas\n");
        printf("Questão 3: Lista dos alunos\n");
        printf("*** Opção: ");
        scanf("%d", &questao);
        printf("\n");

        switch (questao)
        {
        case 1:
            printf("Iniciando a 1° questão\n\n\n");
            quest1();
            printf("\n\nFim da a 1° questão\n\n\n");
            break;
        
        case 2:
            printf("Iniciando a 2° questão\n\n\n");
            quest2();
            printf("\n\nFim da a 2° questão\n\n\n");
            break;
        
        case 3:
            printf("Iniciando a 3° questão\n\n\n");
            quest3();
            printf("\n\nFim da a 3° questão\n\n\n");
            break;
        
        default:
            break;
        }

        printf("Quer ver outra questão? S – Sim ou N - Não.\n");
        scanf(" %c", &continuarPrincial);
        continuarPrincial = toupper(continuarPrincial);
        continuarPrincial = continuar(continuarPrincial);
    } while (continuarPrincial == 'S');
}