#include <stdio.h>

int main()
{
  // Declara as variáveis
  float distancia, velocidade, tempo;
  
  // Solicita a ditancia em metros
  printf("Digite a distância a ser percorrida em m: ");
  scanf("%f", &distancia);
  
  // Solicita a velocidade esperada em m/s
  printf("Digite a velocidade média esperada em m/s: ");
  scanf("%f", &velocidade);
  
  // Calcula o tempo esperado
  tempo = distancia / velocidade;
  
  // Mostra o tempo para percorrer a medida passada
  printf("A distância %.2fm vai ser percorrida em %.2fs\n\n", distancia, tempo);
  
  return 0;
}