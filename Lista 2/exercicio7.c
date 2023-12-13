#include <stdio.h>

/*
    Código que calcula o total que uma pessoa guardou em determinado tempo,
    sendo passado o valor inicial, mensal e os meses
*/

void calculaRendimento(float inicial, float mensal, int meses, float *total, float *guardado) {
    *guardado = mensal * meses; // Cálculo de quando foi guardado
    *total = inicial + *guardado; // Montante acumulado
}

int main() {
    float valorInicial, valorMensal, montante, guardado; // Variáveis
    int meses;

    printf("Digite o valor inicial a ser investido: "); // Salva o valor inicial
    scanf("%f", &valorInicial);

    printf("Digite o valor investido mensalmente: "); // Salva o valor mensal
    scanf("%f", &valorMensal);

    printf("Digite quantos meses irá durar o investimento: "); // Quantidade de meses investindo
    scanf("%i", &meses);

    // Chama a função para calcular o montante e o investido
    calculaRendimento(valorInicial, valorMensal, meses, &montante, &guardado);

    // Mostra o montante e o total investido por mês
    printf("Você tem um total de R$%.2f e rendeu R$%.2f \n\n", montante, guardado);

    return 0;
}