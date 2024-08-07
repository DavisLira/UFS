#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    char name[30];
    struct node *nextNode;
} typeNode;

typedef struct list
{
    typeNode *tail;
    int length;
} typeList;

void appendOnCircleList(typeList *list, char value[30])
{
    typeNode *newNode = (typeNode *)malloc(sizeof(typeNode));

    if (newNode == NULL)
    {
        printf("Erro na alocação de memória.");
        return;
    }

    strcpy(newNode->name, value);

    if (list->tail == NULL) // 1° alocação
    {
        list->tail = newNode;
        newNode->nextNode = newNode;
    }
    else // após a 1° alocação
    {
        newNode->nextNode = list->tail->nextNode;
        list->tail->nextNode = newNode;
        list->tail = newNode;
    } 
    list->length++;
}

typeNode *sortNodeToRemove(typeList *list, typeNode **current, int totalSpins)
{
    if (current == NULL || list->length < 2)
    {
        printf("Lista deve conter pelo menos 2 elementos para spin de remoção");
        return NULL;
    }

    typeNode *sorted = *current;
    
    for (short i = 1; i < totalSpins; i++)
    {
        printf("passando por: %s\n", sorted->name);
        sorted = sorted->nextNode;
    }
    
    printf("passando por: %s\n", sorted->name);
    
    *current = sorted->nextNode;

    return sorted;
}

void removeNodeFromCircleList(typeList *list, typeNode *removing)
{
    typeNode *newTail = list->tail;

    if (removing == list->tail) {
        for (int i = 0; i < list->length-1; i++)
        {
            newTail = newTail->nextNode;
        }
        newTail->nextNode = list->tail->nextNode;
        free(list->tail);
        list->tail = newTail;
    } else
    {
        typeNode *past = list->tail;
        typeNode *toRemove = past->nextNode;

        while (toRemove != removing)
        {
            past = toRemove;
            toRemove = past->nextNode;
        }

        past->nextNode = toRemove->nextNode;
        free(toRemove);
    }

    list->length--;
}

void showList(typeList *list)
{
    if (list->tail == NULL)
    {
        printf("Lista vazia\n");
        return;
    }

    typeNode *current = list->tail->nextNode;

    for (int i = 0; i < list->length; i++)
    {
        printf("%s", current->name);
        current = current->nextNode;

        if (i != list->length - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main()
{
    short clientsNumber;

    typeList *clientsList = (typeList *)malloc(sizeof(typeList));

    srand(time(NULL));

    clientsList->tail = NULL;
    clientsList->length = 0;

    do 
    {
        printf("Quantos clientes participarão da premiação? ");
        scanf("%hd", &clientsNumber);

        if (clientsNumber < 2) 
            printf("A premiação deve ter pelo menos 2 clientes.\n");

        
    } while (clientsNumber < 2);

    getchar();

    for (short i = 0; i < clientsNumber; i++)
    {
        char clientName[30];

        printf("Nome do %d° cliente: ", i + 1);
        fgets(clientName, sizeof(clientName), stdin);

        short len = strlen(clientName);
        if (len > 0 && clientName[len - 1] == '\n')
        clientName[len - 1] = '\0';

        appendOnCircleList(clientsList, clientName);
    }

    typeNode *currentSorting = clientsList->tail->nextNode;

    while (clientsList->length > 1)
    {
        short totalOfSpins = (rand() % (clientsList->length - 1 + 1)) + 1;
        showList(clientsList);
        printf("Começando com: %s\n", currentSorting->name);
        printf("Número sorteado: %d\n", totalOfSpins);
        typeNode *removed = sortNodeToRemove(clientsList, &currentSorting, totalOfSpins);

        printf("\n%s perdeu... rodando de novo! \n", removed->name);
        removeNodeFromCircleList(clientsList, removed);

        printf("Clientes na roda: ");
        showList(clientsList);
    }

    printf("\n%s ganhou!\n", clientsList->tail->name);

    free(clientsList);
    return EXIT_SUCCESS;
}
