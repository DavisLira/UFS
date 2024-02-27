#include <stdio.h>
#include <string.h>
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

int vogais(char p[]) {
    int quantidade = 0;

    for (int i = 0; i < strlen(p); i++) {
        p[i] = tolower(p[i]);
    }

    for (int i = 0; i < strlen(p); i++) {
        if ('a' == p[i] || 'e' == p[i] || 'i' == p[i] || 'o' == p[i] || 'u' == p[i]) {
            quantidade++;
        }
    }
    return quantidade;
}

int main()
{
    char opcao;
    char palavra[21];

    do {
    printf("Digite uma palavra de no maximo 20 caracteres: \n");
    scanf(" %20[^\n]",palavra);

    printf("Quantidade de vogais: %d\n\n", vogais(palavra));

    printf("Deseja sair? S – Sim ou N - Não.\n");
    scanf(" %c", &opcao);
    opcao = toupper(opcao);
    opcao = continuar(opcao);
    printf("\n\n");

    } while (opcao == 'N');
    
    return 0;
}