// Implementar programa para ler total de vendas, de um determinado mês,
// dos 300 vendedores da “Matura”, calcular a média de vendas
// do grupo de vendedores, e exibir quantos vendedores apresentaram
// desempenho (vendas) abaixo da média.

#include <stdio.h>

void lerVetor(int v[], int quantItens, char Msg[]) {
    for (int i = 0; i < quantItens; i++){
        printf("%s %d: ", Msg, i+1);
        scanf(" %d",&v[i]);
    }
}

void mediaVetor(int v[], int quantItens, float *media) {
    float total = 0;

    for (int i = 0; i < quantItens; i++)
    {
        total += v[i];
    }

    *media = total/ quantItens;
}

void abaixoMedia(int v[], int quantItens, float media, int *abaixo) {
    int qtd = 0;
    for (int i = 0; i < quantItens; i++)
    {
        if (v[i] < media)
        {
            qtd++;
        }
        
    }
    *abaixo = qtd;
}

int main() {
    const int VENDEDORES = 300;
    int vendas[VENDEDORES], quantAbaixo = 0;
    float media = 0;

    lerVetor(vendas, VENDEDORES, "Vendas do funcionario ");
    mediaVetor(vendas, VENDEDORES, &media);
    abaixoMedia(vendas, VENDEDORES, media, &quantAbaixo);

    printf("Média = %.2f\n", media);

    printf("Vendedores abaixo da média: %d\n", quantAbaixo);
    
}