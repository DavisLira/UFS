#include <stdio.h>
#include <ctype.h>

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

        printf("\nDeseja sair? S - SIM | N - NAO\n");
        scanf(" %c", &opcao);

        opcao = toupper(opcao);

    } while (opcao == 'N');
    
    printf("Aprovados: %d\n", aprovados);
}