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

void separa(char nomeCompleto[], char nome[], char sobrenome[]) {
    int posicao;

    for (int i = 0; i < strlen(nomeCompleto); i++) {

        if (' ' == nomeCompleto[i]) {
            posicao = i;
            break;
        }
    }

    for (int i = 0; i < posicao; i++){
        nome[i] = nomeCompleto[i];
    }
    nome[posicao] = '\0';
    
    int j = 0;
    for (int i = posicao + 1; i < strlen(nomeCompleto); i++) {
        sobrenome[j++] = nomeCompleto[i];
    }
    sobrenome[j] = '\0';
}


int main()
{
    char opcao;
    char nomeCompleto[51];
    char nome[51];
    char sobrenome[51];

    do {

        printf("Digite nome e sobrenome: ");
        scanf(" %50[^\n]s", nomeCompleto);

        separa(nomeCompleto, nome, sobrenome);

        for (int i = 0; i < strlen(sobrenome); i++) {
            sobrenome[i] = toupper(sobrenome[i]);
        }

        for (int i = 0; i < strlen(nome); i++)
        {
            nome[i] = tolower(nome[i]);
        }
        nome[0] = toupper(nome[0]);

        printf("%s, %s\n", sobrenome, nome);

        printf("Deseja sair? S – Sim ou N - Não.\n");
        scanf(" %c", &opcao);
        opcao = toupper(opcao);
        opcao = continuar(opcao);
        printf("\n\n");

    } while (opcao == 'N');
    
    return 0;
}