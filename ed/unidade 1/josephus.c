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
    int lenght;
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
    list->lenght++;

    printf("Head: %s\n", list->tail->name);
}

typeNode *sortNodeToRemove(typeList *list, typeNode **current, int totalSpins)
{
    if (current == NULL || list->lenght < 2)
    {
        printf("Lista deve conter pelo menos 2 elementos para spin de remoção");
        return NULL;
    }

    typeNode *sorted = (*current)->nextNode;
    
    for (short i = 0; i <= totalSpins; i++)
    {
        sorted = sorted->nextNode;
        *(current) = sorted->nextNode;
    }

    return sorted;
}

void removeNodeFromCircleList(typeList *list, typeNode *removing)
{
    typeNode *newTail = list->tail;

    if (removing == list->tail) {
        for (int i = 0; i < list->lenght-1; i++)
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

    list->lenght--;
}

void showList(typeList *list)
{
    typeNode *current = list->tail;

    for (int i = 0; i < list->lenght; i++)
    {
        printf(" - %s -", current->name);
        current = current->nextNode;
    }
    printf("\n");
}

int main()
{
    short clientsNumber;

    typeList *clientsList = (typeList *)malloc(sizeof(typeList));

    srand(time(NULL));

    clientsList->tail = NULL;
    clientsList->lenght = 0;

    do 
    {
        printf("Quantos clientes participarão da premiação? ");
        scanf("%hd", &clientsNumber);

        if (clientsNumber < 2) 
            printf("A premiação deve ter pelo menos 1 cliente.\n");

        
    } while (clientsNumber < 2);

    getchar();

    for (short i = 0; i < clientsNumber; i++)
    {
        char clientName[30];

        printf("Nome do cliente %d: ", i + 1);
        fgets(clientName, sizeof(clientName), stdin);

        short len = strlen(clientName);
        if (len > 0 && clientName[len - 1] == '\n')
        clientName[len - 1] = '\0';

        appendOnCircleList(clientsList, clientName);
    }

    showList(clientsList);

    typeNode *currentSorting = clientsList->tail;

    while (clientsList->lenght > 1)
    {
        short totalOfSpins = (rand() % (clientsList->lenght - 1 + 1)) + 1;
        typeNode *removed = sortNodeToRemove(clientsList, &currentSorting, totalOfSpins);

        printf("%s perdeu... rodando de novo! \n\n", removed->name);
        removeNodeFromCircleList(clientsList, removed);

        printf("Lista atual: ");
        showList(clientsList);
    }

    printf("\nÚltimo: %s\n", clientsList->tail->name);

    return EXIT_SUCCESS;
}