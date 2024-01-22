#include <stdio.h>

void calculaMediaPonderada(float nota1, float nota2,float nota3, float *media) {
    *media = (nota1 + nota2*2 + nota3*3) / 6;
}

int main()
{
    float nota1, nota2, nota3, media;

    printf("Digite a primeira nota: ");
    scanf("%f", &nota1);
    printf("Digite a segunda nota: ");
    scanf("%f", &nota2);
    printf("Digite a terceira nota: ");
    scanf("%f", &nota3);

    calculaMediaPonderada(nota1, nota2, nota3, &media);

    if(media < 5) {
        printf("Aluno reprovado\n");
    } else if (media >= 5 && media < 7) {
        printf("Aluno em recuperação\n");
    } else {
        printf("Aluno aprovado\n");
    }

    return 0;
}
