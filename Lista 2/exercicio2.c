#include <stdio.h>
#include <math.h>
// rodar no terminal:
// cd Lista\ 2
// gcc exercicio2.c -lm -o exercicio2
// ./exercicio2

int DivisaoArredondada(int dividendo, int divisor) {
    float divisao;
    divisao = (float)dividendo/divisor;
    divisao = ceil(divisao);
    return divisao;
}

int main() {
    int matriculas, maximo, salas;
    printf("Digite o número de alunos matriculados: ");
    scanf("%i", &matriculas);
    printf("Digite o número máximo de alunos por sala: ");
    scanf("%i", &maximo);
    salas = DivisaoArredondada(matriculas, maximo);
    printf("Vai ser preciso %i salas\n", salas);

    return 0;
}