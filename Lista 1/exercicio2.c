#include <stdio.h>

/*
    Código que calcula quanto tempo a pessoa perde o peso de acordo com
    os pesos atual, ideal e a perda mensal
*/

int main()
{
    // Declaração das variáveis
    float pesoAtual, pesoIdeal, perdaMensal, meses, diferencaPeso;

    // Solicita o peso atual
    printf("Digite o peso atual em kg: ");
    scanf("%f", &pesoAtual);

    // Solicita peso ideal
    printf("Digite o peso ideal em kg: ");
    scanf("%f", &pesoIdeal);

    // Solicita a perda mensal
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