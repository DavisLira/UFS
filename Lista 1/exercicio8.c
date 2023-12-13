#include <stdio.h>

/*
    Código que calcula a área de um retângulo a partir
    das medidas passadas pelo usuário
*/

int main()
{
    // Declara as variáveis
    float comprimento, largura, area;
    
    // Solicita o tamanho do comprimento
    printf ("Qual é o comprimento do retângulo em m? ");
    scanf("%f", &comprimento);
    
    // Solicita a largura 
    printf ("Qual é a largura do retângulo m? ");
    scanf("%f", &largura);
    
    // Calcula a área do retângulo
    area = comprimento * largura;
    
    // Mostra a área
    printf("Esse retângulo tem %.2f m² de área\n", area);
    
    return 0;
}