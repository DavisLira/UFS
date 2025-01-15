#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Container {
    int ordem;
    string numero;
    string cnpjCadastrado;
    string cnpjSelecionado;
    int pesoCadastrado = 0;
    int pesoSelecionado = 0;
    bool divergenciaCnpj = false;
    bool divergenciaPeso = false;

};

void lerArquivo(ifstream& arquivo, Container*& cadastrados, int& numC, Container*& selecionados, int& numS) {
    arquivo >> numC;
    cadastrados = new Container[numC];
    for (int i = 0; i < numC; ++i) {
        cadastrados[i].ordem = i;
        arquivo >> cadastrados[i].numero >> cadastrados[i].cnpjCadastrado >> cadastrados[i].pesoCadastrado;
    }

    arquivo >> numS;
    selecionados = new Container[numS];
    for (int i = 0; i < numS; ++i) {
        selecionados[i].ordem = i;
        arquivo >> selecionados[i].numero >> selecionados[i].cnpjSelecionado >> selecionados[i].pesoSelecionado;
    }
}

void filtrarIrregulares(Container* cadastrados, int numC, Container* selecionados, int numS, Container*& irregulares, int& numI) {
    // Inicializar o array de irregulares com o mesmo tamanho de selecionados
    irregulares = new Container[numS];

    // Loop para verificar os cadastrados e selecionados
    for (int i = 0; i < numC; ++i) {
        // Flag para garantir que um container seja adicionado apenas uma vez
        bool adicionado = false;

        Container atual = selecionados[j];
        if (cadastrados[i].numero == selecionados[j].numero) {

            // Verificar divergência de CNPJ
            if (cadastrados[i].cnpjCadastrado != selecionados[j].cnpjSelecionado) {
                selecionados[j].cnpjCadastrado = cadastrados[i].cnpjCadastrado;
                selecionados[j].divergenciaCnpj = true;
                // Adiciona à lista de irregulares apenas se ainda não foi adicionado
                if (!adicionado) {
                    irregulares[numI++] = selecionados[j]; // Adiciona à lista de irregulares
                    adicionado = true;  // Marca como adicionado
                }
            }

            // Verificar divergência de peso
            if (abs(cadastrados[i].pesoCadastrado - selecionados[j].pesoSelecionado) > cadastrados[i].pesoCadastrado * 0.1) {
                selecionados[j].pesoCadastrado = cadastrados[i].pesoCadastrado;
                selecionados[j].divergenciaPeso = true;
                // Adiciona à lista de irregulares apenas se ainda não foi adicionado
                if (!adicionado) {
                    irregulares[numI++] = selecionados[j]; // Adiciona à lista de irregulares
                    adicionado = true;  // Marca como adicionado
                }
            }

            break; // Já achou o item correspondente, pode sair do loop
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
            if (esquerda[i].divergenciaPeso) {
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

int main() {
    ifstream arquivo("porto.input");
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    Container* cadastrados = nullptr;
    Container* selecionados = nullptr;
    Container* irregulares = nullptr;
    int numC = 0, numS = 0, numI = 0;

    // Ler dados do arquivo
    lerArquivo(arquivo, cadastrados, numC, selecionados, numS);
    arquivo.close();

    // Ordenar a lista de selecionados e identificar divergências
    filtrarIrregulares(cadastrados, numC, selecionados, numS, irregulares, numI);

    mergeSort(irregulares, 0, numI - 1);

    // Exibir os resultados de divergências
    for (int i = 0; i < numI; ++i) {
        if (irregulares[i].divergenciaCnpj) {
            cout << irregulares[i].numero << ":" << irregulares[i].cnpjCadastrado << "<->" << irregulares[i].cnpjSelecionado << endl;
        }
        if (irregulares[i].divergenciaPeso) {
            cout << irregulares[i].numero << ":" << abs(irregulares[i].pesoSelecionado - irregulares[i].pesoCadastrado) << "kg (" 
                 << round(abs(irregulares[i].pesoSelecionado - irregulares[i].pesoCadastrado) * 100.0 / irregulares[i].pesoCadastrado) << "%)" << endl;
        }
    }

    // Liberar memória alocada
    delete[] cadastrados;
    delete[] selecionados;
    delete[] irregulares;

    return 0;
}
