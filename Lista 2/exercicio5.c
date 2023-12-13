#include <stdio.h>
#include <math.h>

/*
    Código para calcular a área de um círculo
*/

#define PI 3.14159265358979323846 // Definição do valor de PI 

float quadrado(float x) {
    return x * x; // Cálculo do quadrado de um número
}

void calculaArea(float r, float *A){
    *A = PI * quadrado(r); // Função para calcular a área de um círculo
}

int main() {
    float raio, area; // Variáveis

    printf("Digite o raio do círculo: "); // Salva o raio do círculo
    scanf("%f", &raio);

    calculaArea(raio, &area); // Chama a função para calcular a área e ja salva o valor

    printf("A área do círculo é: %.2f\n\n", area); // Mostra o valor da área
}