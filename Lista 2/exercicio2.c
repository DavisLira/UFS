#include <stdio.h>
#include <math.h>

/*
    Código que faz o cálculo de quantas salas de aula são 
    necessárias de acordo com a quantidade de alunos matriculados 
    e a quantidade máxima de alunos por sala
*/

int DivisaoArredondada(int dividendo, int divisor) {
    // Essa divisão equivale a uma regra de três

    float divisao;

    divisao = (float)dividendo/divisor; // Calcula a divisão entre 2 números
    divisao = ceil(divisao); // Arredonda a divisão para cima

    return divisao; // Retorna a divisão
}

int main() {
    int matriculas, maximo, salas; // Variáveis

    printf("Digite o número de alunos matriculados: "); // Quantidade de alunos matriculados
    scanf("%i", &matriculas);

    printf("Digite o número máximo de alunos por sala: "); // Número máximo de alunos por sala
    scanf("%i", &maximo);

    salas = DivisaoArredondada(matriculas, maximo); // Função que calcula a quantidade de salas

    printf("Vai ser preciso %i salas\n", salas); // Mostra a quantidade de salas

    return 0;
}