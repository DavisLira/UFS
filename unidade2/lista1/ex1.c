// Dieta de saturno, perde 5kg/mes

#include <stdio.h>

int main() 
{
    float pesoInicial, pesoFinal, pesoAtual;

    printf("Digite o seu peso atual: ");
    scanf("%f", &pesoInicial);
    pesoAtual = pesoInicial;

    printf("Digite o peso Almejado: ");
    scanf("%f", &pesoFinal);

    if (pesoInicial > pesoFinal)
    {
        for (int mes = 1; pesoAtual > pesoFinal; mes++)
        {
            pesoAtual -= 5;

            if (pesoAtual < pesoFinal) {
                printf("Mes %d: %.3f \n", mes, pesoFinal);
            } else {
                printf("Mes %d: %.3f \n", mes, pesoAtual);
            }
        }
        

    } else if (pesoInicial == pesoFinal) {
        printf("Voce ja esta com o peso desejado! \n");
    } else if (pesoInicial < pesoFinal) {
        printf("Essa dieta nao e a certa para voce! \n");
    }
    
    return 0;
}