#include <stdio.h>

int main()
{
    // Declaração das variáveis
    float pesoAtual, pesoIdeal, perdaMensal, meses, diferencaPeso;

    //Solicita ao usuário o peso atual em kg
    printf("Digite o peso atual em kg: ");
    scanf("%f", &pesoAtual);

    // Solicita ao usuário o peso ideal em kg
    printf("Digite o peso ideal em kg: ");
    scanf("%f", &pesoIdeal);

    // Solicita ao usuário a perda mensal
    printf("Digite a perda mensal em kg: ");
    scanf("%f", &perdaMensal);

    // Calcula a diferença dos pesos
    diferencaPeso = pesoAtual - pesoIdeal;

    // Calcula quantos meses demora para perder o peso
    meses = diferencaPeso / perdaMensal;

    // Mostra ao usuário em quantos meses irá perder o peso
    printf("Você vai demorar %.1f meses para perder %.2fkg\n\n", meses, diferencaPeso);

    return 0;
}