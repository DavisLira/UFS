// Crie um struct que guarde nome, idade e peso um atletas. Em um
// vetor, alocado dinamicamente, guarde os dados de N atletas. Exiba uma
// listagem dos dados dos atletas cadastrados. Ao final exiba a média dos
// pesos e quantos atletas são menores de idade.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct RegAtleta{
	char nome[20];
    int idade;
    float peso;
};

typedef struct RegAtleta atl;

void mostraAtleta(atl atleta) {
    printf("\n*******************************\n");
    printf("%s com %d anos e pesando %.2fKg\n", atleta.nome, atleta.idade, atleta.peso);
}

void main () {
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
