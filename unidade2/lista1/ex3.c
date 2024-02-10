// ônibus ufs atalaira - qual melhor horário?

#include <stdio.h>

void atualizaViagem(int qtd, int *qtdMaior, int *qtdMenor, int *qtdTotal,
                        int *hora, int *horaMaior, int *horaMenor) 
{
    *qtdTotal += qtd;

    if (qtd < *qtdMenor) {
        *horaMenor = *hora;
        *qtdMenor = qtd;
    }
    if (qtd > *qtdMaior) {
        *horaMaior = *hora;
        *qtdMaior = qtd;
    }
    
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

        if (numPassageiros > 45 || numPassageiros < 0) {
            
            printf("Digite um número válido de passageiros!\n\n");
            
            horas--;

        } else if (numPassageiros >= 0 || numPassageiros <= 45) {
            atualizaViagem(numPassageiros, &maisPassageiros, &menosPassageiros, 
                &totalPassageiros, &horas, &horarioCheio, &horarioVazio);
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