// MERGE SORT PARA STRINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int TAMANHO_STRING = 20;

void merge(char lista[][TAMANHO_STRING], char listaEsquerda[][TAMANHO_STRING], int tamanhoEsquerda, char listaDireita[][TAMANHO_STRING], int tamanhoDireita) {
    int i = 0, j = 0, k = 0;

    // coloca em LISTA as STRINGS em ordem, ignorando letras minúsculas e maiúsculas,
    // até que todos as strings sejam processadas
    while (i < tamanhoEsquerda && j < tamanhoDireita) {
        // int resultado = strcasecmp(listaEsquerda[i], listaDireita[j]);
        int resultado = strcmp(listaEsquerda[i], listaDireita[j]);
        if (resultado <= 0) {
            strcpy(lista[k++], listaEsquerda[i++]);
        } else {
            strcpy(lista[k++], listaDireita[j++]);
        }
    }

    // caso ainda tenha strings na lista esquerda, coloca dentro da lista completa
    while (i < tamanhoEsquerda) {
        strcpy(lista[k++], listaEsquerda[i++]);
    }

    // caso ainda tenha strings na lista direita, coloca dentro da lista completa
    while (j < tamanhoDireita) {
        strcpy(lista[k++], listaDireita[j++]);
    }
}

void mergeSort(char lista[][TAMANHO_STRING], int tamanho) {
    // verificação do tamanho para finalizar a ordenação
    if (tamanho <= 1) {
        return;
    }

    int tamanhoEsquerda = tamanho / 2;
    char listaEsquerda[tamanhoEsquerda][TAMANHO_STRING];

    int tamanhoDireita = tamanho - tamanhoEsquerda;
    char listaDireita[tamanhoDireita][TAMANHO_STRING];

    // separa as palavras da lista inicial em duas listas
    for (int i = 0; i < tamanhoEsquerda; i++) {
        strcpy(listaEsquerda[i], lista[i]);
    }
    for (int i = tamanhoEsquerda; i < tamanho; i++) {
        strcpy(listaDireita[i - tamanhoEsquerda], lista[i]);
    }

    // recursividade
    mergeSort(listaEsquerda, tamanhoEsquerda);
    mergeSort(listaDireita, tamanhoDireita);
    
    // ordenação
    merge(lista, listaEsquerda, tamanhoEsquerda, listaDireita, tamanhoDireita);
}

int main()
{
    const int TAMANHO = 25;
    char listaCompleta[TAMANHO][TAMANHO_STRING];
    strcpy(listaCompleta[0], "CAJU");
    strcpy(listaCompleta[1], "FRAMBOESA");
    strcpy(listaCompleta[2], "DAMASCO");
    strcpy(listaCompleta[3], "BANANA");
    strcpy(listaCompleta[4], "ABACAXI");
    strcpy(listaCompleta[5], "GUARANA");
    strcpy(listaCompleta[6], "GOIABA");
    strcpy(listaCompleta[7], "AMORA");
    strcpy(listaCompleta[8], "CACAU");
    strcpy(listaCompleta[9], "CARAMBOLA");
    strcpy(listaCompleta[10], "CAJA");
    strcpy(listaCompleta[11], "JABUTICABA");
    strcpy(listaCompleta[12], "CUPUACU");
    strcpy(listaCompleta[13], "KIWI");
    strcpy(listaCompleta[14], "JAMBO");
    strcpy(listaCompleta[15], "JACA");
    strcpy(listaCompleta[16], "MACA");
    strcpy(listaCompleta[17], "LIMAO");
    strcpy(listaCompleta[18], "LARANJA");
    strcpy(listaCompleta[19], "MAMAO");
    strcpy(listaCompleta[20], "MANGABA");
    strcpy(listaCompleta[21], "MARACUJA");
    strcpy(listaCompleta[22], "MANGA");
    strcpy(listaCompleta[23], "MORANGO");
    strcpy(listaCompleta[24], "PESSEGO");
    
    mergeSort(listaCompleta, TAMANHO);

    for (int i = 0; i < TAMANHO; i++) {
        printf("*** %s ***\n", listaCompleta[i]);
    }

    return 0;
}
