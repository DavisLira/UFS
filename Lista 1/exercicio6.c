#include <stdio.h>

int main()
{
  // Declara as variáveis
  int num, tabuada, i;
  
  // Solicita o número da tabuada
  printf ("Qual é tabuada você deseja ver? ");
  scanf("%d", &num);
  
  // Mostra a tabuada de 1 a 10
  for (i = 1; i < 11; i++)
  {
    tabuada = i * num;
    printf("%d * %d = %d\n", i, num, tabuada);
  }
  
  return 0;
}