// Código que gera uma matriz de 9x9 com valores de 0 a 9, sendo 0 considerado
// espaços vazios, e vai testar na força bruta o resultado do sukoku

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define SIZE 9
#define TERMINAL "clear"

// Variáveis globais para as métricas
int attempts = 0;     // Contador de quantos números foram tentados
int backtracks = 0;   // Contador de quantas vezes houve retrocesso

// Função para mostrar a matriz de Sudoku
void showSudoku(int m[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", m[i][j]);
            if (j == 2 || j == 5) {
                printf("| ");
            }
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("---------------------\n");
        }
    }
}

// Funções de verificação para linha
bool numberInLine(int m[SIZE][SIZE], int line, int num) {
    for (int column = 0; column < SIZE; column++) {
        if (m[line][column] == num) {
            return true;
        }
    }
    return false;
}

// Funções de verificação para coluna
bool numberInColumn(int m[SIZE][SIZE], int column, int num) {
    for (int line = 0; line < SIZE; line++) {
        if (m[line][column] == num) {
            return true;
        }
    }
    return false;
}

// Funções de verificação para subgrade 3x3
bool numberInBox(int m[SIZE][SIZE], int startLine, int startColumn, int num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m[startLine + i][startColumn + j] == num) {
                return true;
            }
        }
    }
    return false;
}

// Verifica se é possível colocar um número em uma posição específica
bool canPutNumber(int m[SIZE][SIZE], int line, int column, int num) {
    return !numberInLine(m, line, num) && 
           !numberInColumn(m, column, num) && 
           !numberInBox(m, line - line % 3, column - column % 3, num);
}

// Função para gerar uma matriz Sudoku inicial com alguns valores fixos
void generateSudoku(int m[SIZE][SIZE], int fixed) {
    srand(time(NULL));

    int count = 0;

    do {
        int line = rand() % SIZE;
        int column = rand() % SIZE;
        int num = (rand() % SIZE) + 1;

        if (m[line][column] == 0 && canPutNumber(m, line, column, num)) {
            m[line][column] = num;
            count++;
        }
    } while (count < fixed);
}

// Função para encontrar a próxima posição vazia na matriz
bool findEmptyPosition(int m[SIZE][SIZE], int *line, int *column) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (m[i][j] == 0) {
                *line = i;
                *column = j;
                return true; // encontrou
            }
        }
    }
    return false; // não há mais posições vazias
}

// Função recursiva de backtracking para resolver o Sudoku com visualização
bool trySudoku(int m[SIZE][SIZE]) {
    int line, column;

    // Se não encontrar uma posição vazia, significa que o Sudoku está resolvido
    if (!findEmptyPosition(m, &line, &column)) {
        return true;
    }

    // Tentar números de 1 a 9 para a posição vazia encontrada
    for (int num = 1; num <= 9; num++) {
        attempts++; // Incrementa o contador de tentativas
        if (canPutNumber(m, line, column, num)) {
            m[line][column] = num; // Coloca o número na posição

            // Exibe a matriz e aguarda um breve momento
            system(TERMINAL); // Limpa a tela para atualização
            showSudoku(m);
            usleep(1); // Pausa para visualização

            // Tenta resolver o restante do Sudoku recursivamente
            if (trySudoku(m)) {
                return true; // Se resolver, retorna verdadeiro
            }

            m[line][column] = 0; // Se falhar, desfaz a tentativa (backtracking)
            backtracks++; // Incrementa o contador de retrocessos

            // Exibe a matriz e aguarda um breve momento ao retroceder
            system(TERMINAL); // Limpa a tela para atualização
            showSudoku(m);
            usleep(1); // Pausa para visualização
        }
    }
    return false; // Se nenhum número funcionar, retorna falso para retroceder
}

int main() {
    int sudoku[SIZE][SIZE] = {0}; // Inicializa a matriz de Sudoku com zeros

    generateSudoku(sudoku, 20); // Gera um Sudoku com 20 números fixos
    system(TERMINAL);
    showSudoku(sudoku);

    printf("Pressione ENTER para começar a resolver...\n");
    getchar();
    setbuf(stdin, NULL);

    // Inicia o cronômetro
    clock_t start = clock();

    if (trySudoku(sudoku)) {
        printf("\nSudoku resolvido:\n");
        showSudoku(sudoku);
    } else {
        printf("\nNão foi possível resolver o Sudoku.\n");
    }

    // Finaliza o cronômetro e calcula a duração
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    // Exibe as métricas finais
    printf("\nEstatísticas:\n");
    printf("Tentativas de números: %d\n", attempts);
    printf("Retrocessos (backtracking): %d\n", backtracks);
    printf("Tempo total de execução: %.2f segundos\n", duration);

    return 0;
}