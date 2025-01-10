#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

struct Container {
    std::string numero;
    std::string cnpjCadastrado;
    std::string cnpjSelecionado;
    int pesoCadastrado;
    int pesoSelecionado;
    int pesoIrregularidade = 0; // Percentual de diferença do peso
    bool irregularidadeCNPJ = false;
    int ordemCadastro = 0; // Índice baseado na ordem de cadastro

    void imprimir() const {
        if (irregularidadeCNPJ) {
            std::cout << numero << ":" << cnpjCadastrado << "<->" << cnpjSelecionado << "\n";
        } else {
            std::cout << numero << ":" << std::abs(pesoSelecionado - pesoCadastrado)
                      << "kg (" << pesoIrregularidade << "%)\n";
        }
    }
};

void merge(Container arr[], int left, int mid, int right, bool byPeso) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Container* L = new Container[n1];
    Container* R = new Container[n2];

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool condition = byPeso
            ? (L[i].pesoIrregularidade > R[j].pesoIrregularidade ||
               (L[i].pesoIrregularidade == R[j].pesoIrregularidade && L[i].ordemCadastro < R[j].ordemCadastro))
            : (L[i].ordemCadastro < R[j].ordemCadastro);

        if (condition) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Container arr[], int left, int right, bool byPeso) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, byPeso);
        mergeSort(arr, mid + 1, right, byPeso);
        merge(arr, left, mid, right, byPeso);
    }
}

int main() {
    std::ifstream arquivo("porto.input");
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    int numCadastrados, numSelecionados;
    Container cadastrados[100], irregularidadeCNPJ[100], irregularidadePeso[100];
    int qtdIrregularidadeCNPJ = 0, qtdIrregularidadePeso = 0;

    // Lê os containers cadastrados
    arquivo >> numCadastrados;
    for (int i = 0; i < numCadastrados; ++i) {
        arquivo >> cadastrados[i].numero >> cadastrados[i].cnpjCadastrado >> cadastrados[i].pesoCadastrado;
        cadastrados[i].ordemCadastro = i;
    }

    // Lê os containers selecionados e detecta irregularidades
    arquivo >> numSelecionados;
    for (int i = 0; i < numSelecionados; ++i) {
        Container selecionado;
        arquivo >> selecionado.numero >> selecionado.cnpjSelecionado >> selecionado.pesoSelecionado;

        for (int j = 0; j < numCadastrados; ++j) {
            if (cadastrados[j].numero == selecionado.numero) {
                if (cadastrados[j].cnpjCadastrado != selecionado.cnpjSelecionado) {
                    irregularidadeCNPJ[qtdIrregularidadeCNPJ] = cadastrados[j];
                    irregularidadeCNPJ[qtdIrregularidadeCNPJ].cnpjSelecionado = selecionado.cnpjSelecionado;
                    irregularidadeCNPJ[qtdIrregularidadeCNPJ].irregularidadeCNPJ = true;
                    ++qtdIrregularidadeCNPJ;
                } else if (std::abs(cadastrados[j].pesoCadastrado - selecionado.pesoSelecionado) > cadastrados[j].pesoCadastrado * 0.1) {
                    irregularidadePeso[qtdIrregularidadePeso] = cadastrados[j];
                    irregularidadePeso[qtdIrregularidadePeso].pesoSelecionado = selecionado.pesoSelecionado;
                    irregularidadePeso[qtdIrregularidadePeso].pesoIrregularidade = std::round(std::abs(cadastrados[j].pesoCadastrado - selecionado.pesoSelecionado) * 100.0 / cadastrados[j].pesoCadastrado);
                    ++qtdIrregularidadePeso;
                }
                break;
            }
        }
    }
    arquivo.close();

    // Ordena os resultados
    mergeSort(irregularidadeCNPJ, 0, qtdIrregularidadeCNPJ - 1, false);
    mergeSort(irregularidadePeso, 0, qtdIrregularidadePeso - 1, true);

    // Imprime resultados
    for (int i = 0; i < qtdIrregularidadeCNPJ; ++i) irregularidadeCNPJ[i].imprimir();
    for (int i = 0; i < qtdIrregularidadePeso; ++i) irregularidadePeso[i].imprimir();

    return 0;
}
