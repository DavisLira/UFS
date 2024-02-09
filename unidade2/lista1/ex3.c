// ônibus ufs atalaira - qual melhor horário?

#include <stdio.h>

// void atualizaViagem(int qtd, int *qtdMaior, int *qtdMenor, int *qtdTotal,
//                         int *hora, int *horaMaior, int *horaMenor) 
// {
//     *qtdTotal += qtd;
//     *hora = *hora;
    
//     if (qtd < *qtdMenor) {
//         *horaMenor = *hora;
//         *qtdMenor = qtd;
//     } else if (qtd > *qtdMaior) {
//         *horaMaior = *hora;
//         *qtdMaior = qtd;
//     }
    
// }

void verificaViagem(int *qtd) {

    do {
        if (*qtd > 45 || *qtd < 0)
        {
            printf("Digite um numero valido!\n\n");
            scanf("%d", qtd);
        }
    } while (*qtd > 45 || *qtd <0);
    
}

int main()
{
    int numPassageiros, maisPassageiros, menosPassageiros, totalPassageiros;
    int horas, horarioCheio, horarioVazio;

    maisPassageiros = 0;
    menosPassageiros = 45;
    totalPassageiros = 0;
    horarioVazio = 8;
    horarioCheio = 8;

    for(horas = 8; horas <= 18; horas++)
    {
        printf("Numero de passageiros das %d horas: ", horas);
        scanf("%d", &numPassageiros);

        verificaViagem(&numPassageiros);

        totalPassageiros += numPassageiros;

        if (numPassageiros < menosPassageiros) {
            horarioVazio = horas;
            menosPassageiros = numPassageiros;
        } else if (numPassageiros > maisPassageiros) {
            horarioCheio = horas;
            maisPassageiros = numPassageiros;
        }

    }

    printf("\nHorario de maior procura: %d horas\n", horarioCheio);
    printf("Assentos ocupados: %d\n\n", maisPassageiros);

    printf("Horario de menor procura: %d horas\n", horarioVazio);
    printf("Assentos ocupados: %d\n\n", menosPassageiros);

    printf("Média de passageiros: %.2f\n", (float)totalPassageiros/11);
    printf("Total de passageiros: %d\n", totalPassageiros);
    printf("Montante recebido: %d\n", totalPassageiros*22);

    return 0;
}

        // if (numPassageiros > 45 || numPassageiros < 0) {
            
        //     printf("Digite um número válido de passageiros!\n\n");
            
        //     horas--;

        // } else {
        //     atualizaViagem(numPassageiros, &maisPassageiros, &menosPassageiros, 
        //         &totalPassageiros, &horas, &horarioCheio, &horarioVazio);
        // }