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
}

void rotacaoEsquerda(tipoArvore *arvore, tipoNo *no) {
    tipoNo *dir = no->dir;
    no->dir = dir->esq;
    
    if (dir->esq != NULL) {
        dir->esq->pai = no;
    }
    
    dir->pai = no->pai;
    
    if (no->pai == NULL) {
        arvore->raiz = dir;
    } else if (no == no->pai->esq) {
        no->pai->esq = dir;
    } else {
        no->pai->dir = dir;
    }
    
    dir->esq = no;
    no->pai = dir;
}

void rotacaoDireita(tipoArvore *arvore, tipoNo *no) {
    tipoNo *esq = no->esq; // Filho da esquerda do nó
    
    no->esq = esq->dir; // Filho direito de esq vira o filho esquerdo do nó

    // Se o filho direito de esq existir, atualize seu pai para nó
    if (esq->dir != NULL) {
        esq->dir->pai = no;
    }

    esq->pai = no->pai; // pai de esq vira pai de nó

    // Se nó for a raiz da árvore, esq se torna raiz
    if (no->pai == NULL) {
        arvore->raiz = esq;
    }
    else if (no == no->pai->esq) {
        no->pai->esq = esq; // Se nó era o filho esquerdo, agora o filho esquerdo será esq
    }
    else {
        no->pai->dir = esq; // Se nó era o filho direito, agora o filho direito será esq
    }

    // Nó vira filho direito de esq
    esq->dir = no;
    
    // e esq vira pai de no
    no->pai = esq;
}


void verificarCorrecoes(tipoArvore *arvore, tipoNo *no) {
    // Caso raiz seja Rubro, vira negra
    if (no == arvore->raiz && no->cor == 1) {
        printf("Raiz (%d) virou negro\n\n", no->valor);
        no->cor = 0;
        return;
    }

    // Caso 1: Se o pai do nó é negro, não há violação
    if (no->pai == NULL || no->pai->cor == 0) {
        printf("Não precisa de correção!\n");
        return;
    }

    // Caso 2 e 3: Verificar o tio
    tipoNo *avo = no->pai->pai;

    // Não tem avo, o pai do nó é a raiz
    if (avo == NULL) {
        return;
    }

    // se o pai do nó é o filho esquerdo do avo, o tio é o filho direito do avo
    // se o pai do nó é o filho direito do avo, o tio é o filho esquerdo do avo
    tipoNo *tio = (no->pai == avo->esq) ? avo->dir : avo->esq;

    // Caso 2: O pai e o tio são rubros
    if (tio != NULL && tio->cor == 1) {
        printf("O pai (%d) de (%d) virou negro\n", no->pai->valor, no->valor);
        no->pai->cor = 0; // o pai vira negro

        printf("O tio (%d) de (%d) virou negro\n", tio->valor, no->valor);
        tio->cor = 0; // o tio vira negro

        printf("O avô (%d) de (%d) virou rubro\n\n", avo->valor, no->valor);
        avo->cor = 1; // o avo vira rubro

        verificarCorrecoes(arvore, avo); // Continuar verificando o avô
    } else {
        // Caso 3: O tio é negro (ou NULL)

        // nó é filho da direita do pai e
        // pai é filho da esquerda do avo
        if (no == no->pai->dir && no->pai == avo->esq) {
            // Rotação para a esquerda no pai
            printf("Rotacionando pai (%d) para esquerda\n", no->pai->valor);
            rotacaoEsquerda(arvore, no->pai);
            no = no->esq;  // Ajuste do novo nó
        } else if (no == no->pai->esq && no->pai == avo->dir) {
            // Rotação para a direita no pai
            printf("Rotacionando pai (%d) para direita\n", no->pai->valor);
            rotacaoDireita(arvore, no->pai);
            no = no->dir;  // Ajuste do novo nó
        }

        // Caso 3 (continuação): Rotação simples
        if (no == no->pai->esq) {
            // se o nó é filho da esquerda do pai, rotação para a direita no avo
            printf("Rotacionando avô (%d) para direita\n", avo->valor);
            rotacaoDireita(arvore, avo);
        } else {
            // se o nó é filho da direita do pai, rotação para a esquerda no avo
            printf("Rotacionando avô (%d) para esquerda\n", avo->valor);
            rotacaoEsquerda(arvore, avo);
        }

        // Ajustar as cores após a rotação
        printf("Pai (%d) virou negro\n", no->pai->valor);
        no->pai->cor = 0;

        printf("Avô (%d) virou rubro\n", avo->valor);
        avo->cor = 1;
    }
}

tipoNo* inserirNo(tipoNo* raiz, tipoNo* novo) {
    if (raiz == NULL) {
        return novo;
    }

    if (novo->valor < raiz->valor) {
        printf("Inserindo (%d) a esquerda de (%d)\n", novo->valor, raiz->valor);
        raiz->esq = inserirNo(raiz->esq, novo);
        raiz->esq->pai = raiz;
    } else if (novo->valor > raiz->valor) {
        printf("Inserindo (%d) a direita de (%d)\n", novo->valor, raiz->valor);
        raiz->dir = inserirNo(raiz->dir, novo);
        raiz->dir->pai = raiz;
    }

    return raiz;
}

void criarNo(tipoArvore *arvore, int valor) {
    tipoNo *novo = (tipoNo*) malloc(sizeof(tipoNo));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->cor = 1;
    novo->pai = NULL;

    printf("\n\nCriando nó (%d) RUBRO\n", valor);

    if (arvore->raiz == NULL) {
        printf("Nó (%d) é raiz\n", novo->valor);
    }

    arvore->raiz = inserirNo(arvore->raiz, novo);

    verificarCorrecoes(arvore, novo);

    return;
}

// Mostrando no sentido LNR
void mostrarNo(tipoArvore *arvore, tipoNo* no, int linha) {
    if (no != NULL) {
        mostrarNo(arvore, no->esq, linha+1);  // Exibir a subárvore esquerda
        printf("Valor: %d\n", no->valor);
        printf("Cor: %s\n", no->cor == 1 ? "RUBRO" : "NEGRO");
        printf("Linha: %d\n", linha);
        if (no == arvore->raiz){
            printf("Raiz!\n");
        }
        printf("\n\n");
        mostrarNo(arvore, no->dir, linha+1);  // Exibir a subárvore direita
    }
}

void mostrar(tipoArvore *arvore) {
    if (arvore->raiz == NULL) {
        printf("Árvore vazia!\n");
    } else {
        int linha = 0;
        mostrarNo(arvore, arvore->raiz, linha);
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