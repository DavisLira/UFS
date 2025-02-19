#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <chrono> 

using namespace std;
using namespace chrono;

struct Gene {
    string sequencia;
};

struct Doenca {
    string nome;
    int num_gene;
    Gene* genes;
    int prob = 0;
};

// Função para validar e abrir os arquivos
bool abrir_arquivos(const char* entrada, const char* saida, ifstream& input, ofstream& output) {
    // Verificar e abrir o arquivo de entrada
    input.open(entrada);
    if (!input) {
        cerr << "Erro ao abrir o arquivo de entrada: " << entrada << endl;
        return false;
    }

    // Verificar e abrir o arquivo de saída
    output.open(saida);
    if (!output) {
        cerr << "Erro ao criar o arquivo de saída: " << saida << endl;
        return false;
    }

    return true;
}

// Função para ler os dados do arquivo
void ler_arquivo(ifstream& input, string& dna, int& tam_subcadeia, Doenca*& doencas, int& num_doencas) {
    input >> tam_subcadeia;
    input >> dna;
    input >> num_doencas;
    doencas = new Doenca[num_doencas];

    // Lê as doenças
    for (int i = 0; i < num_doencas; i++) {
        input >> doencas[i].nome >> doencas[i].num_gene;
        doencas[i].genes = new Gene[doencas[i].num_gene];
        // Lê os genes
        for (int ii = 0; ii < doencas[i].num_gene; ii++) {
            input >> doencas[i].genes[ii].sequencia;
        }
    }

    input.close();
}

void mostrar_doencas(ofstream& output, Doenca* doencas, int num_doencas) {
    for (int i = 0; i < num_doencas; i++) {
        output << doencas[i].nome << endl;
        for (int ii = 0; ii < doencas[i].num_gene; ii++) {
            output << doencas[i].genes[ii].sequencia << endl;
        }
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
    if (!abrir_arquivos(argv[1], argv[2], input, output)) {
        return 1;
    }

    string dna;
    int tam_subcadeia;
    Doenca* doencas;
    int num_doencas;

    ler_arquivo(input, dna, tam_subcadeia, doencas, num_doencas);

    rabin_karp(dna, tam_subcadeia, doencas, num_doencas);

    mostrar_doencas(output, doencas, num_doencas);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tempo para rodar o código: " << duration.count() << " microsegundos\n";

    return 0;
}
