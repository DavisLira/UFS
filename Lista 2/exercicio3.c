#include <stdio.h>
#include <math.h>

int cubo(int x){
    // return x * x * x;
    return pow(x, 3) ;
}

int main() {
    int N;
    printf("Digite um número: ");
    scanf("%i", &N);
    printf("O número ao cubo é: %i\n\n", cubo(N));
    return 0;
}