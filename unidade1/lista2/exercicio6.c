#include <stdio.h>
#include <math.h>

/*
    Código que calcula o IMC de uma pessoa
*/

void calculaIMC(float kg, float metros, float *imc) {
    *imc = kg/pow(metros, 2); // Função para calcular o IMC
}

int main(){
    float peso, altura, imc; // Variáveis

    printf("Digite o seu peso em kg: "); // Salva o peso em kg
    scanf("%f", &peso);

    printf("Digite sua altura em metros: "); // Salva a aluta em metros
    scanf("%f", &altura);

    calculaIMC(peso, altura, &imc); // Chama o método para calcular o IMC e salva o valor

    printf("O seu imc é de: %.2f\n\n", imc); // Mostra o IMC para o usuário

    return 0;
}