#include <stdio.h>

void verifica(int num, int div1, int div2, int *resto1, int *resto2) {

    *resto1 = num % div1;
    *resto2 = num % div2;
}

int main() {
    int num, div1, div2, resto1, resto2;

    printf("Digite um número: ");
    scanf("%d", &num);
    printf("Digite o primeiro divisor: ");
    scanf("%d", &div1);
    printf("Digite o segundo divisor: ");
    scanf("%d", &div2);

    verifica(num, div1, div2, &resto1, &resto2);

    if (((resto1 == 0) && (resto2 != 0)) || ((resto1 != 0) && (resto2 == 0))) {
        printf("ATENDE CONDIÇÂO\n");    
    } else {
        printf("NÃO ATENDE CONDIÇÃO\n");
    }

    return 0;
}

