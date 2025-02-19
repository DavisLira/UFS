#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

struct Gene {
    string sequencia;
};

struct Doenca {
    string nome;
    int num_genes;
    Gene* genes;
    int prob;    // Porcentagem inteira de genes detectados
};

bool abrir_arquivos(const char* entrada, const char* saida, ifstream &input, ofstream &output) {
    input.open(entrada);
    if (!input) {
        cerr << "Erro ao abrir o arquivo de entrada: " << entrada << endl;
        return false;
    }

    output.open(saida);
    if (!output) {
        cerr << "Erro ao criar o arquivo de saída: " << saida << endl;
        return false;
    }

    return true;
}

void ler_arquivo(ifstream &input, string &dna, int &tam_subcadeia, Doenca *&doencas, int &num_doencas) {
    input >> tam_subcadeia;
    input >> dna;
    input >> num_doencas;
    doencas = new Doenca[num_doencas];

    for (int i = 0; i < num_doencas; i++) {
        input >> doencas[i].nome >> doencas[i].num_genes;
        doencas[i].genes = new Gene[doencas[i].num_genes];
        for (int j = 0; j < doencas[i].num_genes; j++) {
            input >> doencas[i].genes[j].sequencia;
        }
    }
    input.close();
}


4 void calcular_tabela(int32_t* k, char* P) {
5 // i = sufixo, j = prefixo
6 for(int32_t i = 1, j = -1; i < strlen(P); i++) {
7 // Prefixo e sufixo diferentes
8 while(j >= 0 && P[j + 1] != P[i])
9 // Retorno de estado
10 j = k[j];
11 // Combinação de prefixo e sufixo
12 if(P[j + 1] == P[i])
13 // Avanço de estado
14 j++;
15 // Atualização da transição do estado
16 k[i] = j;
17 }
18 }


int contar_genes_detectados(string dna, Gene gene, int tam_subcadeia) {
    int num_genes_detectados = 0;
}

void calcular_probabilidade(string dna, Doenca *doencas, int num_doencas, int tam_subcadeia) {
    int num_genes_detectados = 0;
    for (int i = 0; i < num_doencas; i++) {
        for (int j = 0; j < doencas[i].num_genes; j++) {
            num_genes_detectados += contar_genes_detectados(dna, doencas[i].genes[j], tam_subcadeia);
        }
    }
}

void mostrar_doencas(ofstream &output, Doenca *doencas, int num_doencas) {
    for (int i = 0; i < num_doencas; i++) {
        output << doencas[i].nome << "->" << doencas[i].prob << "%" << endl;
    }
}

// Função para mesclar duas sublistas
void merge(Doenca *doencas, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Doenca *leftArray = new Doenca[n1];
    Doenca *rightArray = new Doenca[n2];

    // Copia os dados para as sublistas temporárias
    for (int i = 0; i < n1; i++) {
        leftArray[i] = doencas[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = doencas[mid + 1 + j];
    }

    // Mescla as sublistas de volta para o vetor original
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].prob >= rightArray[j].prob) { // Ordenação decrescente por probabilidade
            doencas[k] = leftArray[i];
            i++;
        } else {
            doencas[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de leftArray, se houver
    while (i < n1) {
        doencas[k] = leftArray[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de rightArray, se houver
    while (j < n2) {
        doencas[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

// Função de ordenação mergeSort
void mergeSort(Doenca *doencas, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calcula o ponto médio

        mergeSort(doencas, left, mid);  // Ordena a primeira metade
        mergeSort(doencas, mid + 1, right); // Ordena a segunda metade

        merge(doencas, left, mid, right);  // Mescla as duas metades ordenadas
    }
}


int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }
    ifstream input;
    ofstream output;
    if (!abrir_arquivos(argv[1], argv[2], input, output))
        return 1;
    
    string dna;
    int tam_subcadeia;
    Doenca *doencas;
    int num_doencas;
    ler_arquivo(input, dna, tam_subcadeia, doencas, num_doencas);
    
    calcular_probabilidade(dna, doencas, num_doencas, tam_subcadeia); // Calcular a probabilidade de cada doença
    mergeSort(doencas, 0, num_doencas - 1); // Ordena as doenças com o mergeSort
    mostrar_doencas(output, doencas, num_doencas);
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tempo para rodar o código: " << duration.count() << " microsegundos\n";
    
    // Libera memória
    for (int i = 0; i < num_doencas; i++) {
        delete[] doencas[i].genes;
    }
    delete[] doencas;
    
    return 0;
}
