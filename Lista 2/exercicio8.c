#include <stdio.h>

void converte(float real, float cambio, float *convertido) {
    *convertido = real/cambio;
}

int main(){
    float real, cambioDolar, cambioEuro, dolar, euro;

    printf("Digite o valor em reais: ");
    scanf("%f", &real);
    printf("Digite quantos reais são 1 dolar: ");
    scanf("%f", &cambioDolar);
    printf("Digite quantos reais são 1 euro: ");
    scanf("%f", &cambioEuro);

    converte(real, cambioDolar, &dolar);
    converte(real, cambioEuro, &euro);

    printf("R$%.2f equivale a $%.2f e a £%.2f \n\n", real, dolar, euro);

    return 0;
}