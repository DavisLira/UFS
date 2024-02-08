    #include <stdio.h>

    int main() {
        float ph;

        do
        {
            printf("Digite o ph: ");
            scanf("%f", &ph);

            if(ph > 7) {
                printf("BASICA\n");
            } else if (ph == 7) {
                printf("NEUTRA\n");
            } else if (ph < 7 && ph > 0) {
                printf("ACIDA\n");
            }

        } while (ph != -1);
        
    }