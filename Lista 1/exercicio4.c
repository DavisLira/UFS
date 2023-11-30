#include <stdio.h>

int main()
{
    // Declaração das variáveis
    float real, dolar, cambio;

    // Solicita o valor em reais para o usuário
    printf("Digite a quantidade de Reais para a conversão: ");
    scanf("%f", &real);

    // Solicita o valor do câmbio
    printf("Digite quanto 1 Dólar vale em Reais: ");
    scanf("%f", &cambio);

    // Calcula a quantidade de Dólares de acordo com a quantidade de Reais e o câmbio
    dolar = real / cambio;

    // Mostra a conversão
    printf("R$%.2f equivalem a $%.2f\n\n", real, dolar);

    return 0;
}