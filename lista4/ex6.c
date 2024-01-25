#include <stdio.h>

int main() {
    int port, mat, aprovados = 0;
    float red;

    do
    {
        printf("Questões de portugues: ");
        scanf("%d", &port);

        if (port < 0) {
            break;
        }
        
        printf("Questões de matematica: ");
        scanf("%d", &mat);
        printf("Nota na redacao: ");
        scanf("%f", &red);

        if(port >= 40 && mat >= 21 && red >= 7){
            aprovados++;
        }

    } while (1);
    
    printf("Aprovados: %d\n", aprovados);
}