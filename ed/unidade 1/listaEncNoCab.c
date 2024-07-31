// Lista Simplesmente Encadeada com nó cabeça com as seguintes funções implementadas:
// - Remover nó do início da lista
// - Remover nó do fim da lista
// - Destruir a lista
// - Pesquisar informação na lista e retornar índice onde a encontrou (considerar primeiro nó como de índice 0)
// - Inserir nó em determinada posição passada como parâmetro
// - Remover nó de determinada posição passada como parâmetro

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *proxNo;
} tipoNo;

typedef struct listaGerenciada {
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoLista;

void menu() {
    printf("*****************************\n");
    printf("   Digite a opção desejada   \n");
    printf("  1- inserir na frente \n");
    printf("  2- inserir no fim \n");
    printf("  3- exibir lista completa \n");
    printf("  4- remover 1° item \n");
    printf("  5- remover ultimo item \n");
    printf("  6- destruir lista \n");
    printf("  7- pesquisar posição \n");
    printf("  8- inserir em posição dada \n");
    printf("  9- remover em posição dada \n");
}

void inicializar (tipoLista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quant = 0;
}

/*Função de exibição da lista simplesmente encadeada*/
int exibirLista(tipoLista *lista) {
    tipoNo *atual;  //Variável que será usada para percorrer a lista*/

    if(lista->inicio == NULL) return 0;

    atual = lista->inicio;
    printf("\nLista encadeada: ");

    while(atual != NULL){
        printf("%3d", atual->dado);
        atual = atual->proxNo;
    }
    
    printf("\n");

    return 1;
}

int inserirListaVazia (tipoLista *lista, int valor) {
    tipoNo *novoNo = (tipoNo*) malloc(sizeof(tipoNo));

    if(novoNo == NULL) return 0;

    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    lista->inicio = novoNo;
    lista->fim = novoNo;
    lista->quant++;
}

int inserirNaFrente(tipoLista *lista){
    tipoNo *novoNo;

    int valor;
    printf("Digite um elemento: ");
    scanf("%d", &valor);

    if (lista->inicio == NULL) {
        inserirListaVazia(lista ,valor);
    } else {
        novoNo = (tipoNo*)malloc(sizeof(tipoNo));

        if(novoNo==NULL) return 0;

        novoNo->dado = valor;
        novoNo->proxNo = lista->inicio;
        lista->inicio = novoNo;
        lista->quant++;

        exibirLista(lista);
        return 1;
    }
}

int inserirNofim(tipoLista *lista){
    tipoNo *novoNo;

    int valor;
    printf("Digite um elemento: ");
    scanf("%d", &valor);

    if (lista->inicio == NULL) {
        inserirListaVazia(lista ,valor);
    } else {
        novoNo = (tipoNo*)malloc(sizeof(tipoNo));
        if(novoNo==NULL) return 0;

        novoNo->dado = valor;
        novoNo->proxNo = NULL;

        tipoNo *ultimoNo = lista->fim;
        ultimoNo->proxNo = novoNo;
        lista->fim = novoNo;
        lista->quant++;

        exibirLista(lista);
        return 1;
    }
}

int removerPrimeiro(tipoLista *lista) {
    if (lista->inicio == NULL) {
        printf(" Lista não inicializada! \n");
        return 0;
    }

    tipoNo *no1 = lista->inicio;
    lista->inicio = no1->proxNo;
    lista->quant--;

    free(no1);

    exibirLista(lista);
    return 1;
}

int removerUltimo(tipoLista *lista) {
    if (lista->inicio == NULL) {
        printf(" Lista não inicializada! \n");
        return 0;
    }

    tipoNo *ultimo = lista->inicio;
    tipoNo *penultimo = NULL;

    while (ultimo->proxNo != NULL) {
        penultimo = ultimo;
        ultimo = ultimo->proxNo;
    }

    if (penultimo == NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->quant = 0;

        free(ultimo);

        printf("  Lista esvaziada \n");
    } else {
        penultimo->proxNo = NULL;
        lista->fim = penultimo;
        lista->quant--;
        free(ultimo);
    }

    exibirLista(lista);
    return 1;
}

int destruir(tipoLista *lista) {
    tipoNo *no1 = lista->inicio;
    tipoNo *no2 = NULL;

    for (int i = 0; i < lista->quant; i++)
    {
        no2 = no1;
        no1 = no1->proxNo;
        free(no2);
    }
    
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quant = 0;
}

int procurar(tipoLista *lista) {
    tipoNo *atual;
    int cont = 0, valor;

    if(lista->inicio == NULL) return 0;

    atual = lista->inicio;

    printf("  Digite o valor a ser buscado: ");
    scanf("%d", &valor);

    while(atual != NULL) {
        if (atual->dado == valor)
        {
            printf("Posição de %d: %d \n", valor, cont);
            return 1;
        }
        atual = atual->proxNo;
        cont++;
    }

    printf("número nao encontrado\n");
    return 1;
}

int inserirNaPosicao(tipoLista *lista) {
    tipoNo *esquerda, *novoNo, *direita;
    int valor, posicao;

    if(lista->inicio == NULL) return 0;

    direita = lista->inicio;

    printf("  Digite a posição a ser inserida: ");
    scanf("%d", &posicao);
    
    if (posicao == 0) {
        inserirNaFrente(lista);
        return 1;
    } else if (posicao == lista->quant) {
        inserirNofim(lista);
        return 1;
    }

    if (posicao > lista->quant) {
        printf("  Não é possivel adicionar nessa posição \n");
        return 1;
    }

    printf("  Digite o valor: ");
    scanf("%d", &valor);

    novoNo = (tipoNo*)malloc(sizeof(tipoNo));
    novoNo->dado = valor;

    for (int i = 0; i < posicao; i++)
    {
        esquerda = direita;
        direita = esquerda->proxNo;
    }

    esquerda->proxNo = novoNo;
    novoNo->proxNo = direita;
    lista->quant++;

    exibirLista(lista);
    return 1;
}

int removerNaPosicao(tipoLista *lista) {
    tipoNo *esquerda, *direita;
    int posicao;

    printf("  Digite a posição a ser removida: ");
    scanf("%d", &posicao);
    
    if (posicao == 0) {
        removerPrimeiro(lista);
        return 1;
    } else if (posicao == lista->quant) {
        removerUltimo(lista);
        return 1;
    }

    if (posicao > lista->quant) {
        printf("  Não é tem elemento nessa posição \n");
        return 1;
    }

    direita = lista->inicio;
    for (int i = 0; i < posicao; i++)
    {
        esquerda = direita;
        direita = esquerda->proxNo;
    }

    esquerda->proxNo = direita->proxNo;
    lista->quant--;

    free(direita);

    return 1;
}

void main(){
    tipoLista lista;
    inicializar(&lista);

    int opc;

    do {
        menu();
        scanf("%d", &opc);

        switch (opc)
        {
        case 1: inserirNaFrente(&lista);
            break;
        case 2: inserirNofim(&lista);
            break;
        case 3: exibirLista(&lista);
            break;
        case 4: removerPrimeiro(&lista);
            break;
        case 5: removerUltimo(&lista);
            break;
        case 6: destruir(&lista);
            break;
        case 7: procurar(&lista);
            break;
        case 8: inserirNaPosicao(&lista);
            break;
        case 9: removerNaPosicao(&lista);
            break;

        default:
            break;
        }
    } while (opc != 0);

}