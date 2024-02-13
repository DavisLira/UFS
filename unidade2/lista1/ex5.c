// fatorial

#include <stdio.h>

void calculaFatorial(int n, int *f) {
    int resultado = 1;

    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }

    *f = resultado;
}

int main()
{
    int numero, fatorial = 0;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    calculaFatorial(numero, &fatorial);

    printf("%d! = %d\n\n", numero, fatorial);
    
    return 0;
}
