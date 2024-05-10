#include <stdio.h>

/*
    Código que calcula quanto tempo em dias a pessoa perde o 
    peso de acordo com os pesos atual, ideal e a perda mensal
*/

int main()
{
    // Declaração das variáveis
    float pesoAtual, pesoIdeal, perdaMensal, dias, diferencaPeso;

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
    dias = diferencaPeso / perdaMensal * 30;

    // Mostra ao usuário em quantos dias irá perder o peso
    printf("Você vai demorar %.1f dias para perder %.2fkg\n\n", dias, diferencaPeso);

    return 0;
}