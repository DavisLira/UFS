#include <stdio.h>

int main() {
    int num, linha = 1;

    printf("Digite um numero de 1 e 40: ");
    scanf("%d", &num);

    if (num < 1 || num > 40) {
        printf("Número inválido!\n\n");
        return 0;
    }

    while (linha <= num)
    {
        int coluna = 1;
        while(coluna <= linha) {
            printf("%d ", coluna);
            coluna++;
        }
        printf("\n");
        linha++;
    }

    return 0;
    
}