#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace chrono;

//////////////////////////
// Estruturas dos dados //
//////////////////////////

struct Gene {
    string sequencia;
};

struct Doenca {
    string nome;
    int num_gene;
    Gene* genes;
    int prob;    // Porcentagem inteira de genes detectados
    int order;   // Ordem de entrada para estabilidade na ordenação
};

/////////////////////////////
// Funções de I/O e leitura //
/////////////////////////////

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
        input >> doencas[i].nome >> doencas[i].num_gene;
        doencas[i].genes = new Gene[doencas[i].num_gene];
        doencas[i].order = i; // registra ordem de entrada para ordenação estável
        for (int j = 0; j < doencas[i].num_gene; j++) {
            input >> doencas[i].genes[j].sequencia;
        }
    }
    input.close();
}

//////////////////////////////
// Sufix Automaton (SA)     //
// para buscas de substring //
//////////////////////////////

// Nosso alfabeto: A, C, G, T
int charToIndex(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    return -1; // não deve ocorrer
}

struct SAState {
    int len, link;
    int next[4]; // para cada letra do alfabeto
};

SAState* sa;      // array de estados
int saSize;       // número de estados
int saLast;       // índice do estado "last"

// Inicializa o autômato (tamanho máximo = 2 * |dna|)
void sa_init(int maxSize) {
    sa = new SAState[maxSize];
    sa[0].len = 0;
    sa[0].link = -1;
    for (int i = 0; i < 4; i++) 
        sa[0].next[i] = -1;
    saSize = 1;
    saLast = 0;
}

// Extende o autômato com o caractere c
void sa_extend(int c) {
    int cur = saSize++;
    sa[cur].len = sa[saLast].len + 1;
    for (int i = 0; i < 4; i++)
        sa[cur].next[i] = -1;
    int p = saLast;
    for (; p != -1 && sa[p].next[c] == -1; p = sa[p].link) {
        sa[p].next[c] = cur;
    }
    if (p == -1) {
        sa[cur].link = 0;
    } else {
        int q = sa[p].next[c];
        if (sa[p].len + 1 == sa[q].len) {
            sa[cur].link = q;
        } else {
            int clone = saSize++;
            sa[clone].len = sa[p].len + 1;
            for (int i = 0; i < 4; i++)
                sa[clone].next[i] = sa[q].next[i];
            sa[clone].link = sa[q].link;
            for (; p != -1 && sa[p].next[c] == q; p = sa[p].link) {
                sa[p].next[c] = clone;
            }
            sa[q].link = sa[cur].link = clone;
        }
    }
    saLast = cur;
}

// Constrói o autômato para o DNA
void construir_sa(const string &dna) {
    int n = dna.size();
    // Tamanho máximo de estados é 2*n (além de uma margem)
    sa_init(2 * n + 5);
    for (int i = 0; i < n; i++) {
        int idx = charToIndex(dna[i]);
        sa_extend(idx);
    }
}

////////////////////////////////////////
// Cálculo do comprimento do maior trecho
// do gene (iniciando em i) que aparece no DNA,
// usando o autômato de sufixos.
////////////////////////////////////////

int longestMatchFrom(int i, const string &gene) {
    int state = 0, length = 0;
    int maxLen = 0;
    int n = gene.size();
    for (int j = i; j < n; j++) {
        int c = charToIndex(gene[j]);
        if (sa[state].next[c] != -1) {
            state = sa[state].next[c];
            length++;
        } else {
            break;
        }
    }
    maxLen = length;
    return maxLen;
}

////////////////////////////////////////
// DP para calcular a soma máxima dos
// comprimentos dos blocos não sobrepostos
// (cada bloco deve ter comprimento >= tam_subcadeia)
// que podem ser "reconstruídos" do gene e
// que aparecem no DNA.
////////////////////////////////////////

int maxMatchDP(const string &gene, int tam_subcadeia) {
    int m = gene.size();
    int* dp = new int[m + 1];
    // dp[m] = 0
    dp[m] = 0;
    // Pré-computa L[i]: o comprimento máximo do trecho iniciando em i que aparece no DNA
    int* L = new int[m];
    for (int i = 0; i < m; i++) {
        L[i] = longestMatchFrom(i, gene);
    }
    
    for (int i = m - 1; i >= 0; i--) {
        int best = dp[i + 1]; // opção de pular o caractere i
        if (L[i] >= tam_subcadeia) {
            // Tenta todos os comprimentos válidos (de tam_subcadeia até L[i]) a partir de i
            for (int seg = tam_subcadeia; seg <= L[i]; seg++) {
                int candidate = seg + dp[i + seg];
                if (candidate > best)
                    best = candidate;
            }
        }
        dp[i] = best;
    }
    int total = dp[0];
    delete[] dp;
    delete[] L;
    return total;
}

////////////////////////////////////////
// Determina se um gene é detectado:
// se a soma máxima dos comprimentos dos blocos
// for >= ceil(0.9 * tamanho do gene)
////////////////////////////////////////

bool geneDetectada(const string &gene, int tam_subcadeia) {
    int m = gene.size();
    int total = maxMatchDP(gene, tam_subcadeia);
    int required = (int)ceil(0.9 * m);
    return (total >= required);
}

////////////////////////////////////////
// Calcula a probabilidade da doença:
// Para cada doença, conta quantos de seus genes foram detectados.
// A chance é (genes detectados / total de genes) * 100, arredondada.
// Se o valor for ≥ 90, considera 100.
////////////////////////////////////////

void calcular_probabilidade(Doenca *doencas, int num_doencas, const string &dna, int tam_subcadeia) {
    // Constrói o autômato de sufixos para o DNA (apenas uma vez)
    construir_sa(dna);
    
    for (int i = 0; i < num_doencas; i++) {
        int detectadas = 0;
        for (int j = 0; j < doencas[i].num_gene; j++) {
            // Para cada gene, verifica se o total de caracteres "reconstruídos"
            // é, pelo menos, 90% do tamanho do gene.
            if (geneDetectada(doencas[i].genes[j].sequencia, tam_subcadeia))
                detectadas++;
        }
        int perc = (int)round((double)detectadas / doencas[i].num_gene * 100);
        doencas[i].prob = (perc >= 90 ? 100 : perc);
    }
    
    // Libera o autômato
    delete[] sa;
}

////////////////////////////////////////
// MergeSort estável para ordenar as doenças
// em ordem decrescente de probabilidade.
// Em caso de empate, mantém a ordem de entrada.
////////////////////////////////////////

void merge(Doenca *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Doenca *L = new Doenca[n1];
    Doenca *R = new Doenca[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].prob > R[j].prob || (L[i].prob == R[j].prob && L[i].order <= R[j].order)) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(Doenca *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mostrar_doencas(ofstream &output, Doenca *doencas, int num_doencas) {
    for (int i = 0; i < num_doencas; i++) {
        output << doencas[i].nome << "->" << doencas[i].prob << "%" << endl;
    }
}

//////////////////////////////
// Função principal (main)  //
//////////////////////////////

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
    
    calcular_probabilidade(doencas, num_doencas, dna, tam_subcadeia);
    mergeSort(doencas, 0, num_doencas - 1);
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
