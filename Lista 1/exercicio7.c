#include <stdio.h>

int main()
{
  // Declara as variáveis
  float celsius, fahrenheit;
  
  // Solicita a temperatura em Celsius
  printf ("Qual é a temperatura em celsius? ");
  scanf("%f", &celsius);
  
  // Calcula a temperatura em fahrenheit
  fahrenheit = 1.8 * celsius + 32;
  // Temos a formula de conversão: C/5 = (F-32)/9
  // Entao (9C/5) + 32 = F
  // F = 1.8 * C + 32
  
  // Mostra a conversão da temperatura
  printf("Essa temperatura equivale a %.2f °F\n", fahrenheit);
  
  return 0;
}