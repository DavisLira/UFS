// Guarde N números em um vetor alocado dinamicamente. Exiba a
// média dos números lidos e os múltiplos de 6 digitados.

#include <stdio.h>
#include <stdlib.h>

void main () {
    int *numeros, *mult6, quantos, qtddiv = 0, total = 0;

    printf("Digite a quantidade de itens: ");
    scanf("%d", &quantos);

    numeros = (int*) malloc(quantos*sizeof(int));
    mult6 = (int*) malloc(qtddiv*sizeof(int));

    if(!numeros) {
        printf("Memória nao alocada. \nEncerrando programa...\n");
        return;
    }

    for (int i = 0; i < quantos; i++)
    {
        printf("Digite o %d° valor: ", i+1);
        scanf("%d", &numeros[i]);
        total += numeros[i];
        if (numeros[i] % 6 == 0) 
        {
            mult6 = (int*) realloc(mult6, (qtddiv + 1) * sizeof(int));
            mult6[qtddiv] = numeros[i];
            qtddiv++;
        }
    }
    
    printf("\n*****************************\n");
    printf("  Média dos números lidos: %.2f\n", (float)total/quantos);
    printf("  Números multiplos de 6:");
    
    for (int i = 0; i < qtddiv; i++)
    {
        printf(" %d", mult6[i]);
    }
    if (qtddiv == 0) printf(" 0");

    printf("\n\n");

    free(numeros);
    free(mult6);
}
