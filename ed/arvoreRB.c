#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *pai, *esq, *dir;
    // cor == 1 para rubro e 0 para negro
    int cor;
} tipoNo;

typedef struct arvore {
    tipoNo *raiz;
    int quant;
} tipoArvore;

void inicializarArvore(tipoArvore *arvore) {
    arvore->raiz = NULL;
    arvore->quant = 0;
}

tipoNo* inserirNo(tipoNo* raiz, tipoNo* novo) {
    if (raiz == NULL) {
        return novo;
    }

    if (novo->valor < raiz->valor) {
        raiz->esq = inserirNo(raiz->esq, novo);
        raiz->esq->pai = raiz;
    } else if (novo->valor > raiz->valor) {
        raiz->dir = inserirNo(raiz->dir, novo);
        raiz->dir->pai = raiz;
    }

    // Aqui você deveria implementar as correções de cor e rotação da árvore rubro-negra
    return raiz;
}

void criarNo(tipoArvore *arvore, int valor) {
    tipoNo *novo = (tipoNo*) malloc(sizeof(tipoNo));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->cor = 1;
    novo->pai = NULL;

    arvore->raiz = inserirNo(arvore->raiz, novo);

    return;
}

void mostrarNo(tipoNo* no) {
    if (no != NULL) {
        mostrarNo(no->esq);  // Exibir a subárvore esquerda
        printf("Valor: %d\n", no->valor);
        printf("Cor: %s\n", no->cor == 1 ? "RURO" : "NEGRO");
        printf("\n\n");
        mostrarNo(no->dir);  // Exibir a subárvore direita
    }
}

void mostrar(tipoArvore *arvore) {
    if (arvore->raiz == NULL) {
        printf("Árvore vazia!\n");
    } else {
        mostrarNo(arvore->raiz);
    }
}

int main() {
    tipoArvore arvore;
    inicializarArvore(&arvore);

    int opc, valor;

    do {
        printf("** Árvore Rubro-Negra **\n");
        printf("  1 - Inserir\n");
        printf("  2 - Remover\n");
        printf("  3 - Mostrar\n");
        printf("  4 - Sair\n");
        printf("  Escolha uma opção: ");
        scanf("%d", &opc);
        printf("\n\n");

        switch (opc) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                criarNo(&arvore, valor);
                break;

            case 2:
                printf("Ainda nao remove/n/n");
                break;

            case 3:
                mostrar(&arvore);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

        printf("\n");
    } while (opc != 4);

    return 0;
}