#include <stdio.h>
#include <math.h>

void media3(float v1, float v2, float v3,float *media) {
    *media = (v1+v2+v3)/3;
}

void desvioPadrao(float v1, float v2, float v3, float media, float *desvio) {
    *desvio = sqrt((((v1-media)*(v1-media))+((v2-media)*(v2-media))+((v3-media)*(v3-media)))/2);
}

void incertezaA(float desvio, float *A) {
    *A = desvio/sqrt(3);
}

void incertezaC(float A, float B, float *C) {
    *C = sqrt((A*A) + (B*B));
}

void incertezaT(float t, float incertezaC, float *sigmaT2) {
    *sigmaT2 = 2*t*incertezaC;
}

int main()
{
    float medida1, medida2, medida3, media, desvio, sigmaA, sigmaB, sigmaC, sigmaT2;

    while (1)
    {   
        printf("Digite as 3 medidas:\n");
        scanf("%f", &medida1);

        if (medida1 == -1) {
            break;
        }
        
        scanf("%f", &medida2);
        scanf("%f", &medida3);

        media3(medida1, medida2, medida3, &media);

        desvioPadrao(medida1, medida2, medida3, media, &desvio);

        incertezaA(desvio, &sigmaA);

        // printf("Digite a incerteza B: ");
        // scanf("%f", &sigmaB);

        sigmaB = 0.0001;

        incertezaC(sigmaA, sigmaB, &sigmaC);

        incertezaT(media, sigmaC, &sigmaT2);

        printf("\nMedia: %.4f\n", media);
        printf("Sigma A: %.4f\n", sigmaA);
        printf("Sigma C: %.4f\n", sigmaC);
        printf("Resultado T: %.4f + - %.4f\n\n", media, sigmaC);

        printf("T2: %.4f\n", media*media);
        printf("Sigma T2: %.4f\n", sigmaT2);
        printf("Resultado T2: %.4f + - %.4f\n\n", media*media, sigmaT2);

    }
}