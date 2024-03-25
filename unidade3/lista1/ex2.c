// Busca binária com string

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int bbinaria (char chave[20], int inicio, int fim, char vetor[][20]) {
    if (fim < inicio) {
        return -1;
    }
    else {
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(vetor[meio], chave);

        if (resultado == 0){
            return meio;
        }
        else{
            if (resultado < 0) {
                return bbinaria (chave, meio+1, fim, vetor);
            }
            else {
                return bbinaria (chave, inicio, meio-1, vetor);
            }
        }
    }
}

int main() 
{
    char palavra[20];
    int posicao;

    char vetor[][20] = {"ABACAXI", "BANANA", "CAJU", "DAMASCO", "FRAMBOESA", "GOIABA", "GUARANA"};

    printf("Digite a palavra a ser buscada: ");
    scanf(" %14[^\n]s", palavra);

    for (int i = 0; i < 20; i++) {
        palavra[i] = toupper(palavra[i]);
    }
    
    posicao = bbinaria(palavra, 0, 7, vetor);

    if (posicao == -1) {
        printf("A palavra não foi encontrada!\n");
    } else {
        printf("A Palavra %s está na posição %d\n", palavra, posicao);
        printf("*** %s ***\n", vetor[posicao]);
    }

    return 0;
}
