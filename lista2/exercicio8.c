#include <stdio.h>

/*
    Código que passado um valor em Reais, mostra quanto
    equivale em Dolar e em Euro
*/

void converte(float real, float cambio, float *convertido) {
    *convertido = real/cambio; // Função para converter Real em outras Moedas
}

int main(){
    float real, cambioDolar, cambioEuro, dolar, euro; // Variáveis

    printf("Digite o valor em reais: "); // Valor em reais
    scanf("%f", &real);

    printf("Digite quantos reais são 1 dolar: "); // 1 dolar em reais
    scanf("%f", &cambioDolar);

    printf("Digite quantos reais são 1 euro: "); // 1 euro em reais
    scanf("%f", &cambioEuro);

    converte(real, cambioDolar, &dolar); // Chama a função, calcula e salva o valor em dolar
    converte(real, cambioEuro, &euro); // Chama a função, calcula e salva o valor em euro

    printf("R$%.2f equivale a $%.2f e a £%.2f \n\n", real, dolar, euro); // Mostra as conversões

    return 0;
}