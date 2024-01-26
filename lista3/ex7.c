#include <stdio.h>
#include <math.h>

void calculaArea(float lado) {
    printf("%.2f\n", lado * lado);
    
}

void calculaPerimetro(float lado) {
    printf("%.2f\n", lado * 4);
    
}

void calculaDiagonal(float lado) {
    printf("%.2f\n", sqrt(2) * lado);

}

int main() {
    int menu;
    float lado;

    printf("1 – area, 2 – perímetro e 3 – diagonal\n");
    scanf("%d", &menu);
    
    if(menu != 1 && menu != 2 && menu != 3) {
        printf("Opção inválida\n\n");
        return 0;
    }

    printf("Digite o lado do quadrado: ");
    scanf("%f", &lado);

    if(lado < 0) {
        printf("Medida inválida\n\n");
        return 0;
    }

    switch (menu)
    {
    case 1:
        calculaArea(lado);
        break;
    case 2:
        calculaPerimetro(lado);
        break;
    case 3:
        calculaDiagonal(lado);
        break;
    }
}