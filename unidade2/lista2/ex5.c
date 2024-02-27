#include <stdio.h>
#include <string.h>
#include <ctype.h>

int verificaCod(char matricula[]) {

    char cod[3] = "99";

    for (int i = 4; i < 6; i++) {
        int j = 0;
        if (matricula[i] == cod[j++])
        {
            return 1;
        }
    }
    
    return 0;
}

void verifica(char matricula[], char ano[], int *quantidade) {

    int anoCerto = 0;

    for (int i = 0; i < 4; i++) {
        if (matricula[i] == ano[i]) {
            anoCerto++;

            if (anoCerto == 4) {
                *quantidade += verificaCod(matricula);
            }
        }
    }
    
}

int main()
{
    char matricula[11], ano[5];
    int quantidade;

    printf("Digite o ano de busca dos alunos de gerontologia (COD: 99): ");
    scanf(" %4[^\n]", ano);
    
    for (int i = 1; i <= 100; i++) {
        printf("Digite a matricula: ");
        scanf(" %10[^\n]", matricula);

        verifica(matricula, ano, &quantidade);
    }

    printf("%d alunos foram matriculados em gerontologia no ano %s\n\n", quantidade, ano);
    
    return 0;
}