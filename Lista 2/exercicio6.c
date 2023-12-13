#include <stdio.h>
#include <math.h>

void calculaIMC(float kg, float metros, float *imc) {
    *imc = kg/pow(metros, 2);
}

int main(){
    float peso, altura, imc;

    printf("Digite o seu peso em kg: ");
    scanf("%f", &peso);

    printf("Digite sua altura em metros: ");
    scanf("%f", &altura);

    calculaIMC(peso, altura, &imc);

    printf("O seu imc é de: %.2f\n\n", imc);

    return 0;
}