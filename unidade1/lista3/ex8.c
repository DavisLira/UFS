#include <stdio.h>
#include <ctype.h>

void identificaUnidade(int numero) {
    printf("Unidade -> %d\n\n", numero % 10);
}

void identificaDezena(int numero) {
    printf("Dezena -> %d\n\n", numero / 10 % 10);
}

void identificaCentena(int numero) {
    printf("Centena -> %d\n\n", numero / 100 % 10);
}

void identificaUnidadeMilhar(int numero) {
    printf("Unidade de Milhar -> %d\n\n", numero / 1000 % 10);
}

void identificarDezenaMilhar(int numero) {
    printf("Dezena de milhar -> %d\n\n", numero / 10000 % 10);
}

int main() {
    char menu;
    int numero;

    printf("U – unidade, D – dezena, C – centena, M – unidade de milhar e Z – dezena de milhar\n");
    scanf(" %c", &menu);
    menu = toupper(menu);

    if(menu != 'U' && menu != 'D' && menu != 'C' && menu != 'M' && menu != 'Z'){
        printf("Opção inválida\n\n");
        return 0;
    }

    printf("Digite um número de 0 a 99999: ");
    scanf("%d", &numero);

    if(numero < 0 || numero >99999){
        printf("Número inválido\n\n");
        return 0;
    }

    switch (menu)
    {
    case 'U':
        identificaUnidade(numero);
        break;
    case 'D':
        identificaDezena(numero);
        break;
    case 'C':
        identificaCentena(numero);
        break;
    case 'M':
        identificaUnidadeMilhar(numero);
        break;
    case 'Z':
        identificarDezenaMilhar(numero);
        break;
    }

    return 0;
}