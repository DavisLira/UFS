#include <stdio.h>

void calcula(int gatos, int *resultado, int *resto){
    *resultado = gatos / 4;
    *resto = gatos % 4;
}

int main()
{
    int gatos, resultado, resto;
    
    printf("Digite a quantidade de gatos: ");
    scanf("%d", &gatos);
    
    calcula(gatos, &resultado, &resto);
    
    if(gatos <= 4){
        printf("A castracao sera responsabilidade de todos os veterinarios em conjunto \n");
    } else {
        printf("%d gatos para cada veterinario experiente e %d gatos para o recem formado \n", resultado, resto);
    }
    
    return 0;
}
