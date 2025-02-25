#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>    // para round()

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
    int tamanho_genes; // soma dos tamanhos de todos os genes
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
        doencas[i].tamanho_genes = 0; // inicializa com 0 antes de acumular
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
Se o segmento tiver comprimento >= tam_subcadeia, atualiza:
   - new_dna: nova posição no DNA onde a busca continuará;
   - new_gene: nova posição no gene;
   - segCount: quantidade de caracteres combinados.
*/
bool match_segment(const string &dna, const Gene &gene, int pos_dna, int pos_gene, int tam_subcadeia,
                   int &new_dna, int &new_gene, int &segCount)
{
    int i = pos_dna, j = pos_gene;
    int count = 0;
    while(i < dna.size() && j < gene.tamanho) {
        if(dna[i] == gene.sequencia[j]) {
            count++;
            i++;
            j++;
        } else {
            break;
        }
    }
    if(count >= tam_subcadeia) {
        segCount = count;  // Agora, sempre conta o total combinado
        new_dna = i;  
        new_gene = j; 
        return true;
    }
    return false;
}

/*
A função contar_genes percorre o DNA tentando extrair sucessivos segmentos de correspondência do gene.
Se um segmento válido for encontrado (com pelo menos tam_subcadeia caracteres consecutivos),
incrementa o contador com o valor do segmento e a busca continua a partir dos pontos onde parou.
Caso não seja possível extrair um segmento válido, avança o ponteiro do DNA.
*/
int contar_genes(string dna, Gene gene, int tam_subcadeia) {
    int contador = 0;
    int pos_dna = 0, pos_gene = 0;
    int segCount = 0, new_dna = 0, new_gene = 0;

    while(pos_dna < dna.size() && pos_gene < gene.tamanho) {
        if(match_segment(dna, gene, pos_dna, pos_gene, tam_subcadeia, new_dna, new_gene, segCount)) {
            contador += segCount;
            pos_dna = new_dna; 
            pos_gene = new_gene;
        } else {
            // Se ainda não iniciou uma correspondência, avança no DNA
            pos_dna++;
        }
    }
    return contador;
}

/*
Função para procurar os genes e calcular a probabilidade da doença.
- Se a doença tem apenas 1 gene: 
    prob = round((contador * 100) / tamanho_do_gene);
- Se a doença tem mais de 1 gene:
    Para cada gene, se (round((contador * 100) / tamanho_do_gene)) >= 90, conta como 1.
    A probabilidade final é ( (número de genes com >= 90%) * 100 / número total de genes ),
    ajustando para 100 se o resultado for > 90.
*/
void procurar_por_gene(string dna, Doenca &doenca, Gene* genes, int num_genes, int tam_subcadeia) {
    // cout << "Doença: " << doenca.nome << endl;

    if(num_genes == 1) {
        // cout << "Gene: " << genes[0].sequencia << endl;
        int contador = contar_genes(dna, genes[0], tam_subcadeia);
        // cout << "Contador parcial: " << contador << endl;
        int prob = static_cast<int>( round((contador * 100.0) / genes[0].tamanho) );
        if(prob > 90)
            prob = 100;
        doenca.prob = prob;
        // cout << "Probabilidade: " << doenca.prob << endl << endl;
    }
    else {
        int genesAcima90 = 0;
        for (int i = 0; i < num_genes; i++) {
            // cout << "Gene: " << genes[i].sequencia << endl;
            int contador = contar_genes(dna, genes[i], tam_subcadeia);
            int genePerc = static_cast<int>( round((contador * 100.0) / genes[i].tamanho) );
            // cout << "Contador parcial: " << contador << " (Gene %: " << genePerc << "%)" << endl;
            if(genePerc >= 90)
                genesAcima90++;
        }
        int prob = static_cast<int>( round((genesAcima90 * 100.0) / num_genes) );
        if(prob > 90)
            prob = 100;
        doenca.prob = prob;
        // cout << "Contador final (genes com >= 90%): " << genesAcima90 << endl;
        // cout << "Probabilidade: " << doenca.prob << endl << endl;
    }
}

void calcular_probabilidade(string dna, Doenca *doencas, int num_doencas, int tam_subcadeia) {
    for (int i = 0; i < num_doencas; i++) {
        procurar_por_gene(dna, doencas[i], doencas[i].genes, doencas[i].num_genes, tam_subcadeia);
        if (doencas[i].prob >= 90) doencas[i].prob = 100;
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

    for (int i = 0; i < n1; i++) 
        leftArray[i] = doencas[left + i];
    for (int j = 0; j < n2; j++) 
        rightArray[j] = doencas[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].prob >= rightArray[j].prob) 
            doencas[k++] = leftArray[i++];
        else 
            doencas[k++] = rightArray[j++];
    }

    while (i < n1) 
        doencas[k++] = leftArray[i++];
    while (j < n2) 
        doencas[k++] = rightArray[j++];

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
