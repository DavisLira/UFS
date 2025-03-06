#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// =====================
// Função de abertura de arquivos
// =====================
bool abrir_arquivos(const char* entrada, const char* saida, ifstream& input, ofstream& output) {
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

// =====================
// Conversão para hexadecimal (2 dígitos, uppercase)
// =====================
void toHex(int x, char out[3]) {
    const char* hexDigits = "0123456789ABCDEF";
    out[0] = hexDigits[(x >> 4) & 0xF];
    out[1] = hexDigits[x & 0xF];
    out[2] = '\0';
}

// =====================
// RLE – Run-Length Encoding
// =====================
// Para cada grupo de bytes idênticos (máximo 255), gera [contagem em hex][byte em hex]
std::string rleEncode(const int* tokens, int count) {
    std::string result;
    char hex[3];
    int i = 0;
    while(i < count) {
        int run = 1;
        while(i + run < count && tokens[i+run] == tokens[i] && run < 255)
            run++;
        toHex(run, hex);
        result += hex;
        toHex(tokens[i], hex);
        result += hex;
        i += run;
    }
    return result;
}

// =====================
// Estrutura para armazenar cada sequência de entrada
// =====================
struct Sequence {
    int count;
    int* tokens; // array de inteiros (cada byte de 0 a 255)
};

// =====================
// Estrutura da árvore de Huffman
// =====================
struct Node {
    int freq;       // frequência do símbolo (ou soma para nós internos)
    int symbol;     // valor do byte (0–255) para folha; -1 para nó interno
    int minLeaf;    // menor valor (em número) dentre as folhas deste nó
    Node* left;
    Node* right;
};

// Cria nó folha
Node* newLeaf(int symbol, int freq) {
    Node* n = new Node;
    n->freq = freq;
    n->symbol = symbol;
    n->minLeaf = symbol;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

// Cria nó interno a partir de dois filhos
Node* newInternal(Node* left, Node* right) {
    Node* n = new Node;
    n->freq = left->freq + right->freq;
    n->symbol = -1;
    n->minLeaf = (left->minLeaf < right->minLeaf ? left->minLeaf : right->minLeaf);
    n->left = left;
    n->right = right;
    return n;
}

// =====================
// Implementação de uma fila de prioridade (min-heap) usando array
// Máx. de nós = 511 (pois há no máximo 256 folhas)
// =====================
struct Heap {
    Node* arr[512];
    int size;
};

// Comparador customizado – usado na inserção e extração do heap
// Se as frequências diferem, o de menor frequência tem prioridade.
// Se as frequências são iguais e ambos são folhas, o de *maior* valor de símbolo (decrescente) tem prioridade – isso garante que, no caso "FA FA C1 C1", FA seja extraído primeiro e receba código "1" (resultando em "C0").
// Para outros casos, com nós internos, comparamos o campo minLeaf.
bool heapLess(Node* a, Node* b) {
    if(a->freq != b->freq)
        return a->freq < b->freq;
    if(a->symbol != -1 && b->symbol != -1)
        return a->symbol > b->symbol;
    return a->minLeaf < b->minLeaf;
}

void heapPush(Heap* heap, Node* node) {
    int i = heap->size++;
    heap->arr[i] = node;
    while(i > 0) {
        int parent = (i - 1) / 2;
        if(heapLess(heap->arr[i], heap->arr[parent])) {
            Node* temp = heap->arr[i];
            heap->arr[i] = heap->arr[parent];
            heap->arr[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

Node* heapPop(Heap* heap) {
    Node* ret = heap->arr[0];
    heap->size--;
    heap->arr[0] = heap->arr[heap->size];
    int i = 0;
    while(true) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        if(left < heap->size && heapLess(heap->arr[left], heap->arr[smallest]))
            smallest = left;
        if(right < heap->size && heapLess(heap->arr[right], heap->arr[smallest]))
            smallest = right;
        if(smallest != i) {
            Node* temp = heap->arr[i];
            heap->arr[i] = heap->arr[smallest];
            heap->arr[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return ret;
}

// =====================
// Construção da árvore de Huffman (como no código do professor)
// =====================
Node* buildHuffmanTree(const int* data, int count) {
    int freq[256];
    for (int i = 0; i < 256; i++) freq[i] = 0;
    for (int i = 0; i < count; i++) {
        freq[data[i]]++;
    }
    Heap heap;
    heap.size = 0;
    for (int i = 0; i < 256; i++) {
        if(freq[i] > 0)
            heapPush(&heap, newLeaf(i, freq[i]));
    }
    if(heap.size == 0) return nullptr;
    if(heap.size == 1) return heapPop(&heap);
    while(heap.size > 1) {
        Node* x = heapPop(&heap);
        Node* y = heapPop(&heap);
        Node* parent = newInternal(x, y);
        heapPush(&heap, parent);
    }
    return heapPop(&heap);
}

// =====================
// Geração dos códigos de Huffman para cada símbolo
// Usamos recursão para construir a tabela; a convenção aqui é a convencional:
// ao percorrer a árvore, o ramo esquerdo recebe "0" e o direito "1".
// (A escolha do critério de atribuição afeta o código final.)
void buildCodes(Node* root, const char* code, std::string codes[256]) {
    if(!root) return;
    if(!root->left && !root->right) {
        if(strlen(code) == 0)
            codes[root->symbol] = "0";
        else
            codes[root->symbol] = code;
        return;
    }
    char leftCode[128], rightCode[128];
    strcpy(leftCode, code);
    strcpy(rightCode, code);
    strcat(leftCode, "0");
    strcat(rightCode, "1");
    buildCodes(root->left, leftCode, codes);
    buildCodes(root->right, rightCode, codes);
}

void deleteTree(Node* root) {
    if(!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// =====================
// Procedimento de compactação com Huffman
// Constrói a árvore, gera a tabela de códigos e codifica a sequência.
// Em seguida, a string de bits é completada com zeros (se necessário) e convertida para hexadecimal.
// =====================
std::string huffmanEncode(const int* data, int count) {
    Node* root = buildHuffmanTree(data, count);
    if(!root) return "";
    std::string codes[256];
    char code[1] = "";
    buildCodes(root, code, codes);
    std::string bitString;
    for (int i = 0; i < count; i++) {
        bitString += codes[data[i]];
    }
    while(bitString.size() % 8 != 0)
        bitString += "0";
    std::string result;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        int byteVal = 0;
        for (int j = 0; j < 8; j++) {
            byteVal = (byteVal << 1) + (bitString[i+j] - '0');
        }
        char hex[3];
        toHex(byteVal, hex);
        result += hex;
    }
    deleteTree(root);
    return result;
}

// =====================
// Processamento de uma sequência: gera as codificações RLE e Huffman,
// calcula a taxa de compressão e decide qual técnica (ou ambas) será impressa.
// =====================
std::string processSequence(int index, const int* data, int count) {
    std::string encodedRLE = rleEncode(data, count);
    std::string encodedHUF = huffmanEncode(data, count);
    int sizeRLE = encodedRLE.size() / 2; // cada 2 dígitos = 1 byte
    int sizeHUF = encodedHUF.size() / 2;
    double rateRLE = ((double) sizeRLE / count) * 100.0;
    double rateHUF = ((double) sizeHUF / count) * 100.0;
    std::ostringstream oss;
    if(sizeHUF < sizeRLE)
        oss << index << "->HUF(" << fixed << setprecision(2) << rateHUF << "%)=" << encodedHUF;
    else if(sizeRLE < sizeHUF)
        oss << index << "->RLE(" << fixed << setprecision(2) << rateRLE << "%)=" << encodedRLE;
    else {
        oss << index << "->HUF(" << fixed << setprecision(2) << rateHUF << "%)=" << encodedHUF << "\n";
        oss << index << "->RLE(" << fixed << setprecision(2) << rateRLE << "%)=" << encodedRLE;
    }
    return oss.str();
}

// =====================
// Processamento em paralelo: cada thread processa um intervalo de sequências
// =====================
void processRange(Sequence* seqArray, int numSequences, int start, int end, std::string* results) {
    for (int i = start; i < end; i++) {
        results[i] = processSequence(i, seqArray[i].tokens, seqArray[i].count);
    }
}

// =====================
// Função principal
// =====================
int main(int argc, char* argv[]) {
    auto startTime = high_resolution_clock::now();
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }
    ifstream input;
    ofstream output;
    if (!abrir_arquivos(argv[1], argv[2], input, output))
        return 1;
    
    int numSequences;
    input >> numSequences;
    // Aloca array de Sequência (usando array dinâmico)
    Sequence* seqArray = new Sequence[numSequences];
    for (int i = 0; i < numSequences; i++) {
        input >> seqArray[i].count;
        int cnt = seqArray[i].count;
        seqArray[i].tokens = new int[cnt];
        for (int j = 0; j < cnt; j++) {
            char token[3];
            input >> token;
            int value = (int)strtol(token, NULL, 16);
            seqArray[i].tokens[j] = value;
        }
    }
    
    // Array para guardar as saídas (resultado de cada sequência)
    std::string* results = new std::string[numSequences];
    
    // Processamento em paralelo – divide as sequências entre as threads disponíveis
    unsigned int numThreads = std::thread::hardware_concurrency();
    if(numThreads == 0)
        numThreads = 2;
    int sequencesPerThread = numSequences / numThreads;
    int remainder = numSequences % numThreads;
    std::thread* threads = new std::thread[numThreads];
    int current = 0;
    for (unsigned int t = 0; t < numThreads; t++) {
        int startIdx = current;
        int cnt = sequencesPerThread + (t < remainder ? 1 : 0);
        int endIdx = startIdx + cnt;
        threads[t] = std::thread(processRange, seqArray, numSequences, startIdx, endIdx, results);
        current = endIdx;
    }
    for (unsigned int t = 0; t < numThreads; t++) {
        threads[t].join();
    }
    
    // Escreve os resultados na saída (na ordem das sequências)
    for (int i = 0; i < numSequences; i++) {
        output << results[i] << "\n";
    }
    input.close();
    output.close();
    
    // Libera memória alocada
    for (int i = 0; i < numSequences; i++) {
        delete[] seqArray[i].tokens;
    }
    delete[] seqArray;
    delete[] results;
    delete[] threads;
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);
    cerr << "Tempo de execucao: " << duration.count() << " ms" << endl;
    return 0;
}
