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

int main() {
    int port, mat, aprovados = 0;
    float red;
    char opcao;

    do
    {
        printf("Questões de portugues: ");
        scanf("%d", &port);
        printf("Questões de matematica: ");
        scanf("%d", &mat);
        printf("Nota na redacao: ");
        scanf("%f", &red);

        if(port >= 40 && mat >= 21 && red >= 7){
            aprovados++;
        }

        printf("\nDeseja sair? S – Sim ou N - Não.\n");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

        opcao = continuar(opcao);

    } while (opcao == 'N');
    
    printf("Aprovados: %d\n", aprovados);
}