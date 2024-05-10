#include <stdio.h>

/*
    Código que calcula o tempo a ser percorrido uma dada
    distância passando a velocidade esperada
*/

int main()
{
    // Declara as variáveis
    float distancia, velocidade, tempo;

    // Solicita a ditancia
    printf("Digite a distância a ser percorrida em m: ");
    scanf("%f", &distancia);

    // Solicita a velocidade esperada
    printf("Digite a velocidade média esperada em m/s: ");
    scanf("%f", &velocidade);

    // Calcula o tempo
    tempo = distancia / velocidade;

    // Mostra o tempo para percorrer a medida passada
    printf("A distância %.2fm vai ser percorrida em %.2fs\n\n", distancia, tempo);

    return 0;
}