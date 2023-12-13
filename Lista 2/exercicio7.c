#include <stdio.h>

void calculaRendimento(float inicial, float mensal, int meses, float *total, float *guardado) {
    *guardado = mensal * meses;
    *total = inicial + *guardado;
}

int main() {
    float valorInicial, valorMensal, montante, guardado;
    int meses;

    printf("Digite o valor inicial a ser investido: ");
    scanf("%f", &valorInicial);

    printf("Digite o valor investido mensalmente: ");
    scanf("%f", &valorMensal);

    printf("Digite quantos meses irá durar o investimento: ");
    scanf("%i", &meses);

    calculaRendimento(valorInicial, valorMensal, meses, &montante, &guardado);

    printf("Você tem um total de R$%.2f e rendeu R$%.2f \n\n", montante, guardado);

    return 0;
}