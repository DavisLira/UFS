#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>  // Para controle de casas decimais
#include <fstream>  // Para ler e escrever arquivos

using namespace std;

struct Pacote {
    string codigo;  // Identificador do pacote
    float valor;    // Valor do pacote
    int peso;       // Peso do pacote
    int volume;     // Volume do pacote
    bool alocado;   // Flag para indicar se o pacote foi alocado a algum carro
};

struct Carro {
    string placa;    // Placa do carro
    int peso_max;    // Peso máximo que o carro pode carregar
    int volume_max;  // Volume máximo que o carro pode carregar
    Pacote* pacotes; // Lista de pacotes que o carro pode carregar
    int num_pacotes; // Número de pacotes para este carro
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

// Função para ler os dados do arquivo e preencher as listas
void ler_arquivo(ifstream& input, int& num_carros, int& num_pacotes, Carro*& carros, Pacote*& pacotes) {
    input >> num_carros;
    carros = new Carro[num_carros];

    // Lê os carros
    for (int i = 0; i < num_carros; i++) {
        input >> carros[i].placa >> carros[i].peso_max >> carros[i].volume_max;
        carros[i].pacotes = new Pacote[num_pacotes];  // Inicializa os pacotes como nullptr
        carros[i].num_pacotes = 0;  // Inicializa o número de pacotes do carro
    }

    input >> num_pacotes;
    pacotes = new Pacote[num_pacotes];  // Aloca os pacotes

    // Lê os pacotes: código, valor, peso e volume
    for (int i = 0; i < num_pacotes; ++i) {
        input >> pacotes[i].codigo >> pacotes[i].valor >> pacotes[i].peso >> pacotes[i].volume;
        pacotes[i].alocado = false;  // Inicializa a flag de alocação do pacote
    }
}

void knapsack(Carro& carro, Pacote* pacotes, int num_pacotes, Pacote*& pacotes_r, int& qtd_r) {
    int W = carro.peso_max;
    int V = carro.volume_max;
    int totalCelulas = (W + 1) * (V + 1);
    
    // Aloca as matrizes DP e de escolhas como arrays 1D.
    float* dp = new float[totalCelulas];
    int* choice = new int[totalCelulas];
    
    // Inicializa as matrizes: dp com 0 e choice com -1.
    for (int i = 0; i < totalCelulas; i++) {
        dp[i] = 0.0f;
        choice[i] = -1;
    }
    
    // Percorre cada pacote não alocado
    for (int i = 0; i < num_pacotes; i++) {
        if (pacotes[i].alocado) {
            continue;  // Pula pacotes já alocados para outro carro
        }
        int wt = pacotes[i].peso;
        int vol = pacotes[i].volume;
        float val = pacotes[i].valor;
        
        // Para cada pacote, percorre as capacidades de forma decrescente para evitar múltiplas contagens
        for (int w = W; w >= wt; w--) {
            for (int v = V; v >= vol; v--) {
                int idxAtual = w * (V + 1) + v;
                int idxPrev = (w - wt) * (V + 1) + (v - vol);
                float novoValor = dp[idxPrev] + val;
                if (novoValor > dp[idxAtual]) {
                    dp[idxAtual] = novoValor;
                    choice[idxAtual] = i;  // Registra o índice do pacote que melhorou o valor
                }
            }
        }
    }
    
    // Retropropagação (backtracking) para recuperar os pacotes selecionados
    qtd_r = 0;
    int w = W, v = V;
    while (w >= 0 && v >= 0) {
        int idxAtual = w * (V + 1) + v;
        if (choice[idxAtual] == -1) { // Se não houve escolha para este estado, encerra
            break;
        }
        int idxPacote = choice[idxAtual];
        pacotes_r[qtd_r++] = pacotes[idxPacote];  // Adiciona o pacote à lista do carro
        pacotes[idxPacote].alocado = true;           // Marca o pacote como alocado
        // Atualiza a capacidade remanescente
        w -= pacotes[idxPacote].peso;
        v -= pacotes[idxPacote].volume;
    }
    
    delete[] dp;
    delete[] choice;
}

void verificar_disponibilidade(Carro* carros, int num_carros, Pacote* pacotes, int num_pacotes) {
    for (int i = 0; i < num_carros; i++) {
        knapsack(carros[i], pacotes, num_pacotes, carros[i].pacotes, carros[i].num_pacotes);
    }
}

void pegar_dados_pacotes(
        Pacote* pacotes, int num,
        Pacote* pacotes_r, int& qtd_r,
        float& valor_r, int& peso_r, int& volume_r
    ) {

    for (int i = 0; i < num; i++) {
        if (!pacotes[i].alocado) {
            pacotes_r[qtd_r++] = pacotes[i];
            valor_r += pacotes[i].valor;
            peso_r += pacotes[i].peso;
            volume_r += pacotes[i].volume;
        }
    }
}

void mostrar_pacotes(Pacote* pct, int qtd, ofstream& output) {
    for (int i = 0; i < qtd; i++) {
        if (i > 0) {
            output << ",";
        }
        output << pct[i].codigo;
    }
}

void mostrar_carros(ofstream& output, Carro* carros, int num_carros) {
    for (int i = 0; i < num_carros; i++) {
        Pacote* pacotes_c = new Pacote[carros[i].num_pacotes];
        float valor_c = 0;
        int peso_c = 0;
        int volume_c = 0;
        int qtd_c = 0;

        pegar_dados_pacotes(carros[i].pacotes, carros[i].num_pacotes, pacotes_c, qtd_c, valor_c, peso_c, volume_c);

        output << "[" << carros[i].placa << "]R$" << valor_c << "," << peso_c << "KG," << volume_c << "L->";

        mostrar_pacotes(pacotes_c, qtd_c, output);
        output << endl;
    }

}

void mostrar_pacotes_pendentes(ofstream& output, Pacote* pacotes, int num_pacotes) {
    Pacote* pacotes_p = new Pacote[num_pacotes];
    float valor_p = 0;
    int peso_p = 0;
    int volume_p = 0;
    int qtd_p = 0;

    pegar_dados_pacotes(pacotes, num_pacotes, pacotes_p, qtd_p, valor_p, peso_p, volume_p);

    output << "PENDENTE:R$" << valor_p << "," << peso_p << "KG," << volume_p << "L->";

    mostrar_pacotes(pacotes_p, qtd_p, output);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }

    ifstream input;
    ofstream output;
    if (!abrir_arquivos(argv[1], argv[2], input, output)) {
        return 1;
    }

    int num_carros, num_pacotes;
    Pacote* pacotes = nullptr;
    Carro* carros = nullptr;
    ler_arquivo(input, num_carros, num_pacotes, carros, pacotes);

    verificar_disponibilidade(carros, num_carros, pacotes, num_pacotes);

    mostrar_carros(output, carros, num_carros);

    mostrar_pacotes_pendentes(output, pacotes, num_pacotes);

    input.close();
    output.close();

    return 0;
}
