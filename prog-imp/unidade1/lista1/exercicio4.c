#include <stdio.h>

/*
    Código que converte real para dólar
*/

int main()
{
    // Declaração das variáveis
    float real, dolar, cambio;

    // Solicita o valor em reais
    printf("Digite a quantidade de Reais para a conversão: ");
    scanf("%f", &real);

    // Solicita o valor do câmbio
    printf("Digite quanto 1 Dólar vale em Reais: ");
    scanf("%f", &cambio);

    // Calculo da conversão
    dolar = real / cambio;

    // Mostra a conversão
    printf("R$%.2f equivalem a $%.2f\n\n", real, dolar);

    return 0;
}