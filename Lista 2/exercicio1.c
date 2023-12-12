#include <stdio.h>
#include <math.h>

int DivisaoArredondada(int dividendo, int divisor) {
    float divisao;
    divisao = (float)dividendo/divisor;
    divisao = ceil(divisao);
    return divisao;
}

int main(){
    int Mensal, Unidades, Caixas;
    printf("Quantos comprimidos você toma por mês? ");
    scanf("%i", &Mensal);
    printf("Quantos comprimidos tem em uma caixa? ");
    scanf("%i", &Unidades);
    Caixas = DivisaoArredondada(Mensal, Unidades);
    printf("Você precisa comprar %i caixas\n\n", Caixas);
    return 0;
}