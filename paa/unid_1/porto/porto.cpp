#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Container {
    int ordem;
    string codigo;
    string cnpjCadastrado;
    string cnpjSelecionado;
    int pesoCadastrado = 0;
    int pesoSelecionado = 0;
    bool divergenciaCnpj = false;
    bool divergenciaPeso = false;
    int percentualPeso = 0;
};

void lerArquivo(ifstream& arquivo, Container*& cadastrados, int& numC, Container*& selecionados, int& numS) {
    arquivo >> numC;
    cadastrados = new Container[numC];
    for (int i = 0; i < numC; ++i) {
        cadastrados[i].ordem = i;
        arquivo >> cadastrados[i].codigo >> cadastrados[i].cnpjCadastrado >> cadastrados[i].pesoCadastrado;
    }

    arquivo >> numS;
    selecionados = new Container[numS];
    for (int i = 0; i < numS; ++i) {
        arquivo >> selecionados[i].codigo >> selecionados[i].cnpjSelecionado >> selecionados[i].pesoSelecionado;
    }
}

void mergeAlfabetica(Container* entrada, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Container* esquerda = new Container[n1];
    Container* direita = new Container[n2];

    for (int i = 0; i < n1; ++i) esquerda[i] = entrada[inicio + i];
    for (int i = 0; i < n2; ++i) direita[i] = entrada[meio + 1 + i];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (esquerda[i].codigo <= direita[j].codigo) {
            entrada[k++] = esquerda[i++];
        } else {
            entrada[k++] = direita[j++];
        }
    }

    while (i < n1) {
        entrada[k++] = esquerda[i++];
    }

    while (j < n2) {
        entrada[k++] = direita[j++];
    }

    delete[] esquerda;
    delete[] direita;
}

void mergeSortAlfabetica(Container* entrada, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSortAlfabetica(entrada, inicio, meio);
        mergeSortAlfabetica(entrada, meio + 1, fim);
        mergeAlfabetica(entrada, inicio, meio, fim);
    }
}

int buscaBinaria(Container* lista, int esq, int dir, const string& codigo) {
    while (esq <= dir) {
        int mid = esq + (dir - esq) / 2;

        if (lista[mid].codigo == codigo) {
            return mid;
        }

        if (lista[mid].codigo > codigo) {
            dir = mid - 1;
        }

        else {
            esq = mid + 1;
        }
    }
    
    return -1;
}

void filtrarIrregulares(Container* cadastrados, int numC, Container* selecionados, int numS, Container*& irregulares, int& numI) {
    // Inicializar o array de irregulares com o mesmo tamanho de selecionados
    irregulares = new Container[numS];

    // Loop para verificar os cadastrados e selecionados
    for (int c = 0; c < numC; ++c) {
        int s = buscaBinaria(selecionados, 0, numS - 1, cadastrados[c].codigo);

        if (s == -1) {
            continue;
        } else if (cadastrados[c].codigo == selecionados[s].codigo) {
            int diferencaPeso = abs(cadastrados[c].pesoCadastrado - selecionados[s].pesoSelecionado);
            int diferencaPercentual = round(diferencaPeso * 100.0 / cadastrados[c].pesoCadastrado);

            // Verificar divergência de CNPJ
            if (cadastrados[c].cnpjCadastrado != selecionados[s].cnpjSelecionado) {
                selecionados[s].cnpjCadastrado = cadastrados[c].cnpjCadastrado;
                selecionados[s].divergenciaCnpj = true;
                irregulares[numI++] = selecionados[s];
            } else if (diferencaPercentual > 10) {
                selecionados[s].percentualPeso = diferencaPercentual;
                selecionados[s].pesoCadastrado = cadastrados[c].pesoCadastrado;
                selecionados[s].divergenciaPeso = true;
                irregulares[numI++] = selecionados[s];
            }
        }
    }
}

void merge(Container* entrada, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Criar arrays temporários para armazenar as metades
    Container* esquerda = new Container[n1];
    Container* direita = new Container[n2];

    // Copiar os dados para as metades temporárias
    for (int i = 0; i < n1; ++i) {
        esquerda[i] = entrada[inicio + i];
    }
    for (int i = 0; i < n2; ++i) {
        direita[i] = entrada[meio + 1 + i];
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (esquerda[i].divergenciaCnpj) {
            entrada[k++] = esquerda[i++];
        } else if (direita[j].divergenciaCnpj) {
            entrada[k++] = direita[j++];
        } else {
            if (esquerda[i].divergenciaPeso && direita[j].divergenciaPeso) {
                if (esquerda[i].percentualPeso >= direita[j].percentualPeso) {
                    entrada[k++] = esquerda[i++];
                } else {
                    entrada[k++] = direita[j++];
                }
            } else if (esquerda[i].divergenciaPeso) {
                entrada[k++] = esquerda[i++];

            } else {
                entrada[k++] = direita[j++];
            }
        }
    }

    // Copiar os elementos restantes da esquerda, se houver
    while (i < n1) {
        entrada[k++] = esquerda[i++];
    }

    // Copiar os elementos restantes da direita, se houver
    while (j < n2) {
        entrada[k++] = direita[j++];
    }

    // Liberar memória
    delete[] esquerda;
    delete[] direita;
}

void mergeSort(Container* entrada, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(entrada, inicio, meio);
        mergeSort(entrada, meio + 1, fim);
        merge(entrada, inicio, meio, fim);
    }
}

int main(int argc, char* argv[]) {
    // Verificar se os argumentos foram fornecidos
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }
    // Abrir o arquivo de entrada
    ifstream arquivoEntrada(argv[1]);
    if (!arquivoEntrada) {
        cerr << "Erro ao abrir o arquivo de entrada: " << argv[1] << endl;
        return 1;
    }
    // Abrir o arquivo de saída
    ofstream arquivoSaida(argv[2]);
    if (!arquivoSaida) {
        cerr << "Erro ao criar o arquivo de saída: " << argv[2] << endl;
        return 1;
    }

    cout << "Inicio" << endl;

    Container* cadastrados = nullptr;
    Container* selecionados = nullptr;
    Container* irregulares = nullptr;
    int numC = 0, numS = 0, numI = 0;

    // Ler dados do arquivo de entrada
    lerArquivo(arquivoEntrada, cadastrados, numC, selecionados, numS);
    arquivoEntrada.close();

    Container* selecionadosAlf = new Container[numS];
    for (int i = 0; i < numS; ++i) {
        selecionadosAlf[i] = selecionados[i];
    }

    // Ordenar a lista de cadastrados
    mergeSortAlfabetica(selecionadosAlf, 0, numS - 1);

    // Ordenar a lista de selecionados e identificar divergências
    filtrarIrregulares(cadastrados, numC, selecionadosAlf, numS, irregulares, numI);

    // Ordenar a lista de irregulares
    mergeSort(irregulares, 0, numI - 1);

    // Escrever os resultados de divergências no arquivo de saída
    for (int i = 0; i < numI; ++i) {
        if (irregulares[i].divergenciaCnpj) {
            arquivoSaida << irregulares[i].codigo << ":" << irregulares[i].cnpjCadastrado << "<->" << irregulares[i].cnpjSelecionado << endl;
        }
        if (irregulares[i].divergenciaPeso) {
            arquivoSaida << irregulares[i].codigo << ":" << abs(irregulares[i].pesoSelecionado - irregulares[i].pesoCadastrado) << "kg("
                         << irregulares[i].percentualPeso << "%)" << endl;
        }
    }

    // Liberar memória alocada
    delete[] cadastrados;
    delete[] selecionados;
    delete[] irregulares;

    // Fechar o arquivo de saída
    arquivoSaida.close();

    cout << "Fim" << endl;

    return 0;
}
