#include <stdio.h>

int main() {
    int dias, meses = 0;

    printf("Digite uma quantidade de dias: ");
    scanf("%d", &dias);

    while(dias >= 30) {
        dias -= 30;
        meses++;
    }

    if(meses == 0) {
        printf("Essa quantidade de dias não da 1 mes\n\n");
    } else if (meses == 1) {
        printf("Isso equivale a 1 mes\n\n");
    } else {
        printf("Isso equivale a %d meses\n\n", meses);
    }
    
}