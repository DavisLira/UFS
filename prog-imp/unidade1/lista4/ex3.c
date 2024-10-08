#include <stdio.h>
#include <ctype.h>

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

void calculaMedia(int numNotas, float notas[], float *media) {
    float soma = 0;

    for (int i = 0; i < numNotas; i++) {
        soma += notas[i];
    }

    *media =  soma / numNotas;
}

int main() {
    char opcao;
    float notas[4], media;

    do {
        printf("Digite a 1° nota: ");
        scanf("%f", &notas[0]);
        printf("Digite a 2° nota: ");
        scanf("%f", &notas[1]);
        printf("Digite a 3° nota: ");
        scanf("%f", &notas[2]);
        
        calculaMedia(3, notas, &media);

        if (media >= 7){
            printf("Aluno aprovado com media: %.2f\n", media);
        } else if (media >= 3 && media < 7) {
            printf("O aluno tem a possibilidade de fazer a 4° avaliação\n");
            printf("Digite a 4° nota: ");
            scanf("%f", &notas[3]);

            calculaMedia(4, notas, &media);
            
            if (media >=5) {
                printf("O aluno foi aprovado com média: %.2f\n", media);
            } else {
                printf("Aluno reprovado!\n");
            }
        } else {
            printf("Aluno reprovado!\n");
        } 

        printf("Quer verificar a situação de outro aluno? S – Sim ou N - Não.\n");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        opcao = continuar(opcao);

    } while (opcao == 'S');
    
}