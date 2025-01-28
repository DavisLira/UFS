#include <iostream>
#include <fstream>

using namespace std;

struct Pacote {
    int numero;         // Número do pacote
    int tamanho;        // Tamanho do pacote
    string* dados;   // Lista para os elementos do pacote
};

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

void lerArquivo(ifstream& arquivoEntrada, Pacote*& pacotes, int& numTotalPacotes, int& numQtdPacotes) {
    // Ler o número de pacotes
    arquivoEntrada >> numTotalPacotes >> numQtdPacotes;

    // Alocar memória para armazenar os pacotes
    pacotes = new Pacote[numTotalPacotes];

    for (int i = 0; i < numTotalPacotes; ++i) {
        // Ler o número do pacote e o tamanho
        arquivoEntrada >> pacotes[i].numero >> pacotes[i].tamanho;

        // Alocar espaço para os dados do pacote
        pacotes[i].dados = new string[pacotes[i].tamanho];

        // Ler os dados do pacote como strings hexadecimais
        for (int j = 0; j < pacotes[i].tamanho; ++j) {
            arquivoEntrada >> pacotes[i].dados[j];
        }
    }
}

// Função para liberar a memória alocada para as listas
void liberarMemoria(Pacote* pacotes, int numTotalPacotes) {
    for (int i = 0; i < numTotalPacotes; ++i) {
        delete[] pacotes[i].dados;
    }
    delete[] pacotes;
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

    Pacote* pacotes = nullptr;
    int numTotalPacotes = 0;
    int numQtdPacotes = 0;

    lerArquivo(arquivoEntrada, pacotes, numTotalPacotes, numQtdPacotes);

    for (int i = 0; i < numTotalPacotes; ++i) {
        arquivoSaida << "Pacote " << pacotes[i].numero << " (Tamanho: " << pacotes[i].tamanho << "): ";
        for (int j = 0; j < pacotes[i].tamanho; ++j) {
            arquivoSaida << pacotes[i].dados[j] << " ";
        }
        arquivoSaida << endl;
    }

    liberarMemoria(pacotes, numTotalPacotes);
    arquivoEntrada.close();
    arquivoSaida.close();
    return 0;
}