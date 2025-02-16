#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>  // Para controle de casas decimais
#include <fstream>  // Para ler e escrever arquivos

using namespace std;

struct Pacote {
    string codigo;  // Identificador do pacote
    float valor;    // Valor do pacote
    float peso;       // Peso do pacote
    float volume;     // Volume do pacote
    bool alocado;   // Flag para indicar se o pacote foi alocado a algum carro
};

struct Carro {
    string placa;    // Placa do carro
    float peso_max;    // Peso máximo que o carro pode carregar
    float volume_max;  // Volume máximo que o carro pode carregar
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

void knapsack(Carro& carro, Pacote* pacotes, int num_pacotes) {
    // Alocação dinâmica da tabela DP para evitar estouro de pilha
    float*** dp = new float**[num_pacotes + 1];
    for (int i = 0; i <= num_pacotes; i++) {
        dp[i] = new float*[(int)carro.peso_max + 1];
        for (int w = 0; w <= (int)carro.peso_max; w++) {
            dp[i][w] = new float[(int)carro.volume_max + 1](); // Inicializa com 0
        }
    }
    

    // Construindo a tabela DP
    for (int i = 1; i <= num_pacotes; i++) {
        if (pacotes[i - 1].alocado) continue; // Ignora pacotes já alocados

        for (int w = 0; w <= (int)carro.peso_max; w++) {
            for (int v = 0; v <= (int)carro.volume_max; v++) {
                if (pacotes[i - 1].peso <= w && pacotes[i - 1].volume <= v) {
                    int new_w = w - (int)pacotes[i - 1].peso;
                    int new_v = v - (int)pacotes[i - 1].volume;
                    
                    dp[i][w][v] = max(
                        pacotes[i - 1].valor + (new_w >= 0 && new_v >= 0 ? dp[i - 1][new_w][new_v] : 0),
                        dp[i - 1][w][v]
                    );
                } else {
                    dp[i][w][v] = dp[i - 1][w][v];
                }
            }
        }
    }

    // Recuperando os pacotes selecionados
    int w = (int)carro.peso_max, v = (int)carro.volume_max;
    int num_pac_esc = 0;
    Pacote* pacotes_escolhidos = new Pacote[num_pacotes];

    for (int i = num_pacotes; i > 0 && w > 0 && v > 0; i--) {
        if (pacotes[i - 1].alocado) continue; // Pula pacotes já alocados

        if (dp[i][w][v] != dp[i - 1][w][v]) {
            pacotes_escolhidos[num_pac_esc++] = pacotes[i - 1];
            pacotes[i - 1].alocado = true; // Marca o pacote como alocado

            w -= (int)pacotes[i - 1].peso;
            v -= (int)pacotes[i - 1].volume;
        }
    }

    // Atribuir pacotes selecionados ao carro
    carro.pacotes = pacotes_escolhidos;
    carro.num_pacotes = num_pac_esc;

    // Liberar memória alocada para dp
    for (int i = 0; i <= num_pacotes; i++) {
        for (int w = 0; w <= (int)carro.peso_max; w++) {
            delete[] dp[i][w];
        }
        delete[] dp[i];
    }
    delete[] dp;
}

void verificar_disponibilidade(Carro* carros, int num_carros, Pacote* pacotes, int num_pacotes) {
    for (int i = 0; i < num_carros; i++) {
        knapsack(carros[i], pacotes, num_pacotes);
    }
}

void pegar_dados_pacotes(
        Pacote* pacotes, int num,
        Pacote* pacotes_r, int& qtd_r,
        float& valor_r, float& peso_r, float& volume_r
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
    for (int i = qtd - 1; i >= 0; i--) { // Percorre de trás para frente
        if (i < qtd - 1) { // Adiciona a vírgula entre os elementos
            output << ",";
        }
        output << pct[i].codigo;
    }
}

void mostrar_carros(ofstream& output, Carro* carros, int num_carros) {
    for (int i = 0; i < num_carros; i++) {
        Pacote* pacotes_c = new Pacote[carros[i].num_pacotes];
        float valor_c = 0;
        float peso_c = 0;
        float volume_c = 0;
        int qtd_c = 0;

        pegar_dados_pacotes(carros[i].pacotes, carros[i].num_pacotes, pacotes_c, qtd_c, valor_c, peso_c, volume_c);

        int peso_porct = round(peso_c / carros[i].peso_max * 100);
        int vol_porct = round(volume_c / carros[i].volume_max * 100);

        output << "[" << carros[i].placa << "]R$" 
        << std::fixed << std::setprecision(2) << valor_c << ","
        << std::fixed << std::setprecision(0) << peso_c << "KG("
        << peso_porct << "%)," << volume_c << "L(" << vol_porct << "%)->";

        mostrar_pacotes(pacotes_c, qtd_c, output);
        output << endl;
    }
}

void mostrar_pacotes_pendentes(ofstream& output, Pacote* pacotes, int num_pacotes) {
    Pacote* pacotes_p = new Pacote[num_pacotes];
    float valor_p = 0;
    float peso_p = 0;
    float volume_p = 0;
    int qtd_p = 0;

    pegar_dados_pacotes(pacotes, num_pacotes, pacotes_p, qtd_p, valor_p, peso_p, volume_p);

    output << "PENDENTE:R$" << 
        std::fixed << std::setprecision(2) << valor_p << "," << 
        std::fixed << std::setprecision(0) << peso_p << "KG," << volume_p << "L->";

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
