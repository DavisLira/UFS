#include <stdio.h>
#include <stdlib.h>

#define NMax 5  // Tamanho máximo da fila

typedef struct {
    int itens[NMax];
    int inicio;
    int fim;
    int qtdElementos;
} tipoFila;

// Inicializa a fila
void inicializarFila(tipoFila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->qtdElementos = 0;
}

// Verifica se a fila está cheia
int filaCheia(tipoFila *fila) {
    return (fila->qtdElementos == NMax);
}

// Verifica se a fila está vazia
int filaVazia(tipoFila *fila) {
    return (fila->qtdElementos == 0);
}

void inserirNaFila(tipoFila *fila, int info) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível inserir %d.\n", info);
        return;
    }

    fila->itens[fila->fim] = info;
    fila->fim = (fila->fim + 1) % NMax;
    fila->qtdElementos++;
}

int removerDaFila(tipoFila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Não é possível remover.\n");
        return -1;
    }

    int info = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % NMax;
    fila->qtdElementos--;
    return info;
}

void exibirFila(tipoFila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    int i = fila->inicio;
    for (int count = 0; count < fila->qtdElementos; count++) {
        printf("%d ", fila->itens[i]);
        i = (i + 1) % NMax;
    }
    printf("\n");
}

void menu() {
    printf("\n**********************************");
    printf("\n       Bem vindo a 'A FILA'       ");
    printf("\n   1 - inserir na fila            ");
    printf("\n   2 - remover da fila            ");
    printf("\n   3 - Exibir a fila              ");
    printf("\n   0 - Sair                       ");

    printf("\nEscolha uma opção: ");
}

int main() {
    tipoFila fila;
    inicializarFila(&fila);

    int opcMenu;
    
    do
    {
        menu();
        scanf("%d", &opcMenu);
        printf("\n");

        int valor = 0;
        
        switch (opcMenu)
        {
        case 1:
            printf("Digite o valor: ");
            scanf("%d", &valor);
            inserirNaFila(&fila, valor);
            break;
        
        case 2:
            printf("Removido: %d\n", removerDaFila(&fila));
            break;
        
        case 3:
            exibirFila(&fila);
            break;

        default:
            break;
        }

    } while (opcMenu != 0);

    return 0;
}
