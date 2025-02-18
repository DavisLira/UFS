#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>  // Para controle de casas decimais
#include <fstream>  // Para ler e escrever arquivos
#include <chrono> 

using namespace std;
using namespace chrono;

struct Pacote {
    string codigo;  // Identificador do pacote
    float valor;    // Valor do pacote
    float peso;     // Peso do pacote
    float volume;   // Volume do pacote
    bool alocado;   // Flag para indicar se o pacote foi alocado a algum carro
};

struct Carro {
    string placa;     // Placa do carro
    float peso_max;   // Peso máximo que o carro pode carregar
    float volume_max; // Volume máximo que o carro pode carregar
    Pacote* pacotes;  // Lista de pacotes que o carro pode carregar
    int num_pacotes;  // Número de pacotes para este carro
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
        // Aqui, note que o número de pacotes ainda não foi lido;
        // a alocação dos pacotes para cada carro será feita depois.
        carros[i].pacotes = nullptr;  
        carros[i].num_pacotes = 0;
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
    int maxPeso = (int)carro.peso_max;
    int maxVolume = (int)carro.volume_max;

    // Aloca um bloco único para todos os valores da DP
    float* dp_data = new float[(num_pacotes + 1) * (maxPeso + 1) * (maxVolume + 1)]();
    
    // Cria a estrutura dp (três níveis) apontando para o bloco alocado
    float*** dp = new float**[num_pacotes + 1];
    for (int i = 0; i <= num_pacotes; i++) {
        dp[i] = new float*[maxPeso + 1];
        for (int w = 0; w <= maxPeso; w++) {
            dp[i][w] = dp_data + i * ((maxPeso + 1) * (maxVolume + 1)) + w * (maxVolume + 1);
        }
    }

    // Construindo a tabela DP
    for (int i = 1; i <= num_pacotes; i++) {
        // Se o pacote já foi alocado, copiamos a linha anterior para manter o estado ótimo
        if (pacotes[i - 1].alocado) {
            for (int w = 0; w <= maxPeso; w++) {
                for (int v = 0; v <= maxVolume; v++) {
                    dp[i][w][v] = dp[i - 1][w][v];
                }
            }
            continue;
        }

        // Cache local dos atributos do pacote para reduzir acessos repetidos
        float valorPacote = pacotes[i - 1].valor;
        int pacotePeso = (int)pacotes[i - 1].peso;
        int pacoteVolume = (int)pacotes[i - 1].volume;

        // Cache dos ponteiros para a linha da DP
        float** prevDP = dp[i - 1];
        float** currDP = dp[i];
        for (int w = 0; w <= maxPeso; w++) {
            for (int v = 0; v <= maxVolume; v++) {
                if (w >= pacotePeso && v >= pacoteVolume) {
                    float candidate = valorPacote + prevDP[w - pacotePeso][v - pacoteVolume];
                    currDP[w][v] = (candidate > prevDP[w][v] ? candidate : prevDP[w][v]);
                } else {
                    currDP[w][v] = prevDP[w][v];
                }
            }
        }
    }

    // Recuperando os pacotes selecionados
    int w = maxPeso, v = maxVolume;
    int num_pac_esc = 0;
    Pacote* pacotes_escolhidos = new Pacote[num_pacotes];

    for (int i = num_pacotes; i > 0 && w > 0 && v > 0; i--) {
        // Se o pacote já foi alocado, pula
        if (pacotes[i - 1].alocado)
            continue;
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

    // Liberar memória alocada para a DP
    delete[] dp_data;
    for (int i = 0; i <= num_pacotes; i++) {
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

void mostrar_pacotes_pendentes2(Pacote* pct, int qtd, ofstream& output) {
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
        float peso_c = 0;
        float volume_c = 0;
        int qtd_c = 0;

        pegar_dados_pacotes(carros[i].pacotes, carros[i].num_pacotes, pacotes_c, qtd_c, valor_c, peso_c, volume_c);

        int peso_porct = round(peso_c / carros[i].peso_max * 100);
        int vol_porct = round(volume_c / carros[i].volume_max * 100);

        output << "[" << carros[i].placa << "]R$" 
               << fixed << setprecision(2) << valor_c << ","
               << fixed << setprecision(0) << peso_c << "KG(" << peso_porct << "%),"
               << volume_c << "L(" << vol_porct << "%)->";

        mostrar_pacotes(pacotes_c, qtd_c, output);
        output << endl;

        delete[] pacotes_c;
    }
}

void mostrar_pacotes_pendentes(ofstream& output, Pacote* pacotes, int num_pacotes) {
    Pacote* pacotes_p = new Pacote[num_pacotes];
    float valor_p = 0;
    float peso_p = 0;
    float volume_p = 0;
    int qtd_p = 0;

    pegar_dados_pacotes(pacotes, num_pacotes, pacotes_p, qtd_p, valor_p, peso_p, volume_p);

    output << "PENDENTE:R$" 
           << fixed << setprecision(2) << valor_p << ","
           << fixed << setprecision(0) << peso_p << "KG," << volume_p << "L->";

    mostrar_pacotes_pendentes2(pacotes_p, qtd_p, output);
    delete[] pacotes_p;
}

int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();
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

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Tempo para inicializar e ler arquivo: " << duration.count() << " microsegundos\n";

    start = high_resolution_clock::now();
    verificar_disponibilidade(carros, num_carros, pacotes, num_pacotes);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Tempo para verificar disponibilidade: " << duration.count() << " microsegundos\n";

    mostrar_carros(output, carros, num_carros);
    mostrar_pacotes_pendentes(output, pacotes, num_pacotes);

    input.close();
    output.close();

    // Liberação de memória (carros e pacotes)
    for (int i = 0; i < num_carros; i++) {
        delete[] carros[i].pacotes;
    }
    delete[] carros;
    delete[] pacotes;

    return 0;
}
