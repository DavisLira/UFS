// MERGE SORT

#include <stdio.h>

void merge(int lista[], int listaEsquerda[], int tamanhoEsquerda, int listaDireita[], int tamanhoDireita) {
    int i = 0, j = 0, k = 0;

    // coloca em LISTA os números em ordem, até que todos os número sejam processados
    while (i < tamanhoEsquerda && j < tamanhoDireita) {
        if (listaEsquerda[i] <= listaDireita[j]) {
            lista[k++] = listaEsquerda[i++];
        } else {
            lista[k++] = listaDireita[j++];
        }
    }

    // caso ainda tenha número na lista esquerda, coloca dentro da lista completa
    while (i < tamanhoEsquerda) {
        lista[k++] = listaEsquerda[i++];
    }

    // caso ainda tenha número na lista direita, coloca dentro da lista completa
    while (j < tamanhoDireita) {
        lista[k++] = listaDireita[j++];
    }
}

void mergeSort(int lista[], int tamanho) {
    // verificação do tamanho para finalizar a ordenação
    if (tamanho <= 1) {
        return;
    }

    int tamanhoEsquerda = tamanho / 2;
    int listaEsquerda[tamanhoEsquerda];
    int tamanhoDireita = tamanho - tamanhoEsquerda;
    int listaDireita[tamanhoDireita];

    // separa os números da lista inicial em duas listas
    for (int i = 0; i < tamanhoEsquerda; i++) {
        listaEsquerda[i] = lista[i];
    }
    for (int i = tamanhoEsquerda; i < tamanho; i++) {
        listaDireita[i - tamanhoEsquerda] = lista[i];
    }

    // recursividade
    mergeSort(listaEsquerda, tamanhoEsquerda);
    mergeSort(listaDireita, tamanhoDireita);
    
    // ordenação
    merge(lista, listaEsquerda, tamanhoEsquerda, listaDireita, tamanhoDireita);
}

int main()
{
    const int TAMANHO = 10;
    int listaCompleta[] = {5, 6, 2, 8, 9, 3, 1, 4, 7, 4};
    // const int TAMANHO = 2;
    // int listaCompleta[] = {5, 6};
    
    mergeSort(listaCompleta, TAMANHO);

    for (int i = 0; i < TAMANHO; i++) {
        printf("*** %d ***\n", listaCompleta[i]);
    }

    return 0;
}
