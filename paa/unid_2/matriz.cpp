#include <iostream>
#include <chrono>  // Para cronometrar o tempo

using namespace std;
using namespace chrono;

int main() {
    // Definindo uma matriz 3D com dimensões 2x3x4
    int matriz[8][8][12] = {
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        },
        {
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8},
            {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4},
            {5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8}
        }
    };

    int dimensao1 = 8; // número de "blocos" (camadas)
    int dimensao2 = 8; // número de linhas
    int dimensao3 = 12; // número de colunas

    // Cronometrando o tempo para 3 for aninhados
    auto start = high_resolution_clock::now();

    // Varrendo a matriz 3D com 3 laços for aninhados
    for (int i = 0; i < dimensao1; i++) {
        for (int j = 0; j < dimensao2; j++) {
            for (int k = 0; k < dimensao3; k++) {
                // Acessando o elemento
                // No caso, só imprimimos para mostrar que estamos acessando os elementos
                cout << "Elemento [" << i << "][" << j << "][" << k << "] = " 
                     << matriz[i][j][k] << endl;
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tempo com 3 for aninhados: " << duration.count() << " microsegundos\n";

    // Cronometrando o tempo para 1 for com cálculos manuais de índice
    start = high_resolution_clock::now();

    // Varrendo a matriz 3D com 1 laço for e cálculos manuais
    for (int i = 0; i < dimensao1 * dimensao2 * dimensao3; i++) {
        int x = i / (dimensao2 * dimensao3);        // Calcula o índice da primeira dimensão
        int y = (i % (dimensao2 * dimensao3)) / dimensao3;  // Calcula o índice da segunda dimensão
        int z = i % dimensao3;                     // Calcula o índice da terceira dimensão

        // Acessando o elemento
        // Também apenas imprimimos para mostrar o acesso
        cout << "Elemento [" << x << "][" << y << "][" << z << "] = " 
             << matriz[x][y][z] << endl;
    }

    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Tempo com 1 for e cálculos manuais: " << duration.count() << " microsegundos\n";

    return 0;
}
