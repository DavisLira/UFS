#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

struct Gene {
    int tamanho;
    string sequencia;
};

struct Doenca {
    string nome;
    int num_genes;
    Gene* genes;
    int tamanho_genes;
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

    int tam_gene = 0;

    for (int i = 0; i < num_doencas; i++) {
        input >> doencas[i].nome >> doencas[i].num_genes;
        doencas[i].genes = new Gene[doencas[i].num_genes];
        for (int j = 0; j < doencas[i].num_genes; j++) {
            input >> doencas[i].genes[j].sequencia;
            tam_gene = doencas[i].genes[j].sequencia.size();
            doencas[i].genes[j].tamanho = tam_gene;
            doencas[i].tamanho_genes += tam_gene;
        }
    }
    input.close();
}

/* 
Função auxiliar: tenta extrair um segmento de correspondência do gene a partir das posições atuais.
Parâmetros:
  dna, gene, tam_subcadeia
  pos_dna, pos_gene: posição inicial nos respectivos vetores.
  
Retorna (por referência):
  new_dna, new_gene: as posições onde a busca parou;
  segCount: quantos caracteres consecutivos foram combinados.
  
Se o segmento encontrado tiver comprimento >= tam_subcadeia, a função retorna true.
Além disso, se o segmento foi interrompido por divergência (e não por ter chegado ao fim do gene)
e se o que falta no gene é menor que tam_subcadeia, então o segmento é “ajustado” para valer apenas tam_subcadeia.
*/
bool match_segment(const string &dna, const Gene &gene, int pos_dna, int pos_gene, int tam_subcadeia,
                   int &new_dna, int &new_gene, int &segCount)
{
    int i = pos_dna, j = pos_gene;
    int count = 0;
    // percorre enquanto houver caracteres em ambos
    while(i < dna.size() && j < gene.tamanho) {
        if(dna[i] == gene.sequencia[j]) {
            count++;
            i++;
            j++;
        } else {
            break;
        }
    }
    // Se encontramos um segmento com tamanho suficiente:
    if(count >= tam_subcadeia) {
        // Se a interrupção ocorreu por divergência (ou seja, não chegou ao fim do gene)
        // e o que falta do gene (a partir de j) é menor que tam_subcadeia,
        // consideramos que esse segmento, apesar de maior, não poderá ser completado;
        // assim, contamos somente o mínimo.
        if(j < gene.tamanho && (gene.tamanho - j) < tam_subcadeia)
            segCount = tam_subcadeia;
        else
            segCount = count;
        new_dna = i;  // a busca continuará a partir daqui no DNA
        new_gene = j; // e a partir deste índice no gene
        return true;
    }
    return false;
}

/*
A função contar_genes percorre o DNA tentando “extrair” sucessivos segmentos de correspondência do gene.
Se um segmento válido for encontrado (ou seja, com pelo menos tam_subcadeia caracteres consecutivos),
o contador é incrementado (com o valor do segmento – ou com tam_subcadeia, se for final de gene) e a busca
continua a partir dos pontos onde parou.
Caso a tentativa de extração falhe, se ainda não tivermos iniciado um segmento (pos_gene == 0)
avançamos uma posição no DNA; se já estivermos “dentro” de uma correspondência (pos_gene > 0), deixamos o ponteiro do gene inalterado e avançamos no DNA.
*/
int contar_genes(string dna, Gene gene, int tam_subcadeia) {
    int contador = 0;
    int pos_dna = 0, pos_gene = 0;
    int segCount = 0, new_dna = 0, new_gene = 0;

    // enquanto houver caracteres no DNA e ainda houver parte do gene a ser “processada”
    while(pos_dna < dna.size() && pos_gene < gene.tamanho) {
        // Tenta extrair um segmento a partir das posições atuais
        if(match_segment(dna, gene, pos_dna, pos_gene, tam_subcadeia, new_dna, new_gene, segCount)) {
            contador += segCount;
            pos_dna = new_dna; 
            pos_gene = new_gene;
        } else {
            // Se não conseguiu extrair um segmento válido:
            if(pos_gene == 0) {
                pos_dna++; // não estava iniciando uma correspondência, avança o DNA
            } else {
                // Se já estava no meio de uma tentativa, mantém o ponteiro do gene e avança o DNA
                pos_dna++;
            }
        }
    }
    return contador;
}

void procurar_por_gene(string dna, Doenca& doenca, Gene* genes, int num_genes, int tam_subcadeia) {
    int contador = 0;
    int contador_final = 0;
    cout << "Doença: " << doenca.nome << endl;

    for (int i = 0; i < num_genes; i++) {
        cout << "Gene: " << genes[i].sequencia << endl;
        // Para cada gene, reiniciamos a busca no DNA do início
        contador = contar_genes(dna, genes[i], tam_subcadeia);
        cout << "Contador parcial: " << contador << endl;
        // Aqui você pode acumular (por exemplo, somando) ou armazenar o valor em doenca.prob;
        // neste exemplo, atribuímos o resultado deste gene.
        contador_final += contador;
    }
    cout << "Contador final: " << contador_final << endl << endl;

    doenca.prob = (contador_final * 100) / doenca.tamanho_genes;
    if (doenca.prob >= 90) {
        doenca.prob = 100;
    }

    cout << "probabilidade: " << doenca.prob << endl << endl;
}

void calcular_probabilidade(string dna, Doenca *doencas, int num_doencas, int tam_subcadeia) {
    for (int i = 0; i < num_doencas; i++) {
        procurar_por_gene(dna, doencas[i], doencas[i].genes, doencas[i].num_genes, tam_subcadeia);
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

    calcular_probabilidade(dna, doencas, num_doencas, tam_subcadeia);
    mergeSort(doencas, 0, num_doencas - 1);
    mostrar_doencas(output, doencas, num_doencas);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tempo para rodar o código: " << duration.count() << " microsegundos\n";
    
    output.close();
    for (int i = 0; i < num_doencas; i++) 
        delete[] doencas[i].genes;
    delete[] doencas;
    
    return 0;
}
