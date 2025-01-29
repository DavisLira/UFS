#include <iostream>
#include <fstream>

using namespace std;

int totalPacotes = 0;
int qtdPacotes = 0;
int lido = 0;
int atual = 0; // Próximo número de pacote esperado

struct Pacote {
    int numero;         // Número do pacote
    int tamanho;        // Tamanho do pacote
    string* dados;      // Lista para os elementos do pacote
};

bool abrirArquivos(const char* entrada, const char* saida, ifstream& arquivoEntrada, ofstream& arquivoSaida) {
    arquivoEntrada.open(entrada);
    if (!arquivoEntrada) {
        cerr << "Erro ao abrir o arquivo de entrada: " << entrada << endl;
        return false;
    }

    arquivoSaida.open(saida);
    if (!arquivoSaida) {
        cerr << "Erro ao criar o arquivo de saída: " << saida << endl;
        return false;
    }

    return true;
}

void lerArquivo(ifstream& arquivoEntrada, Pacote*& pacotes) {
    arquivoEntrada >> totalPacotes >> qtdPacotes;

    pacotes = new Pacote[totalPacotes];

    for (int i = 0; i < totalPacotes; ++i) {
        arquivoEntrada >> pacotes[i].numero >> pacotes[i].tamanho;

        pacotes[i].dados = new string[pacotes[i].tamanho];
        for (int j = 0; j < pacotes[i].tamanho; ++j) {
            arquivoEntrada >> pacotes[i].dados[j];
        }
    }
}

void liberarMemoria(Pacote* pacotes) {
    for (int i = 0; i < totalPacotes; ++i) {
        delete[] pacotes[i].dados;
    }
    delete[] pacotes;
}

void heapify(Pacote* pacotes, int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && pacotes[esquerda].numero > pacotes[maior].numero)
        maior = esquerda;

    if (direita < n && pacotes[direita].numero > pacotes[maior].numero)
        maior = direita;

    if (maior != i) {
        swap(pacotes[i], pacotes[maior]);
        heapify(pacotes, n, maior);
    }
}

void heapSort(Pacote* pacotes, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(pacotes, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(pacotes[0], pacotes[i]);
        heapify(pacotes, i, 0);
    }
}

void selecionarPacotes(Pacote* pcts, Pacote* pctAguardo) {
    for (int i = 0; i < qtdPacotes && lido < totalPacotes; i++, lido++) {
        pctAguardo[lido] = pcts[lido];
    }
}

void mostrarPacotes(Pacote* pacotes, int n, int& atual, ofstream& arquivoSaida) {
    while (true) {
        bool encontrouPacote = false; // Para rastrear se encontramos pacotes na sequência atual
        string linhaDados;            // Armazena os dados da linha atual
        bool primeiraParte = true;    // Para controlar a separação dos pacotes

        for (int i = atual; i < n; i++) {
            if (pacotes[i].numero == atual) {
                // Adiciona a barra de separação no início da linha
                if (!primeiraParte) {
                    linhaDados += "|";
                }
                // Adiciona os dados do pacote à string da linha, separados por vírgula
                for (int j = 0; j < pacotes[i].tamanho; j++) {
                    linhaDados += pacotes[i].dados[j];
                    if (j < pacotes[i].tamanho - 1) {
                        linhaDados += ",";
                    }
                }
                primeiraParte = false;  // Marca que não é mais o primeiro pacote
                atual++;                // Incrementa o próximo número esperado
                encontrouPacote = true; // Marcamos que encontramos um pacote na sequência atual
            }
        }

        if (encontrouPacote) {
            // Escreve a linha no arquivo de saída
            arquivoSaida << "|" << linhaDados << "|" << endl;
            linhaDados.clear(); // Limpa a string para a próxima linha
        } else {
            break; // Sai do loop se não houver mais pacotes na sequência
        }
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

    Pacote* pacotes = nullptr;
    Pacote* pacotesAguardo = nullptr;

    lerArquivo(arquivoEntrada, pacotes);
    pacotesAguardo = new Pacote[totalPacotes];

    while (lido < totalPacotes) {
        selecionarPacotes(pacotes, pacotesAguardo);

        heapSort(pacotesAguardo, lido); // Ordena os pacotes já lidos

        mostrarPacotes(pacotesAguardo, lido, atual, arquivoSaida); // Mostra pacotes em ordem
    }

    liberarMemoria(pacotes);
    delete[] pacotesAguardo;

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}
