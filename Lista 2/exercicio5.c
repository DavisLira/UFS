#include <stdio.h>
#include <math.h>

float quadrado(float x) {
    return x * x;
}

void calculaArea(float r, float *A){
    *A = M_PI * quadrado(r);
}

int main() {
    float raio, area;

    printf("Digite o raio do círculo: ");
    scanf("%f", &raio);

    calculaArea(raio, &area);

    printf("A área do círculo é: %.2f\n\n", area);
}