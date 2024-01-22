#include <stdio.h>

void calculaViagens(int alunos, int *resultado, int *resto){
    *resultado = alunos / 11;
    *resto = alunos % 11;
}

int main()
{
    int alunos, resultado, resto;
    
    printf("Digite a quantidade de alunos: ");
    scanf("%d", &alunos);
    
    calculaViagens(alunos, &resultado, &resto);
    
    if(alunos <= 11){
        printf("1 Viagem de kombi e 0 passagens de coletivo");
    } else {
        printf("%d viagens de kombi e %d passagens de coletivo", resultado, resto);
    }
    
    return 0;
}
