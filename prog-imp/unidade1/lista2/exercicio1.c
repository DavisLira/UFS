// rodar no terminal quando usa o <math.h>:
// cd Lista\ 2
// gcc exercicio1.c -lm -o exercicio1
// ./exercicio1

#include <stdio.h>
#include <math.h>

/*
    Código que faz o cálculo de quantas caixas de remédio são 
    necessárias comprar de acordo com a quantidade de comprimidos 
    tomados por mês e a quantos que vem em uma caixa
*/

int DivisaoArredondada(int dividendo, int divisor) {
    // Essa divisão equivale a uma regra de três

    float divisao;

    divisao = (float)dividendo/divisor; // Calcula a divisão entre 2 números
    divisao = ceil(divisao); // Arredonda a divisão para cima

    return divisao; // Retorna a divisão
}

int main(){
    int Mensal, Unidades, Caixas; // Variáveis

    printf("Quantos comprimidos você toma por mês? "); // Quantidade mensal de comprimidos
    scanf("%i", &Mensal);

    printf("Quantos comprimidos tem em uma caixa? "); // Quantidades de comprimidos em uma caixa
    scanf("%i", &Unidades);

    Caixas = DivisaoArredondada(Mensal, Unidades); // Função que calcula a quantidade de caixas

    printf("Você precisa comprar %i caixas\n\n", Caixas); // Mostra a quantidade de caixas

    return 0;
}