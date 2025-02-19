#include <iostream>
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
    int prob;
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

void mostrar_encontros(int* lista_encontros, int count) {
    for (int i = 0; i < count; i++) {
        cout << lista_encontros[i] << " ";
    }
}

void calcular_tabela(int* tabela_transicao, const string& gene) {
    int tamanho_gene = gene.size();
    tabela_transicao[0] = -1;
    
    for (int i = 1, j = -1; i < tamanho_gene; i++) {
        while (j >= 0 && gene[j + 1] != gene[i]) 
            j = tabela_transicao[j];
        if (gene[j + 1] == gene[i]) 
            j++;
        tabela_transicao[i] = j;
    }
}

int KMP(int* tabela_transicao, int* lista_encontros, string dna, const string& gene) {
    int tamanho_dna = dna.size(), tamanho_gene = gene.size(), count = 0;
    calcular_tabela(tabela_transicao, gene);
    for (int i = 0, j = -1; i < tamanho_dna; i++) {
        while (j >= 0 && gene[j + 1] != dna[i]) 
            j = tabela_transicao[j];
        if (gene[j + 1] == dna[i]) 
            j++;
        if (j == tamanho_gene - 1) { 
            lista_encontros[count++] = i - tamanho_gene + 1;
            j = tabela_transicao[j];
        }
    }
    mostrar_encontros(lista_encontros, count);
    cout << " - "<< count << endl;
    return count;
}

int contar_genes_detectados(string dna, string gene, int tam_subcadeia) {
    int tamanho_gene = gene.size();
    int* tabela_transicao = new int[tamanho_gene]; 
    int* lista_encontros = new int[dna.size()];

    int num_genes_detectados = KMP(tabela_transicao, lista_encontros, dna, gene);
    
    delete[] tabela_transicao;
    delete[] lista_encontros;
    
    return num_genes_detectados;
}

void calcular_probabilidade(string dna, Doenca *doencas, int num_doencas, int tam_subcadeia) {
    for (int i = 0; i < num_doencas; i++) {
        cout << "Calculando i = " << i << ": " << doencas[i].nome << endl;
        int num_genes_detectados = 0;
        for (int j = 0; j < doencas[i].num_genes; j++) {
            cout << "Lendo gene j = " << j << ": " << doencas[i].genes[j].sequencia << endl;
            num_genes_detectados += contar_genes_detectados(dna, doencas[i].genes[j].sequencia, tam_subcadeia);
        }
        doencas[i].prob = (num_genes_detectados * 100) / doencas[i].num_genes;
    }
}

void mostrar_doencas(ofstream &output, Doenca *doencas, int num_doencas) {
    for (int i = 0; i < num_doencas; i++) {
        output << doencas[i].nome << "->" << doencas[i].prob << "%" << endl;
    }
}

void merge(Doenca *doencas, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Doenca *leftArray = new Doenca[n1];
    Doenca *rightArray = new Doenca[n2];

    for (int i = 0; i < n1; i++) leftArray[i] = doencas[left + i];
    for (int j = 0; j < n2; j++) rightArray[j] = doencas[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].prob >= rightArray[j].prob) 
            doencas[k++] = leftArray[i++];
        else 
            doencas[k++] = rightArray[j++];
    }

    while (i < n1) doencas[k++] = leftArray[i++];
    while (j < n2) doencas[k++] = rightArray[j++];

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(Doenca *doencas, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(doencas, left, mid);
        mergeSort(doencas, mid + 1, right);
        merge(doencas, left, mid, right);
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
    
    output.close();
    for (int i = 0; i < num_doencas; i++) delete[] doencas[i].genes;
    delete[] doencas;
    
    return 0;
}
