#include <iostream>
#include <fstream>

using namespace std;

// Definição da struct Lista
struct Lista {
    int tamanho;        // Tamanho da lista
    int* elementosLP;   // lista para Lomuto padrao
    int* elementosLM;   // lista para Lomuto mediana de 3
    int* elementosLA;   // lista para Lomuto aleatorio
    int* elementosHP;   // lista para Hoare padrão
    int* elementosHM;   // lista para Hoare mediana de 3
    int* elementosHA;   // lista para Hoare aleatorio
    int lp = 0;         // Contador para Lomuto Padrão
    int lm = 0;         // Contador para Lomuto por mediana de 3
    int la = 0;         // Contador para Lomuto por pivô aleatorio
    int hp = 0;         // Contador para Hoare Padrão
    int hm = 0;         // Contador para Hoare por mediana de 3
    int ha = 0;         // Contador para Hoare por pivô aleatorio
};

enum Modo {
    LP = 1,
    LM = 2,
    LA = 3,
    HP = 4,
    HM = 5,
    HA = 6
};

// Função para validar e abrir os arquivos
bool abrirArquivos(const char* entrada, const char* saida, ifstream& arquivoEntrada, ofstream& arquivoSaida) {
    // Verificar e abrir o arquivo de entrada
    arquivoEntrada.open(entrada);
    if (!arquivoEntrada) {
        cerr << "Erro ao abrir o arquivo de entrada: " << entrada << endl;
        return false;
    }

    // Verificar e abrir o arquivo de saída
    arquivoSaida.open(saida);
    if (!arquivoSaida) {
        cerr << "Erro ao criar o arquivo de saída: " << saida << endl;
        return false;
    }

    return true;
}

// Função para ler os dados do arquivo e preencher as listas
void lerArquivo(ifstream& arquivoEntrada, Lista*& listas, int& numListas) {
    arquivoEntrada >> numListas;

    listas = new Lista[numListas];

    int valor = 0;

    for (int i = 0; i < numListas; ++i) {
        arquivoEntrada >> listas[i].tamanho;
        listas[i].elementosLP = new int[listas[i].tamanho];
        listas[i].elementosLM = new int[listas[i].tamanho];
        listas[i].elementosLA = new int[listas[i].tamanho];
        listas[i].elementosHP = new int[listas[i].tamanho];
        listas[i].elementosHM = new int[listas[i].tamanho];
        listas[i].elementosHA = new int[listas[i].tamanho];

        for (int j = 0; j < listas[i].tamanho; ++j) {
            arquivoEntrada >> valor;
            listas[i].elementosLP[j] = valor; // Copiando
            listas[i].elementosLM[j] = valor;
            listas[i].elementosLA[j] = valor;
            listas[i].elementosHP[j] = valor;
            listas[i].elementosHM[j] = valor;
            listas[i].elementosHA[j] = valor;
        }
    }
}

// Função para liberar a memória alocada para as listas
void liberarMemoria(Lista* listas, int numListas) {
    for (int i = 0; i < numListas; ++i) {
        delete[] listas[i].elementosLP;
        delete[] listas[i].elementosLM;
        delete[] listas[i].elementosLA;
        delete[] listas[i].elementosHP;
        delete[] listas[i].elementosHM;
        delete[] listas[i].elementosHA;
    }
    delete[] listas;
}

// Trocar valores (auxiliar)
void trocar(int& a, int& b, Lista& lista, int modo) {
    int temp = a;
    a = b;
    b = temp;
    
    if (modo == LP) lista.lp++;
    else if (modo == LM) lista.lm++;
    else if (modo == LA) lista.la++;
    else if (modo == HP) lista.hp++;
    else if (modo == HM) lista.hm++;
    else if (modo == HA) lista.ha++;
}

int medianaDeTres(int* elementos, int inicio, int fim) {
    int n = fim - inicio + 1;

    // Índices dos três valores
    int idx1 = inicio + n / 4;
    int idx2 = inicio + n / 2;
    int idx3 = inicio + (3 * n) / 4;

    // Valores correspondentes
    int v1 = elementos[idx1];
    int v2 = elementos[idx2];
    int v3 = elementos[idx3];

    // Determinar a mediana sem alterar a lista
    if ((v1 > v2) != (v1 > v3)) return idx1; // 'v1' é a mediana
    else if ((v2 > v1) != (v2 > v3)) return idx2; // 'v2' é a mediana
    else return idx3; // 'v3' é a mediana
}

// Particionamento usando o esquema Lomuto
int lomuto(int* elementos, int inicio, int fim, Lista& lista, int modo) {
    int pivoIndex;

    if (modo == LM) {
        // Escolher o pivô usando a mediana de 3
        pivoIndex = medianaDeTres(elementos, inicio, fim);
        // Mover a mediana para a posição final
        trocar(elementos[pivoIndex], elementos[fim], lista, modo);
    } else if (modo == LA) {
        // Calcular índice do pivô aleatório
        int n = fim - inicio + 1;
        pivoIndex = inicio + abs(elementos[inicio]) % n;

        // Trocar pivô calculado com o último elemento
        trocar(elementos[pivoIndex], elementos[fim], lista, modo);
    }

    int pivo = elementos[fim];
    int x = inicio - 1;

    for (int y = inicio; y < fim; y++) {
        if (elementos[y] <= pivo) {
            trocar(elementos[++x], elementos[y], lista, modo);
        }
    }
    trocar(elementos[++x], elementos[fim], lista, modo);

    return x;
}

// Quicksort Lomuto
void quicksortL(int* elementos, int inicio, int fim, Lista& lista, int modo) {
    if (modo == LP) lista.lp++;
    else if (modo == LM) lista.lm++;
    else if (modo == LA) lista.la++;

    if (inicio < fim) {
        int pivo = lomuto(elementos, inicio, fim, lista, modo);
        quicksortL(elementos, inicio, pivo - 1, lista, modo);
        quicksortL(elementos, pivo + 1, fim, lista, modo);
    }
}

// Particionamento usando o esquema Hoare
int hoare(int* elementos, int inicio, int fim, Lista& lista, int modo) {
    int pivoIndex;

    if (modo == HM) {
        // Escolher o pivô usando a mediana de 3
        pivoIndex = medianaDeTres(elementos, inicio, fim);
        // Mover a mediana para a posição final
        trocar(elementos[pivoIndex], elementos[inicio], lista, modo);
    } else if (modo == HA) {
        // Calcular índice do pivô aleatório
        int n = fim - inicio + 1;
        pivoIndex = inicio + abs(elementos[inicio]) % n;

        // Trocar pivô calculado com o último elemento
        trocar(elementos[pivoIndex], elementos[inicio], lista, modo);
    }

    int pivo = elementos[inicio];
    int x = inicio - 1;
    int y = fim + 1;

    while(1) {
        while(elementos[--y] > pivo);
        while(elementos[++x] < pivo);
        if (x < y) trocar(elementos[x], elementos[y], lista, modo);
        else return y;
    }
}

// Quicksort Hoare
void quicksortH(int* elementos, int inicio, int fim, Lista& lista, int modo) {
    if (modo == HP) lista.hp++;
    else if (modo == HM) lista.hm++;
    else if (modo == HA) lista.ha++;

    if (inicio < fim) {
        int pivo = hoare(elementos, inicio, fim, lista, modo);
        quicksortH(elementos, inicio, pivo, lista, modo);
        quicksortH(elementos, pivo + 1, fim, lista, modo);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }
    ifstream arquivoEntrada;
    ofstream arquivoSaida;
    if (!abrirArquivos(argv[1], argv[2], arquivoEntrada, arquivoSaida)) {
        return 1;
    }

    Lista* listas = nullptr;
    int numListas = 0;

    lerArquivo(arquivoEntrada, listas, numListas);

    // Ordenar cada lista usando quicksort Lomuto
    for (int i = 0; i < numListas; ++i) {
        quicksortL(listas[i].elementosLP, 0, listas[i].tamanho - 1, listas[i], LP);
    }

    for (int i = 0; i < numListas; ++i) {
        quicksortL(listas[i].elementosLM, 0, listas[i].tamanho - 1, listas[i], LM);
    }

    for (int i = 0; i < numListas; ++i) {
        quicksortL(listas[i].elementosLA, 0, listas[i].tamanho - 1, listas[i], LA);
    }

    for (int i = 0; i < numListas; ++i) {
        quicksortH(listas[i].elementosHP, 0, listas[i].tamanho - 1, listas[i], HP);
    }

    for (int i = 0; i < numListas; ++i) {
        quicksortH(listas[i].elementosHM, 0, listas[i].tamanho - 1, listas[i], HM);
    }

    for (int i = 0; i < numListas; ++i) {
        quicksortH(listas[i].elementosHA, 0, listas[i].tamanho - 1, listas[i], HA);
    }

    for (int i = 0; i < numListas; ++i) {
        arquivoSaida << "Lista " << i + 1 << ": N(" << listas[i].tamanho 
                     << "), LP(" << listas[i].lp
                     << "), LM(" << listas[i].lm
                     << "), LA(" << listas[i].la
                     << "), HP(" << listas[i].hp
                     << "), HM(" << listas[i].hm
                     << "), HA(" << listas[i].ha << ")" << endl;
    }
    
    liberarMemoria(listas, numListas);

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}
