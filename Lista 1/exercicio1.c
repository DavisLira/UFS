#include <stdio.h>

int main()
{
    // Declarando as variáveis
    int num, antecessor, sucessor;

    // Solicita um número ao usuário
    printf("Digite um número: ");
    scanf("%d", &num);

    // Calcula o antecessor e o sucessor
    antecessor = num-1;
    sucessor = num+1;

    // Mostra o antecessor e o sucessor ao usuário
    printf("O antecessor é: %d\n", antecessor);
    printf("O sucessor é: %d\n\n", sucessor);

    return 0;
}