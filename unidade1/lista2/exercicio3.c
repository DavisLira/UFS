#include <stdio.h>
#include <math.h>

/*
    Código que calcula o cúbo de um número por meio de um método
*/

int cubo(int x){
    // return x * x * x; // Fazendo cada multiplicação uma por uma
    return pow(x, 3) ; // Utilizando uma função da biblioteca <math.h>
}

int main() {
    int N; // Variável

    printf("Digite um número: "); // Salva um número digitado
    scanf("%i", &N);

    printf("O número ao cubo é: %i\n\n", cubo(N)); // Calcula o cubo do número e mostra ao usuário

    return 0;
}