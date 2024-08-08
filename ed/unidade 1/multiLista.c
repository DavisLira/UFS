// Implemente a multilista mostrada no exemplo que deve ter as seguintes funções:
// Criar disciplina
// Matricular aluno em disciplina
// Excluir aluno de disciplina
// Informar Lista de disciplinas com a quantidade de alunos matriculados em cada uma delas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    char nomeAluno[21];
    struct aluno *proxAluno;
} tipoAluno;

typedef struct disciplina {
    char nomeDisciplina[21];
    int quantAlunos;
    tipoAluno *primeiroAluno;
    tipoAluno *ultimoAluno;
    struct disciplina *proxDisciplina;
} tipoDisciplina;

typedef struct listaGerenciada {
    tipoDisciplina *inicio;
    tipoDisciplina *fim;
    int quant;
} tipoLista;

void inicializarLista (tipoLista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quant = 0;
}

void menu() {
    printf("******************************\n");
    printf("    Digite a opção desejada   \n");
    printf("  1 - Criar disciplina        \n");
    printf("  2 - Matricular aluno        \n");
    printf("  3 - Mostrar aluno           \n");
    printf("  4 - Excluir aluno           \n");
    printf("  5 - Quantidade alunos       \n");
    printf("  0 - Sair                    \n");
}

void criarDisciplina(tipoLista *lista) {
    tipoDisciplina *novaDisciplina = (tipoDisciplina*)malloc(sizeof(tipoDisciplina));
    if(novaDisciplina == NULL) return;

    char nome[21];
    printf("\n  Digite o nome da disciplina: ");
    scanf(" %20[^\n]s", nome);

    strcpy(novaDisciplina->nomeDisciplina, nome);
    novaDisciplina->proxDisciplina = NULL;

    if (lista->inicio == NULL) // Caso seja a 1° disciplina
    {
        lista->inicio = novaDisciplina;
        lista->fim = novaDisciplina;
    } else 
    {
        lista->fim->proxDisciplina = novaDisciplina;
        lista->fim = novaDisciplina;
    }

    novaDisciplina->quantAlunos = 0;
    novaDisciplina->primeiroAluno = NULL;
    novaDisciplina->ultimoAluno = NULL;
    lista->quant++;
}

tipoDisciplina* escolherDisciplina(tipoLista *lista) {
    
    printf("\n******************************\n");
    printf("    Escolha a Disciplina:       \n");

    tipoDisciplina *atual = lista->inicio;
    for (int i = 1; i <= lista->quant; i++)
    {
        printf("  %d - %s \n", i, atual->nomeDisciplina);
        atual = atual->proxDisciplina;
    }
    printf("\n");

    int disc;
    scanf("%d", &disc);
    
    while (disc < 1 || disc > lista->quant)
    {
        printf("Digite uma disciplina válida: ");
        scanf("%d", &disc);
        printf("\n\n");
    }

    tipoDisciplina *disciplina = lista->inicio;
    for (int i = 1; i < disc; i++)
    {
        disciplina = disciplina->proxDisciplina;
    }

    return disciplina;
}

void matricularAluno(tipoLista *lista, tipoDisciplina *disciplina) {
    tipoAluno *novoAluno = (tipoAluno*)malloc(sizeof(tipoAluno));
    char nomeAluno[21];

    printf("Digite o nome do aluno: ");
    scanf(" %20[^\n]s", nomeAluno);

    strcpy(novoAluno->nomeAluno, nomeAluno);
    novoAluno->proxAluno = NULL;

    if (disciplina->primeiroAluno == NULL) // Caso seja a 1° aluno
    {
        printf("Primeiro aluno adicionado!\n\n");
        disciplina->primeiroAluno = novoAluno;
        disciplina->ultimoAluno = novoAluno;
    } else 
    {
        printf("Aluno número %d adicionado!\n\n", disciplina->quantAlunos +1);
        disciplina->ultimoAluno->proxAluno = novoAluno;
        disciplina->ultimoAluno = novoAluno;
    }

    disciplina->quantAlunos++;
}

void mostrarAlunos(tipoLista *lista, tipoDisciplina *disciplina) {
    tipoAluno *atual = disciplina->primeiroAluno;

    printf(" Alunos: \n");
    
    for (int i = 1; i <= disciplina->quantAlunos; i++)
    {
        printf("  %d - %s \n", i, atual->nomeAluno);
        atual = atual->proxAluno;
    }
    
    printf("\n\n");
}

void removerAluno(tipoLista *lista, tipoDisciplina *disciplina) {
    printf("  Escolha um dos");
    mostrarAlunos(*&lista, disciplina);

    int opcAluno;
    scanf("%d", &opcAluno);

    tipoAluno *aluno = disciplina->primeiroAluno;
    tipoAluno *anterior = disciplina->primeiroAluno;

    if (opcAluno == 1)
    {
        disciplina->primeiroAluno = aluno->proxAluno;
        free(aluno);
    } else {
        for (int i = 1; i < opcAluno; i++)
        {
            if (i != 1)
            {
                anterior = aluno;
            } 
            
            aluno = aluno->proxAluno;
        }
        
        anterior->proxAluno = aluno->proxAluno;
        free(aluno);
    }
    
    disciplina->quantAlunos--;
}

void mostrarTudo(tipoLista *lista) {
    tipoDisciplina *disciplina = lista->inicio;

    for (int i = 0; i < lista->quant; i++)
    {
        printf("Disciplina: %s\n", disciplina->nomeDisciplina);
        printf("Quantidade alunos: %d\n\n", disciplina->quantAlunos);
        disciplina = disciplina->proxDisciplina;
    }
}

int main()
{
    tipoLista lista;
    inicializarLista(&lista);
    tipoDisciplina *disciplina = (tipoDisciplina*)malloc(sizeof(tipoDisciplina));

    int opcMenu;

    do
    {
        menu();
        scanf("%d", &opcMenu);

        if ((&lista)->quant == 0 && opcMenu > 1){
            printf("    Lista sem matérias!\n");
        } else {
            switch (opcMenu)
            {
            case 1:
                criarDisciplina(&lista);
                break;

            case 2:
                disciplina = escolherDisciplina(&lista);
                matricularAluno(&lista, disciplina);
                break;
            
            case 3:
                disciplina = escolherDisciplina(&lista);
                mostrarAlunos(&lista, disciplina);
                break;

            case 4:
                disciplina = escolherDisciplina(&lista);
                removerAluno(&lista, disciplina);
                break;

            case 5:
                mostrarTudo(&lista);
                break;

            default:
                break;
            }
        }

    } while (opcMenu != 0);
    

    return 0;
}
