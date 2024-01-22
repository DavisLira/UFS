#include <stdio.h>

void calculaImc(float peso, float altura, float *imc) {
    *imc = peso / (altura * altura);
}

int main() {
    float peso, altura, imc;

    printf("Digite o peso em quilos: ");
    scanf("%f", &peso);
    printf("Digite a altura em metros: ");
    scanf("%f", &altura);

    calculaImc(peso, altura, &imc);

    if(imc < 18.5) {
        printf("Magreza\n");
    } else if(imc >= 18.5 && imc < 25) {
        printf("Saudável\n");
    } else if(imc >= 25 && imc < 30) {
        printf("Sobrepeso\n");
    } else if(imc >=30 && imc < 35) {
        printf("Obesidade Grau I\n");
    } else if(imc >= 35 && imc < 40) {
        printf("Obesidade Grau II (Severa)\n");
    } else if(imc >= 40) {
        printf("Obesidade Grau III (morbida)\n");
    }

    return 0;
}