#include <stdio.h>

// Caso de exemplo: 123

void inverterDigitos(int numero, int *invertido) {
    int terceiro = (numero % 10);                       //   3
    int segundo = (numero % 100);                       //  23
    int primeiro = (numero / 100);                      // 1

    segundo -= terceiro;                                //  20
    terceiro *= 100;                                    // 300

    *invertido = terceiro + segundo + primeiro;         // 300 + 20 + 1 = 321
}


int main() 
{
    int numLido, numGerado;

    printf("Digite um numero positivo ate 999: ");
    scanf("%d", &numLido);

    inverterDigitos(numLido, &numGerado);

    if (numLido > 999 || numLido < 0) {
        printf("Número inválido\n");
    } else if (numLido > numGerado) {
        printf("Número lido maior que numero gerado\n");
    } else if (numLido < numGerado) {
        printf("Número lido menor que numero gerado\n");
    } else if (numLido == numGerado) {
        printf("Número lido igual ao numero gerado\n");
    }
}