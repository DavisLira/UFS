#include <iostream>  // Para std::cout, std::cerr
#include <fstream>   // Para std::ifstream
#include <sstream>   // Para std::istringstream
#include <string>
#include <chrono>
#include <cmath>
#include <stdint.h>

using namespace std::chrono;
using namespace std;
int cont = 0;

//Lista da velocidade dos vetores e futura organização
struct Quick{
    string tipo;
    int contador;
};

//lista de controle dos vetores de tamanho  e ordem
struct Vetores{
    int tamanho;
    int* vetorLP;
    int* vetorLM;
    int* vetorLA;
    int* vetorHP;
    int* vetorHM;
    int* vetorHA;
    Quick listaQuicks;

};

//troca de valores
//troca de valores
void ordem(int* vetor1, int* vetor2){
    int temp = *vetor1;
    *vetor1 = *vetor2;
    *vetor2 = temp;
    cont++;
};

//definição dos tipos de ordenação
int LP(int* vetor, int inicio, int fim){
    int pivo = vetor[fim], marcador = inicio - 1;
    for (int ponteiro = inicio; ponteiro < fim; ponteiro++ ){
        if(vetor[ponteiro] <= pivo){
            ordem(&vetor[++marcador], &vetor[ponteiro]);
        };
    };
    ordem(&vetor[++marcador], &vetor[fim]);
    return marcador;
};

int LM(int* vetor, int inicio, int fim){

    int v1 = inicio + (fim - inicio + 1) / 4;
    int v2 = inicio + (fim - inicio + 1) / 2;
    int v3 = inicio + 3 * (fim - inicio + 1) / 4;

    if (vetor[v1] >= vetor[v2]  && vetor[v1] <= vetor[v3] || vetor[v1] <= vetor[v2] && vetor[v1] >= vetor[v3]){
        return v1;
    } else if(vetor[v2] >= vetor[v1]  && vetor[v2] <= vetor[v3] || vetor[v2] <= vetor[v1] && vetor[v2] >= vetor[v3]){
        return v2;
    } else {
        return v3;
    };
    
    return LP(vetor, inicio, fim);
};

int LA(int* vetor, int inicio, int fim){
    int aleatorio = inicio + (abs(vetor[inicio]) % (fim - inicio + 1));
    ordem(&vetor[fim], &vetor[aleatorio]);
    return LP(vetor, inicio, fim);
};

int HP(int* vetor, int inicio, int fim){
    int pivo = vetor[inicio], marcador = inicio - 1, ponteiro = fim + 1;

    while(true) {
        while(vetor[--ponteiro] > pivo);
        while(vetor[++marcador] < pivo);
        if (marcador < ponteiro) ordem(&vetor[marcador], &vetor[ponteiro]);
        else return ponteiro;
    }
};

int HM(int* vetor, int inicio, int fim){

    int v1 = inicio + (fim - inicio + 1) / 4;
    int v2 = inicio + (fim - inicio + 1) / 2;
    int v3 = inicio + 3 * (fim - inicio + 1) / 4;

    if (vetor[v1] >= vetor[v2]  && vetor[v1] <= vetor[v3] || vetor[v1] <= vetor[v2] && vetor[v1] >= vetor[v3]){
       return v1;
    } else if(vetor[v2] >= vetor[v1]  && vetor[v2] <= vetor[v3] || vetor[v2] <= vetor[v1] && vetor[v2] >= vetor[v3]){
       return v2;
    } else {
       return v3;
    };
    
    return HP(vetor, inicio, fim);
};


int HA(int* vetor, int inicio, int fim){
    int aleatorio = inicio + (abs(vetor[inicio]) % (fim - inicio + 1));
    ordem(&vetor[inicio], &vetor[aleatorio]);
    return HP(vetor, inicio, fim);
};


//definição do quicksort 
void quickSort(int* vetor, int inicio, int fim, string tipo){
    cont ++;
    //seleção de ordenação
    int pivo;
    if (inicio<fim){
        if(tipo == "LP"){ 
            pivo = LP(vetor, inicio, fim);
            quickSort(vetor, inicio, pivo-1, tipo);
            quickSort(vetor, pivo+1, fim, tipo);
        } else if(tipo == "LM"){
            int indice = LM(vetor, inicio, fim);
            ordem(&vetor[fim], &vetor[indice]);
            pivo = LP(vetor, inicio, fim);
            quickSort(vetor, inicio, pivo-1, tipo);
            quickSort(vetor, pivo+1, fim, tipo);
        } else if(tipo == "LA"){
            pivo = LA(vetor, inicio, fim);
            quickSort(vetor, inicio, pivo-1, tipo);
            quickSort(vetor, pivo+1, fim, tipo);
        } else if(tipo == "HP"){
            pivo = HP(vetor, inicio, fim);
            quickSort(vetor, inicio, pivo, tipo);
            quickSort(vetor, pivo+1, fim, tipo);
        } else if(tipo == "HM"){
            int indice = HM(vetor, inicio, fim);
            ordem(&vetor[inicio], &vetor[indice]);
            pivo = HP(vetor, inicio, fim);
            quickSort(vetor, inicio, pivo, tipo);
            quickSort(vetor, pivo+1, fim, tipo);
        }else if(tipo == "HA"){
            pivo = HA(vetor, inicio, fim);
            quickSort(vetor, inicio, pivo, tipo);
            quickSort(vetor, pivo+1, fim, tipo);
        };
    };
};


void ordemQuick(Quick* a, Quick* b) {
    Quick temp = *a;
    *a = *b;
    *b = temp;
};

int PPQuick(Quick* quicks, int inicio , int fim){
    int pivo = quicks[fim].contador;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (quicks[j].contador < quicks[fim].contador) {
            i++;
            ordemQuick(&quicks[i], &quicks[j]);
        }
    }
    ordemQuick(&quicks[i + 1], &quicks[fim]);
    return i + 1;
};

void quickSortQuick(Quick* quicks, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = PPQuick(quicks, inicio, fim);
        quickSortQuick(quicks, inicio, pivo - 1);
        quickSortQuick(quicks, pivo + 1, fim);
    }
}

void merge(Quick* entrada, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Quick* esquerda = new Quick[n1];
    Quick* direita = new Quick[n2];

    for (int i = 0; i < n1; ++i) esquerda[i] = entrada[inicio + i];
    for (int i = 0; i < n2; ++i) direita[i] = entrada[meio + 1 + i];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (esquerda[i].contador <= direita[j].contador) {
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

void mergeSort(Quick* entrada, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(entrada, inicio, meio);
        mergeSort(entrada, meio + 1, fim);
        merge(entrada, inicio, meio, fim);
    }
}

int main (int argc, char* argv[]){

    auto start = high_resolution_clock::now();
    //leitura e escrita de arquivo
    ifstream arquivoIn(argv[1]);
    ofstream arquivoOut(argv[2]);

    //verificação da leitura do arquivo 
    if(!arquivoIn.is_open()){
        std::cerr << "\n Erro ao abrir o arquivo" <<std::endl; 
        return 1;
    };

    int numVetores;

    arquivoIn >> numVetores;
    cout << numVetores << endl;
    Vetores* leituraVetores = new Vetores[numVetores];
    Quick* leituraQuicks = new Quick[7]; //eu vou sobrepor os valores de quicks

    for (int i = 0; i < numVetores; i++){

        //definição dos tipos de ordenação para voltar ao padrão em cada iteração
        leituraQuicks[1].tipo = "LP"; 
        leituraQuicks[2].tipo = "LM";
        leituraQuicks[3].tipo = "LA"; 
        leituraQuicks[4].tipo = "HP"; 
        leituraQuicks[5].tipo = "HM";  
        leituraQuicks[6].tipo = "HA";  

        arquivoIn >> leituraVetores[i].tamanho;
        leituraVetores[i].vetorLP = new int[leituraVetores[i].tamanho];
        leituraVetores[i].vetorLM = new int[leituraVetores[i].tamanho];
        leituraVetores[i].vetorLA = new int[leituraVetores[i].tamanho];
        leituraVetores[i].vetorHP = new int[leituraVetores[i].tamanho];
        leituraVetores[i].vetorHM = new int[leituraVetores[i].tamanho];
        leituraVetores[i].vetorHA = new int[leituraVetores[i].tamanho];


        for (int j = 0; j < leituraVetores[i].tamanho; j++){
            int num;
            arquivoIn >> num;
            leituraVetores[i].vetorLP[j] = num;
            leituraVetores[i].vetorLM[j] = num;
            leituraVetores[i].vetorLA[j] = num;
            leituraVetores[i].vetorHP[j] = num;
            leituraVetores[i].vetorHM[j] = num;
            leituraVetores[i].vetorHA[j] = num;
            cout << leituraVetores[i].vetorLP[j] << " ";
        };
        cout << endl;

        leituraQuicks[0].contador = leituraVetores[i].tamanho; 



        cont = 0;
        quickSort(leituraVetores[i].vetorLP, 0, leituraVetores[i].tamanho - 1, "LP");  
        leituraQuicks[1].contador = cont;
        cout << "terminou LP"  << endl;
        for (int j = 0; j < leituraVetores[i].tamanho; j++) {
            cout << leituraVetores[i].vetorLP[j] << " ";
        }
        cout << endl;
        
        cont = 0;
        quickSort(leituraVetores[i].vetorLM, 0, leituraVetores[i].tamanho - 1, "LM");  
        leituraQuicks[2].contador = cont;
        cout << "terminou LM"  << endl;
        cont = 0; 
        for (int j = 0; j < leituraVetores[i].tamanho; j++) {
            cout << leituraVetores[i].vetorLM[j] << " ";
        }
        cout << endl;

        quickSort(leituraVetores[i].vetorLA, 0, leituraVetores[i].tamanho - 1, "LA");  
        leituraQuicks[3].contador = cont;
        cout << "terminou LA"  << endl;
        for (int j = 0; j < leituraVetores[i].tamanho; j++) {
            cout << leituraVetores[i].vetorLA[j] << " ";
        }
        cout << endl;

        cont = 0;  
        quickSort(leituraVetores[i].vetorHP, 0, leituraVetores[i].tamanho - 1, "HP");
        leituraQuicks[4].contador = cont;  
        cout << "terminou HP"  << endl;
        for (int j = 0; j < leituraVetores[i].tamanho; j++) {
            cout << leituraVetores[i].vetorHP[j] << " ";
        }
        cout << endl;

        cont = 0; 
        quickSort(leituraVetores[i].vetorHM, 0, leituraVetores[i].tamanho - 1, "HM");  
        leituraQuicks[5].contador = cont;
        cout << "terminou HM"  << endl;
        for (int j = 0; j < leituraVetores[i].tamanho; j++) {
            cout << leituraVetores[i].vetorHM[j] << " ";
        }
        cout << endl;
        
        cont = 0; 
        quickSort(leituraVetores[i].vetorHA, 0, leituraVetores[i].tamanho - 1, "HA");  
        leituraQuicks[6].contador = cont;
        cout << "terminou HA"  << endl;
        for (int j = 0; j < leituraVetores[i].tamanho; j++) {
            cout << leituraVetores[i].vetorHA[j] << " ";
        }
        cout << endl;
        
        cont = 0; 
        mergeSort(leituraQuicks, 1, 6);


        arquivoOut << i << ":N(" << leituraQuicks[0].contador << ")," 
        << leituraQuicks[1].tipo << "(" << leituraQuicks[1].contador << ")," 
        << leituraQuicks[2].tipo << "(" << leituraQuicks[2].contador << ")," 
        << leituraQuicks[3].tipo << "(" << leituraQuicks[3].contador << ")," 
        << leituraQuicks[4].tipo << "(" << leituraQuicks[4].contador << ")," 
        << leituraQuicks[5].tipo << "(" << leituraQuicks[5].contador << ")," 
        << leituraQuicks[6].tipo << "(" << leituraQuicks[6].contador << ")" << endl;

    };
    cout << "cheguei" << endl;

    arquivoIn.close();
    arquivoOut.close();
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo de execução: " << duration.count() << " microsegundos" << endl;
    
    return 0;
};

// ./malu quick.input quick.output